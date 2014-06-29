#include "SharedImage.h"

void Image::safeReleaseImage(IplImage*& img)
{
  try
  {
    if(img)
      cvReleaseImage(&img);
  }
  catch(const std::exception &e)
  {
    std::cerr<<e.what()<<std::endl;
  }
  img=nullptr;
}
void Image::safeCopyImage(IplImage *src, IplImage*& dest, IplImage *mask)
{
  if(src == nullptr) return;
  if(dest == nullptr) dest = cvCreateImage(cvGetSize(src),
                                        src->depth, src->nChannels);
  try
  {
    cvCopy(src, dest, mask);
  }
  catch(const std::exception &e)
  {
    std::cerr<<e.what()<<std::endl;
    safeReleaseImage(dest);
    safeCopyImage(src, dest, mask);
  }
}

Image::Image ()
  :m_img(nullptr)
{}

Image::Image (IplImage * img)
  :m_img(nullptr)
{
  safeCopyImage(img, m_img);
}

Image::Image (int W, int H, int D, int C)
{
  m_img = cvCreateImage(cvSize(W,H),D,C);
}

Image::Image(std::string path, bool force_gray)
  :m_img(nullptr)
{
  if(force_gray)
    m_img = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
  else
    m_img = cvLoadImage(path.c_str());
}

Image::~Image ()
{
  safeReleaseImage(m_img);
}

void Image::consume(IplImage *&img)
{
  safeReleaseImage(m_img);
  m_img = img;
  img = nullptr;
}

void Image::split(std::vector<Image::self_shared_ptr>& channels)
{
  if(nullptr == m_img) return;
  for(int i=0; i<m_img->nChannels; i++)
    channels.push_back(std::make_shared<Image>());
  CvSize s = cvGetSize(m_img);
  int d = m_img->depth;
  IplImage *c1 = cvCreateImage(s,d,1);
  IplImage *c2 = cvCreateImage(s,d,1);
  IplImage *c3 = cvCreateImage(s,d,1);
  cvSplit(m_img, c1, c2, c3, nullptr);
  channels[0]->consume(c1);
  channels[1]->consume(c2);
  channels[2]->consume(c3);
}

void Image::merge(const std::vector<Image::self_shared_ptr>& channels)
{
  if(channels.size() != 3) return;
  safeReleaseImage(m_img);
  merge(channels[0],channels[1],channels[2]);
}
void Image::merge(Image::self_shared_ptr c1,Image::self_shared_ptr c2, Image::self_shared_ptr c3)
{
  m_img = cvCreateImage(cvGetSize(c1->get()), c1->get()->depth, 3);
  cvMerge(c1->get(),c2->get(),c3->get(),nullptr,m_img);
}

Image::self_shared_ptr Image::add (Image::self_shared_ptr img)
{
  Image::self_shared_ptr ret = std::make_shared<Image>(m_img->width,
                                                 m_img->height,
                                                 m_img->depth,
                                                 m_img->nChannels);
  IplImage* b = img->get();
  IplImage* a = m_img;
  unsigned char* ad = (unsigned char*)a->imageData;
  unsigned char* bd = (unsigned char*)b->imageData;
  unsigned char* cd = (unsigned char*)ret->get()->imageData;
  assert( a->width == b->width && a->height == b->height );
  for(int i=0; i<a->height; i++)
  {
    int row = i*a->widthStep;
    for(int j=0;j<a->width;j++)
    {
      int loc = row + j;
      int pixel = ad[loc] + bd[loc];
      cd[loc] = (pixel<255)?pixel:255;
    }
  }
  return ret;
}

Image::self_shared_ptr Image::add (Image::self_shared_ptr img, double scale)
{
  double inv_scale = 1-scale;
  Image::self_shared_ptr ret = std::make_shared<Image>(m_img->width,
                                                 m_img->height,
                                                 m_img->depth,
                                                 m_img->nChannels);
  IplImage* b = img->get();
  IplImage* a = m_img;
  unsigned char* ad = (unsigned char*)a->imageData;
  unsigned char* bd = (unsigned char*)b->imageData;
  unsigned char* cd = (unsigned char*)ret->get()->imageData;
  assert( a->width == b->width && a->height == b->height );
  for(int i=0; i<a->height; i++)
  {
    int row = i*a->widthStep;
    for(int j=0;j<a->width;j++)
    {
      int loc = row + j;
      int pixel = (scale)*ad[loc] + (inv_scale)*bd[loc];
      cd[loc] = (pixel<255)?pixel:255;
    }
  }
  return ret;
}

Image::self_shared_ptr Image::sub (Image::self_shared_ptr img)
{
  Image::self_shared_ptr ret = std::make_shared<Image>(m_img->width,
                                                  m_img->height,
                                                  m_img->depth,
                                                  m_img->nChannels);
  IplImage* b = img->get();
  IplImage* a = m_img;
  unsigned char* ad = (unsigned char*)a->imageData;
  unsigned char* bd = (unsigned char*)b->imageData;
  unsigned char* cd = (unsigned char*)ret->get()->imageData;
  assert( a->width == b->width && a->height == b->height );
  for(int i=0; i<a->height; i++)
  {
    int row = i*a->widthStep;
    for(int j=0;j<a->width;j++)
    {
      int loc = row + j;
      cd[loc] = abs(ad[loc] - bd[loc]);
    }
  }
  return ret;
}

Image::self_shared_ptr Image::const_scale(double scale)
{
  Image::self_shared_ptr ret = std::make_shared<Image>(m_img->width,
                                             m_img->height,
                                             m_img->depth,
                                             m_img->nChannels);
  unsigned char* iPtr = (unsigned char*)m_img->imageData;
  unsigned char* oPtr = (unsigned char*)ret->get()->imageData;
  for(int i=0; i<m_img->height; i++)
  {
    int row = i*m_img->widthStep;
    for(int j=0; j<m_img->width; j++)
    {
      int loc = row+j;
      oPtr[loc] = iPtr[loc]*scale;
    }
  }
  return ret;
}

Image::self_shared_ptr Image::cdf()
{
  Image::self_shared_ptr ret = histogram();
  IplImage* cdf = ret->get();
  int *ptr = (int*)cdf->imageData;
  for(int i=1; i<cdf->width; i++)
  {
    ptr[i] = ptr[i-1] + ptr[i];
  }
  return ret;
}

Image::self_shared_ptr Image::histogram()
{
  Image::self_shared_ptr ret = std::make_shared<Image>(256,1,IPL_DEPTH_32S,1);
  ret->zeros();
  IplImage *hist = ret->get();
  unsigned char* ptr = (unsigned char*)m_img->imageData;
  int *hPtr = (int*)hist->imageData;
  for(int i=0; i<m_img->height; i++)
  {
    int row = i*m_img->widthStep;
    for(int j=0; j<m_img->width; j++)
    {
      int loc = row+j;
      hPtr[ptr[loc]]++;
    }
  }
  return ret;
}

void Image::zeros()
{
  unsigned char*  ptr = (unsigned char*)m_img->imageData;
  std::fill_n(ptr, m_img->height*m_img->widthStep, 0);
}

Image::self_shared_ptr Image::to_HSV()
{
  Image::self_shared_ptr ret = std::make_shared<Image>(m_img->width,
                                         m_img->height,
                                         m_img->depth,
                                         m_img->nChannels);
  cvCvtColor(m_img, ret->get(), CV_BGR2HSV);
  return ret;
}

Image::self_shared_ptr Image::to_RGB()
{
  Image::self_shared_ptr ret = std::make_shared<Image>(m_img->width,
                                         m_img->height,
                                         m_img->depth,
                                         m_img->nChannels);
  cvCvtColor(m_img, ret->get(), CV_HSV2BGR);
  return ret;
}

IplImage* Image::get()
{
  return m_img;
}

