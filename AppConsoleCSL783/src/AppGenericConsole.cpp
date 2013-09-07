#include "Controller.h"
#include "SharedImage.h"
#include <list>
#include <opencv/highgui.h>

using namespace std;
using namespace ControllerAPI;

void applyAlgo(int uid, Controller *obj)
{
  if(uid == -1) return;
  list<AlgoArgs> arglist;
  obj->getAlgoArgsList(uid, arglist);
  typedef list<AlgoArgs>::iterator  ArgIT;
  for(ArgIT it= arglist.begin(); it!= arglist.end(); it++)
  {
    cout<<"Enter "<<it->name<<" : ";
    scanf("%lf", &it->value);
  }
  obj->applyAlgo(uid, arglist);
}

void callBackDisplay(void *arg, SImage img)
{
  cvSaveImage("output.jpg", img->get());
  cvDestroyAllWindows();
  cvNamedWindow("IMAGE");
  cvShowImage("IMAGE", img->get());
  cvWaitKey(500);
}

void printMenu()
{
  cout << "\x1b[2J\x1b[1;1H" <<endl;
  cout.flush();
  cout<<"=================================================================="<<endl;
  cout<<"Q/E  ::::    Exit/Quit"<<endl;
  cout<<"P    ::::    Print Menu"<<endl;
  cout<<"L    ::::    List Algorithms"<<endl;
  cout<<"A    ::::    Apply Algorithms"<<endl;
  cout<<"U    ::::    Undo Last Operation"<<endl;
  cout<<"=================================================================="<<endl;
  cout.flush();
}

int main(int argc, char** argv)
{
  Controller *m_controller = new Controller();
  CBInterface interface;
  interface.display_arg = nullptr;
  interface.display = callBackDisplay;
  m_controller->SetupCBInterface(interface);
  if(argc > 1)
  {
    if(argc > 2)
    {
      std::string s = &argv[2][0];
      if(s.compare("-g")==0)
        m_controller->init(&argv[1][0], true);
    }
    else
      m_controller->init(&argv[1][0]);
  }
  else
  {
    cout<<"Usage: App <path to image file> <-g to force grayscale>"<<endl;
    return -1;
  }

  char c = 'S';
  list<AlgoGroup> algos;
  typedef list<AlgoGroup>::iterator GrpIT;
  typedef list<AlgoName>::iterator NameIT;
  m_controller->getListOfAlgos(algos);
  printMenu();
  while(true)
  {
    cout<<"Enter Choice #> ";
    cout.flush();
    cin>>c;
    int uid;
    switch(c)
    {
      case 'l':
      case 'L':
        for(GrpIT it=algos.begin();it!= algos.end();it++)
        {
          cout<<"<<<<<<<<   "<<it->name<<"   >>>>>>>>>"<<endl;
          for(NameIT it2 = it->algos.begin(); it2 != it->algos.end(); it2++)
          {
            cout<<"\t"<<it2->uid<<"   ::::    "<<it2->name<<endl;
          }
        }
      break;
      case 'p':
      case 'P':
        printMenu();
      break;
      case 'a':
      case 'A':
        if(m_controller->isFree())
        {
          cout<<"Enter Algo ID(-1 to Cancel): ";
          scanf("%d", &uid);
          applyAlgo(uid, m_controller);
        }
        else
        {
          cout<<"Engine is busy please try after some time"<<endl;
        }
      break;
      case 'U':
      case 'u':
        m_controller->undo();
      break;
      case 'e':
      case 'E':
      case 'Q':
      case 'q':
        break;
      default:
        cout<<"Invalid Input"<<endl;
        break;
    }
    if(c == 'q'|| c=='Q'|| c=='E'|| c=='e')
      break;
  }
  cout<<"Exiting....."<<endl;
  delete m_controller;
  cvDestroyAllWindows();
  cout << "\x1b[2J\x1b[1;1H" <<endl;
  cout.flush();
  cout<<"Good Bye !!!"<<endl;
  cout.flush();
  return 0;
}

