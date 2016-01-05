#include <string>
#include "MessageProcessor.h"
#include "Drone.h"
#include "Communication.h"
#include "Message.h"


MessageProcessor::MessageProcessor(Communication* moduleCom_, Drone* drone_): moduleCom(moduleCom_), drone(drone_){};

MessageProcessor::~MessageProcessor(){};

void MessageProcessor::start(){
  drone->startThread(this, mProcessorThread);
};

void* MessageProcessor::run(){
    while(true){
        Message * msg= moduleCom->ttMsgPop();
        treatMsg(msg);
    }
    return 0;
};

void MessageProcessor::treatMsg(Message* msg){
    std::string* content =msg->getContent();
    
    //--------------DRONE--------------------//
    if(msg->getType()==Message::SYSTEM){
      if(!content->compare("kill")){
        drone->shutOff();
      }
    }
    if(msg->getType()==Message::PINGANSWER){
        std::string delimiter = ";";
        std::string  id_str = content->substr(0, content->find(delimiter));
        int id = atoi(id_str.c_str());
        moduleCom->registerAnswer(id);
    }
  
    if(msg->getType()== Message::CONTROL){
        std::string delimiter = ";";
        std::size_t pos = 0 ;
        std::size_t oldpos = 0;
        pos = content->find(delimiter);
        std::string  ordre = content->substr(oldpos, pos);
        if(!ordre.compare("target")){
            //X
            oldpos = pos;
            pos = content->find(delimiter);
            std::string x_str = content->substr(oldpos, pos);
            //Y
            oldpos = pos;
            pos = content->find(delimiter);
            std::string y_str = content->substr(oldpos, pos);
            //Z
            oldpos = pos;
            pos = content->find(delimiter);
            std::string z_str = content->substr(oldpos, pos);
            
            drone->setTarget(::atof(x_str.c_str()), ::atof(y_str.c_str()), ::atof(z_str.c_str()));
        }
    }
    if(msg->getType()==Message::CONFIG){
        
    }
   //--------------ORDI------------------------//
    if(msg->getType()==Message::PING){
      std::cout<<"réponse"<<std::endl;
      std::size_t pos = 0 ;
        std::size_t oldpos = 0;
      std::string delimiter = ";";
      pos = content->find(delimiter);
      
      //id ping
      std::string  id_str = content->substr(oldpos, pos);
      Message* msg = new Message(Message::PINGANSWER, id_str, 0);
      moduleCom->addtsMsg(msg);
      
      //incrément ou pas
      oldpos = pos;
      pos = content->find(delimiter);
      std::string type = content->substr(oldpos , pos);
      //X
      oldpos = pos;
      pos = content->find(delimiter);
      std::string x_str = content->substr(oldpos, pos);
      //Y
      oldpos = pos;
      pos = content->find(delimiter);
      std::string y_str = content->substr(oldpos, pos);
      //Z
      oldpos = pos;
      pos = content->find(delimiter);
      std::string z_str = content->substr(oldpos, pos);
      //VX
      oldpos = pos;
      pos = content->find(delimiter);
      std::string vx_str = content->substr(oldpos, pos);
      //VY
      oldpos = pos;
      pos = content->find(delimiter);
      std::string vy_str = content->substr(oldpos, pos);
      //VZ
      oldpos = pos;
      pos = content->find(delimiter);
      std::string vz_str = content->substr(oldpos, pos);
      //alpha
      oldpos = pos;
      pos = content->find(delimiter);
      std::string ax_str = content->substr(oldpos, pos);
      //beta
      oldpos = pos;
      pos = content->find(delimiter);
      std::string ay_str = content->substr(oldpos, pos);
      //gamma
      oldpos = pos;
      pos = content->find(delimiter);
      std::string az_str = content->substr(oldpos, pos);
      //alt
      oldpos = pos;
      pos = content->find(delimiter);
      std::string alt_str = content->substr(oldpos, pos);
      
      
      if(!type.compare("r")){
          drone->setPos(::atof(x_str.c_str()), ::atof(y_str.c_str()), ::atof(z_str.c_str()));
          drone->setSpeed(::atof(vx_str.c_str()), ::atof(vy_str.c_str()), ::atof(vz_str.c_str()));
          drone->setAngles(::atof(ax_str.c_str()), ::atof(ay_str.c_str()), ::atof(az_str.c_str()));
          drone->setAlt(::atof(alt_str.c_str()));
      }else if (!type.compare("i")){
          drone->setPosIncr(::atof(x_str.c_str()), ::atof(y_str.c_str()), ::atof(z_str.c_str()));
          drone->setSpeedIncr(::atof(vx_str.c_str()), ::atof(vy_str.c_str()), ::atof(vz_str.c_str()));
          drone->setAngleIncr(::atof(ax_str.c_str()), ::atof(ay_str.c_str()), ::atof(az_str.c_str()));
          drone->setAltIncr(::atof(alt_str.c_str()));
      }
    
  }
}