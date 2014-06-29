#include "Controller.h"
#include "ImageScaler.h"
#include <iostream>
#include <GenericFilter.h>
#include <iterator>
#include <utility>
#include <thread>
#include <chrono>

//using namespace std;
using namespace ControllerAPI;
using namespace ControllerDetails;

void Controller::generateAlgoLists()
{
  // Scaling
  {
    m_algoGroup.push_back(AlgoGroup());
    AlgoGroup &grp = m_algoGroup.back();
    grp.algos.push_back(AlgoName());
    {
      AlgoName &algo = grp.algos.back();
      algo.name = "Bilinear Interpolation";
      algo.uid = e_BILINEAR_INTEPOLATION_SCALING;
      m_algoFuncMap.insert(std::make_pair(e_BILINEAR_INTEPOLATION_SCALING, ImageScaler::BilinearInterpolation::apply));
    }
    grp.name = "Scaling";
  }
  // Time Domain Filters
  {
    m_algoGroup.push_back(AlgoGroup());
    AlgoGroup &grp = m_algoGroup.back();
    grp.algos.push_back(AlgoName());
    {
      AlgoName &algo = grp.algos.back();
      algo.name = "Gaussian Filter";
      algo.uid = e_GAUSSIAN_FILTER;
      m_algoFuncMap.insert(std::make_pair(e_GAUSSIAN_FILTER, TimeFilters::GaussianFilter::apply));
    }
    grp.name = "Time Filters";
  }
  // Gradient Detecters
  {
    m_algoGroup.push_back(AlgoGroup());
    AlgoGroup &grp = m_algoGroup.back();
    grp.algos.push_back(AlgoName());
    {
      AlgoName &algo = grp.algos.back();
      algo.name = "Difference of Gaussians";
      algo.uid = e_DOG;
      m_algoFuncMap.insert(std::make_pair(e_DOG, TimeFilters::DoG::apply));
    }
    grp.algos.push_back(AlgoName());
    {
      AlgoName &algo = grp.algos.back();
      algo.name = "Sobel Filter";
      algo.uid = e_SOBEL;
      m_algoFuncMap.insert(std::make_pair(e_SOBEL, TimeFilters::SobelFilter::apply));
    }
    grp.algos.push_back(AlgoName());
    {
      AlgoName &algo = grp.algos.back();
      algo.name = "Scharr Filter";
      algo.uid = e_SCARR;
      m_algoFuncMap.insert(std::make_pair(e_SCARR, TimeFilters::ScharrFilter::apply));
    }
    grp.name = "Gradient Operators";
  }
  // Segmentation
  {
    m_algoGroup.push_back(AlgoGroup());
    AlgoGroup &grp = m_algoGroup.back();
    grp.algos.push_back(AlgoName());
    {
      AlgoName &algo = grp.algos.back();
      algo.name = "Binray Threshold";
      algo.uid = e_BINTHRESH;
      m_algoFuncMap.insert(std::make_pair(e_BINTHRESH, TimeFilters::SimpleThreshold::apply));
    }
    grp.algos.push_back(AlgoName());
    {
      AlgoName &algo = grp.algos.back();
      algo.name = "Bit Splicing";
      algo.uid = e_BITSPLICE;
      m_algoFuncMap.insert(std::make_pair(e_BITSPLICE, TimeFilters::BitSplice::apply));
    }
    grp.name = "Segmentation";
  }
  // Enhancement
  {
    m_algoGroup.push_back(AlgoGroup());
    AlgoGroup &grp = m_algoGroup.back();
    grp.algos.push_back(AlgoName());
    {
      AlgoName &algo = grp.algos.back();
      algo.name = "Normalization";
      algo.uid = e_NORMALIZE;
      m_algoFuncMap.insert(std::make_pair(e_NORMALIZE, TimeFilters::Normalize::apply));
    }
    grp.name = "Enhancement";
  }
}

void Controller::getAlgoArgsList(int uid, std::list<AlgoArgs>& arglist)
{
  arglist.clear();
  switch(uid)
  {
    case e_BILINEAR_INTEPOLATION_SCALING:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "Scaling Factor(greater than 0.0)";
    break;
    case e_GAUSSIAN_FILTER:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "kernel_size(odd kernel >= 3)";
    break;
    case e_DOG:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "kernel_size 1(odd kernel >= 3)";
      arglist.push_back(AlgoArgs());
      arglist.back().name = "kernel_size 2(odd kernel >= 3)";
    break;
    case e_SOBEL:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "kernel_size(3 and 5 only)";
    break;
    case e_SCARR:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "kernel_size(3 and 5 only)";
    break;
    case e_BINTHRESH:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "Threshold(1 to 254)";
      arglist.push_back(AlgoArgs());
      arglist.back().name = "Invert(1 to 254)";
    break;
    case e_BITSPLICE:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "Bit Map(8 digit 0 & 1 )";
    break;
    case e_NORMALIZE:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "Low (0.0-0.9)";
      arglist.push_back(AlgoArgs());
      arglist.back().name = "High (0.1-1.0)";
    break;
    default:
    break;
  }
}


void Controller::applyAlgo(int uid, void *params)
{
  if(m_history.size() > 9)
    m_history.pop_front();
  switch (uid) {
    case e_UNDO:
      m_history.pop_back();
    break;
    case e_BILINEAR_INTEPOLATION_SCALING:
    case e_GAUSSIAN_FILTER:
    case e_DOG:
    case e_SOBEL:
    case e_SCARR:
    case e_BINTHRESH:
    case e_BITSPLICE:
    case e_NORMALIZE:
    default:
      m_history.push_back(m_algoFuncMap[uid](m_history.back(), params));
    break;
  }
  m_cbi.display(m_cbi.display_arg, m_history.back());
}

Controller::Controller()
{
  mp_algoParamMemroy = nullptr;
  m_algoGroup.clear();
  m_algoFuncMap.clear();
  generateAlgoLists();
}

Controller::~Controller()
{
  if(m_future.valid())
    m_future.wait();
  if(mp_algoParamMemroy)
    free(mp_algoParamMemroy);
}

void Controller::SetupCBInterface(CBInterface interface)
{
  m_cbi = interface;
}

void Controller::init(std::string path, bool force_gray)
{
  SImage img = std::make_shared<Image>(path, force_gray);
  m_history.push_back(img);
  m_cbi.display(m_cbi.display_arg, m_history.back());
}

void Controller::getListOfAlgos(std::list<AlgoGroup>& types)
{
  types = m_algoGroup;
}


bool Controller::undo()
{
  if(false == isFree())
    return false;
  CallInterface tci;
  tci.func = threadCallBack;
  tci.uid = e_UNDO;
  tci.callBackObject = this;
  tci.callBackParams = nullptr;
  m_future = std::async(std::launch::async,
                        [tci] () mutable -> int { return tci.func(tci.callBackObject, tci.uid, tci.callBackParams); }
                        );
  return true;
}

bool Controller::applyAlgo(int uid, const std::list<AlgoArgs>& arglist)
{
  if(false == isFree())
    return false;
  CallInterface tci;
  tci.func = threadCallBack;
  tci.uid = uid;
  tci.callBackObject = this;
  tci.callBackParams = createAlgoParams(uid, arglist);
  m_future = std::async(std::launch::async,
                        [tci] () mutable -> int { return tci.func(tci.callBackObject, tci.uid, tci.callBackParams); }
                        );
  return true;
}

void* Controller::createAlgoParams(int, const std::list<AlgoArgs> &arglist)
{
  if(mp_algoParamMemroy)
    free(mp_algoParamMemroy);
  std::list<AlgoArgs>::const_iterator it = arglist.begin();
  mp_algoParamMemroy = (double*)malloc(sizeof(double)*arglist.size());
  for(int i=0;i<arglist.size();i++)
  {
    mp_algoParamMemroy[i] = it->value;
    it++;
  }
  return (void*)mp_algoParamMemroy;
}

bool Controller::isFree()
{
  if(m_future.valid())
  {
    auto status = m_future.wait_for(std::chrono::milliseconds(1));
    if(!status)
      return false;
  }
  return true;
}

int Controller::threadCallBack(void * arg1, int uid,  void* arg2)
{
  ((Controller*)arg1)->applyAlgo(uid, arg2);
  return 0;
}
