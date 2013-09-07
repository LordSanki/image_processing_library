#ifndef __SHAREDIMAGE_H__
#define __SHAREDIMAGE_H__

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <memory>
#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include <algorithm>

#define VAR_OUT(X) std::cout<<#X<<":"<<X<<std::endl;

class Image
{
    typedef std::shared_ptr<Image> self_shared_ptr;
  public:
    static void safeReleaseImage(IplImage*& img)
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
    static void safeCopyImage(IplImage *src, IplImage*& dest, IplImage *mask=nullptr)
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
    Image ()
      :m_img(nullptr)
    {}
    Image (IplImage * img)
      :m_img(nullptr)
    {
      safeCopyImage(img, m_img);
    }
    Image (int W, int H, int D, int C)
    {
      m_img = cvCreateImage(cvSize(W,H),D,C);
    }
    Image(std::string path, bool force_gray=false)
      :m_img(nullptr)
    {
      if(force_gray)
        m_img = cvLoadImage(path.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
      else
        m_img = cvLoadImage(path.c_str());
    }
    ~Image ()
    {
      safeReleaseImage(m_img);
    }
    void consume(IplImage *&img)
    {
      safeReleaseImage(m_img);
      m_img = img;
      img = nullptr;
    }
    void split(std::vector<self_shared_ptr>& channels)
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

    void merge(const std::vector<self_shared_ptr>& channels)
    {
      if(channels.size() != 3) return;
      safeReleaseImage(m_img);
      m_img = cvCreateImage(cvGetSize(channels[0]->get()), channels[0]->get()->depth, 3);
      cvMerge(channels[0]->get(),channels[1]->get(),channels[2]->get(),nullptr,m_img);
    }

    self_shared_ptr add (self_shared_ptr img)
    {
      self_shared_ptr ret = std::make_shared<Image>(m_img->width,
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

    self_shared_ptr sub (self_shared_ptr img)
    {
      self_shared_ptr ret = std::make_shared<Image>(m_img->width,
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


    self_shared_ptr cdf()
    {
      self_shared_ptr ret = histogram();
      IplImage* cdf = ret->get();
      int *ptr = (int*)cdf->imageData;
      for(int i=1; i<cdf->width; i++)
      {
        ptr[i] = ptr[i-1] + ptr[i];
      }
      return ret;
    }

    self_shared_ptr histogram()
    {
      self_shared_ptr ret = std::make_shared<Image>(256,1,IPL_DEPTH_32S,1);
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

    void zeros()
    {
      unsigned char*  ptr = (unsigned char*)m_img->imageData;
      std::fill_n(ptr, m_img->height*m_img->widthStep, 0);
    }

    self_shared_ptr to_HSV()
    {
      self_shared_ptr ret = std::make_shared<Image>(m_img->width,
                                             m_img->height,
                                             m_img->depth,
                                             m_img->nChannels);
      cvCvtColor(m_img, ret->get(), CV_BGR2HSV);
      return ret;
    }

    self_shared_ptr toRGB()
    {
      self_shared_ptr ret = std::make_shared<Image>(m_img->width,
                                             m_img->height,
                                             m_img->depth,
                                             m_img->nChannels);
      cvCvtColor(m_img, ret->get(), CV_HSV2BGR);
      return ret;
    }

    IplImage* get()
    {
      return m_img;
    }
  private:
    IplImage *m_img;
};

typedef std::shared_ptr<Image> SImage;

#endif // __SHAREDIMAGE_H__
