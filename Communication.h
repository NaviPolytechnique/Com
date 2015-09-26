#ifndef Communication_Header_h
#define Communication_Header_h

#include "BlockingQueue.h"
#include "MessageChecker.h"
#include "Listener.h"
#include "Drone.h"
#include "Message.h"


extern const char* Radio;

class Drone;
class MessageChecker;


class Communication{
  
public :
  
  Communication(Drone* drone_);
  ~Communication();
  void* start();
  void* stop();
  
  char* rMsgPop();
  Message* ttMsgPop();
  
  
private :
  
  Drone* drone;
  
  BlockingQueue<char*>* rMsg;
  BlockingQueue<char*>* tsMsg;
  BlockingQueue<Message*>* ttMsg;
  
  MessageChecker* rMsgChecker; 
  
  Listener* rMsgListener;
  
  
};
#endif