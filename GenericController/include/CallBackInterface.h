#ifndef __CALLBACKINTERFACE_H__
#define __CALLBACKINTERFACE_H__

#include "SharedImage.h"

typedef void(*CBDisplay)(void *arg, SImage img);
typedef void(*CBProgress)(void *arg, int percent_done);

class CBInterface
{
  public:
    void *display_arg;
    void *progress_arg;
    CBDisplay display;
    CBProgress progress;
};

#endif //__CALLBACKINTERFACE_H__
