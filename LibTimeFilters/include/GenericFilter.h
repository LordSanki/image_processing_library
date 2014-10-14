#ifndef __GENERIC_FILTER_H__
#define __GENERIC_FILTER_H__

#include "SharedImage.h"
#include <limits>

namespace TimeFilters
{
  class Normalize
  {
    public:
      struct Params
      {
          double low; // % data for lower bin
          double high; // % data for lower bin
      };
      static SImage apply(SImage src, void *params);
  };

  class BitSplice
  {
    public:
      struct Params
      {
          double bit_map; // eight digit bitmap of 0 or 1
      };
      static SImage apply(SImage src, void *params);
  };

  class SimpleThreshold
  {
    public:
      struct Params
      {
          double thresh;
          double invert;
      };
      static SImage apply(SImage src, void *params);
  };

  class SobelFilter
  {
    public:
      struct Params
      {
          double kernel_size; // 3 or 5
      };
      static SImage apply(SImage src, void *params);
  };

  class ScharrFilter
  {
    public:
      struct Params
      {
          double kernel_size; // 3 or 5
      };
      static SImage apply(SImage src, void *params);
  };

  class DoG
  {
    public:
      struct Params
      {
          double kernel_size1;
          double kernel_size2;
      };
      static SImage apply(SImage src, void *params);
  };

  class GaussianFilter
  {
    public:
      struct Params
      {
          double kernel_size;
      };
    public:
      static SImage apply(SImage src, void *params);

    private:
      static void createKernel( int size, double *& k);
  };

  namespace Utility
  {
    template <class T>
    class DataHelper
    {
      public:
        int row;
        int col;
        std::vector<T*> rows;
        void init(T *ptr, int nrow, int ncol, int widthstep)
        {
          row = nrow; col = ncol;
          for(int i=0;i<nrow;i++)
          {
            T *c = (T*)ptr + i*widthstep;
            rows.push_back(c);
          }
        }
        inline T* operator[] (int index)
        {
          return rows[index];
        }
    };

    template <class IMAGE, class MASK>
    SImage convolve(SImage src, DataHelper<MASK> mask)
    {
      SImage ret;
      if(src->get()->nChannels > 1)
      {
        ret = std::make_shared<Image>();
        std::vector<SImage> iC;
        std::vector<SImage> oC;
        src->split(iC);

        for(int i=0; i<iC.size(); i++)
        {
          oC.push_back(std::make_shared<Image>(iC[i]->get()->width,
                                                 iC[i]->get()->height,
                                                 iC[i]->get()->depth,
                                                 iC[i]->get()->nChannels));
          DataHelper <IMAGE> input, output;
          input.init((IMAGE*)iC[i]->get()->imageData, iC[i]->get()->height, iC[i]->get()->width, iC[i]->get()->widthStep);
          output.init((IMAGE*)oC[i]->get()->imageData, oC[i]->get()->height, oC[i]->get()->width, oC[i]->get()->widthStep);
          convolve_1C(input, output, mask);
        }
        ret->merge(oC);
      }
      else
      {
        ret = std::make_shared<Image>(src->get()->width,
                                        src->get()->height,
                                        src->get()->depth,
                                        src->get()->nChannels);
        DataHelper <IMAGE> input, output;
        output.init((IMAGE*)ret->get()->imageData, ret->get()->height, ret->get()->width, ret->get()->widthStep);
        input.init((IMAGE*)src->get()->imageData, src->get()->height, src->get()->width, src->get()->widthStep);
        convolve_1C(input, output, mask);
      }
      return ret;
    }

    template <class INPUT, class OUTPUT, class MASK>
    void convolve_1C(DataHelper<INPUT> input, DataHelper<OUTPUT> output,
                  DataHelper<MASK> mask)
    {
      int kS = mask.row;
      int hKS = kS/2;
      int iH = input.row - hKS;
      int iW = input.col - hKS;
      for(int iR=hKS; iR < iH; iR++)
      {
        for(int iC=hKS; iC < iW; iC++)
        {
          double pixel=0;
          for(int imR=0; imR < kS; imR++)
            for(int imC=0; imC < kS; imC++)
              pixel += input[iR+imR -hKS][iC+imC -hKS] * mask[imR][imC];
          if(pixel > std::numeric_limits<OUTPUT>::max())
            pixel = std::numeric_limits<OUTPUT>::max();
          if(pixel < -std::numeric_limits<MASK>::min())
            pixel = std::numeric_limits<MASK>::min();
          output[iR][iC] = (OUTPUT)pixel;
        }
      }
      for(int iR=0;iR<hKS;iR++)
      {
        for(int iC=0;iC<input.col;iC++)
        {
          output[iR][iC] = 0;
        }
      }
      for(int iR=iH+hKS;iR<input.row;iR++)
      {
        for(int iC=0;iC<input.col;iC++)
        {
          output[iR][iC] = 0;
        }
      }
      for(int iR=0;iR<input.row;iR++)
      {
        for(int iC=0;iC<hKS;iC++)
        {
          output[iR][iC] = 0;
        }
      }
      for(int iR=0;iR<input.row;iR++)
      {
        for(int iC=iW+hKS;iC<input.col;iC++)
        {
          output[iR][iC] = 0;
        }
      }
    }
  }
}

#endif // __GENERIC_FILTER_H__
