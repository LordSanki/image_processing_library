#ifndef __SHAREDIMAGE_H__
#define __SHAREDIMAGE_H__

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <string>
#include <exception>
#include <iostream>

class Image
{
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
      img=NULL;
    }
    static void safeCopyImage(IplImage *src, IplImage*& dest, IplImage *mask=NULL)
    {
      if(src == NULL) return;
      if(dest == NULL) dest = cvCreateImage(cvGetSize(src),
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
      :m_img(NULL)
    {}
    Image (IplImage * img)
      :m_img(NULL)
    {
      safeCopyImage(img, m_img);
    }
    Image(std::string path)
      :m_img(NULL)
    {
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
      img = NULL;
    }
    IplImage* get()
    {
      return m_img;
    }
  private:
    IplImage *m_img;
};

typedef boost::shared_ptr<Image> SImage;

#endif // __SHAREDIMAGE_H__
