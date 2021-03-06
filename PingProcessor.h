#ifndef PingProcessor_Header_h
#define PingProcessor_Header_h

#include "pthread.h"
#include "Runnable.h"
#include "Message.h"
#include "Drone.h"
#include "Communication.h"
#include "Point3D.hpp"


extern int pingProcessorThread;



class Communication;
class Drone;


class PingProcessor : public Runnable {
  
public:
  
  PingProcessor(Communication* moduleCom_, Drone* drone_);
  ~PingProcessor();
  
  void start();
  void* run();
  
  void registerAnswer(int i);
  
private:
  
  Drone* drone;
  Communication* moduleCom;
  int* id;
    
  Point3D<uint16_t>* target;
  Point3D<uint16_t>* pos;
  Point3D<uint16_t>* speed;
  Point3D<uint16_t>* angles;
  Point3D<uint16_t>* posincr;
  Point3D<uint16_t>* speedincr;
  Point3D<uint16_t>* angleincr;
    
    
    //Attention : les verrous de la classe drone ne servent a rien ici
  uint16_t* alt;
  uint16_t* altincr;
  uint8_t* charge;
  uint8_t* chargeincr;
    
    
  
  
  void waitAnswer(int i);
  
  pthread_mutex_t waiting_mutex;
  int waiting[10];
  
  
  
  
};
#endif