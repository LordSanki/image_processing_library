#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "CallBackInterface.h"
#include <list>
#include <string>

namespace ImageScalerAPI
{
  class ImageScaler;
};

namespace boost
{
  class thread;
}

namespace ControllerDetails
{
  typedef void(*CBfunc)(void*, int, void*);
  struct WorkerCallInterface
  {
      void *callBackObject;
      void *callBackParams;
      int uid;
      CBfunc func;
  };

  class Worker
  {
    public:
      Worker(WorkerCallInterface wci);
      void operator() ();
    private:
      WorkerCallInterface m_wci;
  };
  enum AlgoId
  {
    e_BILINEAR_INTEPOLATION_SCALING=0
  };
}

namespace ControllerAPI
{
  struct AlgoName
  {
      int uid;
      std::string name;
  };

  struct AlgoGroup
  {
      std::string name;
      std::list<AlgoName> algos;
  };

  struct AlgoArgs
  {
      std::string name;
      double value;
  };

  class Controller
  {
    public:
      Controller();
      ~Controller();
      void SetupCBInterface(CBInterface interface);
      void init(std::string path);
      void getListOfAlgos(std::list<AlgoGroup>& types);
      void getAlgoArgsList(int uid, std::list<AlgoArgs>& arglist);
      bool applyAlgo(int uid, const std::list<AlgoArgs>& arglist);
      bool isFree();

      static void workerCallBack(void * arg1, int uid, void* arg2);

    private:
      CBInterface m_cbi;
      std::list<SImage> m_history;
      boost::thread *mp_thread;
      std::list<AlgoGroup> m_algoGroup;
      char* mp_algoParamMemroy;
      int m_algoParamMemroySize;
      ImageScalerAPI::ImageScaler *mp_imageScaler;

    private:
      void generateAlgoLists();
      void* createAlgoParams(int uid, const std::list<AlgoArgs>& arglist);
      void applyAlgo(int uid, void* params);
  };
}
#endif // __CONTROLLER_H__
