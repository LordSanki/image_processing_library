#ifndef __IMAGESCALER_H__
#define __IMAGESCALER_H__

#include "SharedImage.h"

namespace ImageScalerAPI
{
  struct Params
  {
      double scale;
  };

  class ImageScaler
  {
    public:
      SImage bilinearScaling(SImage src, Params *params);
  };
}
#endif // __IMAGESCALER_H__
