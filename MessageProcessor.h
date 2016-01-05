#ifndef MessageProcessor_Header_h
#define MessageProcessor_Header_h


#include "Runnable.h"
#include "Message.h"
#include "Drone.h"
#include "Communication.h"


extern int mProcessorThread;

class Communication;
class Drone;

class MessageProcessor : public Runnable {
  
public:
  
  MessageProcessor(Communication* moduleCom_, Drone* drone);
  ~MessageProcessor();
  
  void start();
  void* run();
  void treatMsg(Message* msg);
  
private:
  
  Communication* moduleCom;
  Drone* drone;
};

#endif