#include "Controller.h"
#include "ImageScaler.h"
#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


using namespace boost;
using namespace ControllerAPI;
using namespace ControllerDetails;

Controller::Controller()
{
  mp_thread = NULL;
  mp_algoParamMemroy = NULL;
  m_algoParamMemroySize = 0;
  m_algoGroup.clear();
  generateAlgoLists();
}

Controller::~Controller()
{
  if(mp_thread)
  {
    mp_thread->join();
    delete mp_thread;
  }
  if(mp_algoParamMemroy)
    free(mp_algoParamMemroy);
}

void Controller::SetupCBInterface(CBInterface interface)
{
  m_cbi = interface;
}

void Controller::init(std::string path)
{
  SImage img = boost::make_shared<Image>(path);
  m_history.push_back(img);
  m_cbi.display(m_cbi.display_arg, m_history.back());
}

void Controller::getListOfAlgos(std::list<AlgoGroup>& types)
{
  types = m_algoGroup;
}

void Controller::getAlgoArgsList(int uid, std::list<AlgoArgs>& arglist)
{
  arglist.clear();
  switch(uid)
  {
    case e_BILINEAR_INTEPOLATION_SCALING:
      arglist.push_back(AlgoArgs());
      arglist.back().name = "Scaling Factor";
      break;
    default:
      break;
  }
}

bool Controller::applyAlgo(int uid, const std::list<AlgoArgs>& arglist)
{
  if(false == isFree())
    return false;
  if(mp_thread)
  {
    delete mp_thread;
    mp_thread = NULL;
  }
  WorkerCallInterface wci;
  wci.func = workerCallBack;
  wci.uid = uid;
  wci.callBackObject = this;
  wci.callBackParams = createAlgoParams(uid, arglist);
  mp_thread = new thread(Worker(wci));
  return true;
}

void* Controller::createAlgoParams(int uid, const std::list<AlgoArgs> &arglist)
{
  if(mp_algoParamMemroy)
    free(mp_algoParamMemroy);
  switch (uid)
  {
    case e_BILINEAR_INTEPOLATION_SCALING:
      mp_algoParamMemroy = (char* )malloc(sizeof(ImageScalerAPI::Params));
      m_algoParamMemroySize = sizeof(ImageScalerAPI::Params);
      ((ImageScalerAPI::Params *)mp_algoParamMemroy)->scale = arglist.front().value;
    break;
    default:
    break;
  }
  return (void*)mp_algoParamMemroy;
}

bool Controller::isFree()
{
  if(mp_thread)
    return mp_thread->timed_join<posix_time::time_duration>(boost::posix_time::milliseconds(5));
  else
    return true;
}

void Controller::workerCallBack(void * arg1, int uid,  void* arg2)
{
  ((Controller*)arg1)->applyAlgo(uid, arg2);
}

void Controller::generateAlgoLists()
{
  {
    m_algoGroup.push_back(AlgoGroup());
    AlgoGroup &grp = m_algoGroup.back();
    grp.algos.push_back(AlgoName());
    AlgoName &algo = grp.algos.back();
    algo.name = "Bilinear Interpolation";
    algo.uid = e_BILINEAR_INTEPOLATION_SCALING;
    mp_imageScaler = new ImageScalerAPI::ImageScaler();
    grp.name = "Scaling";
  }
}

void Controller::applyAlgo(int uid, void *params)
{
  switch (uid) {

    case e_BILINEAR_INTEPOLATION_SCALING:
      m_history.push_back(mp_imageScaler->bilinearScaling(
                           m_history.back(), (ImageScalerAPI::Params*)params));
      m_cbi.display(m_cbi.display_arg, m_history.back());
    break;
    default:
    break;
  }
}

Worker::Worker(WorkerCallInterface wci)
{
  m_wci = wci;
}

void Worker::operator ()()
{
  m_wci.func(m_wci.callBackObject, m_wci.uid, m_wci.callBackParams);
}
