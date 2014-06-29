#ifndef __IMAGESCALER_H__
#define __IMAGESCALER_H__

#include "SharedImage.h"

namespace ImageScaler
{
  class BilinearInterpolation
  {
    public:
      struct Params
      {
          double scale;
      };

      static SImage apply(SImage src, void *params);
  };
}
#endif // __IMAGESCALER_H__
