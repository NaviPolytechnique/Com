#ifndef Communication_Header_h
#define Communication_Header_h


#include "BlockingQueue.h"
#include "MessageChecker.h"
#include "Listener.h"
#include "Drone.h"
#include "Message.h"
#include "MessageProcessor.h"
#include "MessageSender.h"
#include "PingProcessor.h"
#include "ComException.h"

extern char* Radio;

class Drone;
class MessageChecker;
class MessageProcessor;
class MessageSender;
class PingProcessor;
class ComException;


class Communication{
  
public :
  
  Communication(Drone* drone_);
  ~Communication();
  void start();
  void stop();
  
  char* rMsgPop();
  Message* ttMsgPop();
  void addttMsg(Message* msg);
  void addtsMsg(Message* msg);
  Message* tsMsgPop();
  char* pingPop();
  
  void sendStr(char* str);
  
  void registerAnswer(int id);
  
  void launchException(std::exception e);
    
    
private :
  
  Drone* drone;
  
  BlockingQueue<char*>* rMsg;
  BlockingQueue<Message*>* tsMsg;
  BlockingQueue<Message*>* ttMsg;
  BlockingQueue<char*>* ping;
  
  MessageChecker* rMsgChecker; 
  MessageSender* msgSender;
  
  Listener* rMsgListener;
  
  MessageProcessor* msgProcessor;
  PingProcessor* pingProcessor;
  
  
  
};
#endif