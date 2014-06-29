#include "ImageScaler.h"

using namespace ImageScaler;

SImage BilinearInterpolation::apply(SImage src, void *_params)
{
  BilinearInterpolation::Params *params = (BilinearInterpolation::Params *)_params;
  IplImage *input = src->get();
  int W = input->width * params->scale;
  int H = input->height * params->scale;
  IplImage *output = cvCreateImage(cvSize(W,H), input->depth, input->nChannels);
  cvResize(input, output);
  SImage img = std::make_shared<Image>();
  img->consume(output);
  return img;
}
