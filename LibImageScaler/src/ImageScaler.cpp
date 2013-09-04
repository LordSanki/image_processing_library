#include "ImageScaler.h"

using namespace ImageScalerAPI;

SImage ImageScaler::bilinearScaling(SImage src, Params *params)
{
  IplImage *input = src->get();
  int W = input->width * params->scale;
  int H = input->height * params->scale;
  IplImage *output = cvCreateImage(cvSize(W,H), input->depth, input->nChannels);
  cvResize(input, output);
  SImage img = boost::make_shared<Image>();
  img->consume(output);
  return img;
}
