#include "GenericFilter.h"
#include <cmath>
#include <limits>
using namespace TimeFilters;
using namespace TimeFilters::Utility;

SImage Normalize::apply(SImage src, void *_params)
{
  Normalize::Params *params = (Normalize::Params *)_params;
  SImage ret = std::make_shared<Image>(src->get()->width,
                                         src->get()->height,
                                         src->get()->depth,
                                         src->get()->nChannels);
  SImage hist = src->cdf();
  int* ptr = (int*)hist->get()->imageData;
  int lV = params->low*ptr[255];
  int hV = params->high*ptr[255];
  int lI=0, hI=255;
  for(int i=0;i<256;i++) // generating bounds
  {
    if(lV > ptr[i])
      lI=i;
    if(hV < ptr[i])
    {
      hI=i;
      break;
    }
  }
  unsigned char map[256];
  for(int i=0; i<256;i++) // genetaring map
  {
    int m = ((i-lI)*255)/hI;
    m = (m>0)?m:0;
    m = (m<255)?m:255;
    map[i] = m;
  }
  unsigned char* oPtr = (unsigned char*)ret->get()->imageData;
  unsigned char* iPtr = (unsigned char*)src->get()->imageData;
  for(int i=0; i<src->get()->height; i++) //mapping image
  {
    int row = i*src->get()->widthStep;
    for(int j=0; j<src->get()->width; j++)
    {
      int loc = row+j;
      oPtr[loc] = map[iPtr[loc]];
    }
  }
  return ret;
}

SImage BitSplice::apply(SImage src, void *_params)
{
  BitSplice::Params *params = (BitSplice::Params *)_params;
  unsigned char byte_mask = 0x0;
  unsigned char bit_mask = 0x1;
  unsigned int bit_map = params->bit_map;
  for(int i=0;i<8;i++)
  {
    if(i > 0)
      bit_mask = bit_mask<<1;
    if(bit_map%10 > 0)
      byte_mask = byte_mask | bit_mask;
    bit_map = bit_map/10;
  }
  SImage ret = std::make_shared<Image>(src->get()->width,
                                         src->get()->height,
                                         src->get()->depth,
                                         src->get()->nChannels);
  unsigned char *iData = (unsigned char*)src->get()->imageData;
  unsigned char *oData = (unsigned char*)ret->get()->imageData;
  for(int i=0;i<src->get()->height;i++)
  {
    int row = i*src->get()->widthStep;
    for(int j=0; j<src->get()->width;j++)
    {
      int loc = row+j;
      oData[loc] = iData[loc] & byte_mask;
    }
  }
  return ret;
}

SImage SimpleThreshold::apply(SImage src, void *_params)
{
  SimpleThreshold::Params *params = (SimpleThreshold::Params *)_params;
  SImage ret = std::make_shared<Image>(src->get()->width,
                                         src->get()->height,
                                         src->get()->depth,
                                         src->get()->nChannels);
  unsigned char level = params->thresh;
  bool invert = false;
  if(params->invert > std::numeric_limits<double>::min())
    invert = true;
  int high=255,low=0;
  if(invert){high = 0; low = 255;}
  unsigned char *idata = (unsigned char*)src->get()->imageData;
  unsigned char *odata = (unsigned char*)ret->get()->imageData;

  for(int i=0; i<src->get()->height; i++)
  {
    int row = i*src->get()->widthStep;
    for(int j=0; j<src->get()->width; j++)
    {
      int loc = row+j;
      odata[loc] = (idata[loc]>level)?high:low;
    }
  }
  return ret;
}

SImage SobelFilter::apply(SImage src, void *_params)
{
  SobelFilter::Params *params = (SobelFilter::Params *)_params;
  SImage ret;
  const double kernel_3_x [9] = {1,2,1,0,0,0,-1,-2,-1};
  const double kernel_3_y [9] = {1,0,-1,2,0,-2,1,0,-1};
  const double kernel_5_x [25] = {5,8,10,8,5,4,10,20,10,4,0,0,0,0,0,-4,-10,-20,-10,-4,-5,-8,-10,-8,-5};
  const double kernel_5_y [25] = {5,4,0,-5,-4,8,10,0,-10,-8,10,20,0,-20,-10,8,10,0,-10,-8,5,4,0,-5,-4};

  DataHelper <const double> maskX, maskY;

  if(params->kernel_size == 3)
  {
    maskX.init(kernel_3_x, params->kernel_size, params->kernel_size, params->kernel_size);
    maskY.init(kernel_3_y, params->kernel_size, params->kernel_size, params->kernel_size);
  }
  else if(params->kernel_size == 5)
  {
    maskX.init(kernel_5_x, params->kernel_size, params->kernel_size, params->kernel_size);
    maskY.init(kernel_5_y, params->kernel_size, params->kernel_size, params->kernel_size);
  }
  else
    return src;
  SImage sobelX = convolve <unsigned char, const double> (src,maskX);
  SImage sobelY = convolve <unsigned char, const double> (src,maskY);
  ret = sobelX->add(sobelY);
  return ret;
}

SImage ScharrFilter::apply(SImage src, void *_params)
{
  ScharrFilter::Params *params = (ScharrFilter::Params *)_params;
  SImage ret;
  const double kernel_3_x [9] = {3,10,3,0,0,0,-3,-10,-3};
  const double kernel_3_y [9] = {3,0,-3,10,0,-10,3,0,-3};
  const double kernel_5_x [25] = {1,2,3,2,1,1,2,6,2,1,0,0,0,0,0,-1,-2,-6,-2,-1,-1,-2,-3,-2,-1};
  const double kernel_5_y [25] = {1,1,0,-1,-1,2,2,0,-2,-2,3,6,0,-6,-3,2,2,0,-2,-2,1,1,0,-1,-1};

  DataHelper <const double> maskX, maskY;

  if(params->kernel_size == 3)
  {
    maskX.init(kernel_3_x, params->kernel_size, params->kernel_size, params->kernel_size);
    maskY.init(kernel_3_y, params->kernel_size, params->kernel_size, params->kernel_size);
  }
  else if(params->kernel_size == 5)
  {
    maskX.init(kernel_5_x, params->kernel_size, params->kernel_size, params->kernel_size);
    maskY.init(kernel_5_y, params->kernel_size, params->kernel_size, params->kernel_size);
  }
  else
    return src;
  SImage scharrX = convolve <unsigned char, const double> (src,maskX);
  SImage scharrY = convolve <unsigned char, const double> (src,maskY);
  ret = scharrX->add(scharrY);
  return ret;
}

SImage DoG::apply(SImage src, void *_params)
{
  DoG::Params *params = (DoG::Params *)_params;
  SImage ret;
  GaussianFilter::Params arg;
  arg.kernel_size = params->kernel_size1;
  SImage g1 = GaussianFilter::apply(src, &arg);
  arg.kernel_size = params->kernel_size2;
  SImage g2 = GaussianFilter::apply(src, &arg);
  ret = g1->sub(g2);
  return ret;
}

SImage GaussianFilter::apply(SImage src, void *_params)
{
  GaussianFilter::Params *params = (GaussianFilter::Params *)_params;
  double *kernel = nullptr;
  createKernel((int)params->kernel_size, kernel);

  SImage ret;
  DataHelper <double> mask;
  mask.init(kernel, params->kernel_size, params->kernel_size, params->kernel_size);
  ret = convolve <unsigned char, double> (src, mask);
  free(kernel);
  return ret;
}

void GaussianFilter::createKernel( int size, double *& k)
{
  k = (double*)malloc(size*size*sizeof(double));
  int size1 = size/2;
  double size2= size*size*2;
  double sum=0;
  for(int i=0; i< size; i++)
  {
    int r = i*size;
    for(int j=0; j<size; j++)
    {
      int x=size1-i; int y=size1-j;
      k[r+j] = exp(-(x*x+y*y)/size2);
      sum += k[r+j];
    }
  }
  for(int i=0; i< size; i++)
  {
    int r= i*size;
    for(int j=0; j<size; j++)
    {
      k[r+j] = k[r+j]/sum;
    }
  }
}
