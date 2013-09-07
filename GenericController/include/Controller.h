#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "CallBackInterface.h"
#include <list>
#include <string>
#include <unordered_map>
#include <future>


namespace ControllerAPI
{
  namespace ControllerDetails
  {
    typedef int(*CBfunc)(void*, int, void*);
    struct CallInterface
    {
        void *callBackObject;
        void *callBackParams;
        int uid;
        CBfunc func;
    };

    enum AlgoId
    {
      e_UNDO=-0,
      e_BILINEAR_INTEPOLATION_SCALING=1,
      e_GAUSSIAN_FILTER=2,
      e_DOG=3,
      e_SOBEL=4,
      e_SCARR=5,
      e_BINTHRESH=6,
      e_BITSPLICE=7,
      e_NORMALIZE=8
    };
  }

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
      typedef SImage (*AlgoFunction)(SImage, void*);
    public:
      Controller();
      ~Controller();
      void SetupCBInterface(CBInterface interface);
      void init(std::string path, bool force_gray=false);
      void getListOfAlgos(std::list<AlgoGroup>& types);
      void getAlgoArgsList(int uid, std::list<AlgoArgs>& arglist);
      bool applyAlgo(int uid, const std::list<AlgoArgs>& arglist);
      bool isFree();
      bool undo();

      static int threadCallBack(void * arg1, int uid, void* arg2);

    private:
      CBInterface m_cbi;
      std::list<SImage> m_history;
      std::future<int> m_future;
      std::list<AlgoGroup> m_algoGroup;
      double* mp_algoParamMemroy;
      std::unordered_map<int,AlgoFunction> m_algoFuncMap;

    private:
      void generateAlgoLists();
      void* createAlgoParams(int uid, const std::list<AlgoArgs>& arglist);
      void applyAlgo(int uid, void* params);
  };
}
#endif // __CONTROLLER_H__
