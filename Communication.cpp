#include "Communication.h"
#include "BlockingQueue.h"
#include "Drone.h"
#include "Message.h"


using namespace std;

Communication::Communication(Drone* drone_): drone(drone_){
  
  rMsg = new BlockingQueue<char*>();
  tsMsg = new BlockingQueue<char*>();
  ttMsg = new BlockingQueue<Message*>();
  
  
  rMsgListener = new Listener(Radio, rMsg);
  rMsgChecker = new MessageChecker(this, drone);
  
  
};

Communication::~Communication(){};

void* Communication::start(){
  
  rMsgListener->start();
  rMsgChecker->start();
   
  std::cout<<"Communication started"<<std::endl;
    
};

char* Communication::rMsgPop(){

  return rMsg->pop();
  
};

Message* Communication::ttMsgPop(){
  
  return ttMsg->pop();
};

void* addttMsg(Message* msg){
  
  ttMsg->add(msg);
};