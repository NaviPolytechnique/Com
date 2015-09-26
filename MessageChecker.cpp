#include <iostream>
#include <stdint.h>
#include "MessageChecker.h"
#include "Drone.h"
#include "Communication.h"
#include "Message.h"
#include <string>
#include <vector>


using namespace std;

MessageChecker::MessageChecker(Communication* moduleCom_, Drone* drone_) : moduleCom(moduleCom_), drone(drone_){};  


MessageChecker::~MessageChecker(){};


void* MessageChecker::start(){  
     drone->startThread(this, mCheckerThread);
};

void* MessageChecker::run(){
  while(true){
    char* msg = moduleCom->rMsgPop();
    vector<string> msg_tab(6);
    int j = MessageChecker::isValid(msg, &msg_tab);
    std::cout<<msg<<std::endl;
    if(j){
      std::cout<<"valide"<<std::endl;
      int i = addMsgToProcess(&msg_tab);
      if(i==1){
	std::cout<<"wrong message type"<<std::endl;
      }
      else{
	std::cout<<"message added to to treat queue"<<std::endl;
      }
    }else{
      std::cout<<"message non valide"<<std::endl;
    }
    /*std::cout<<msg<<std::endl;
    const char* kill = "kill\r\n";
    std::cout<<strcmp(msg, kill)<<std::endl;
    
    if(!strcmp(msg, kill)){
      drone->shutOff();
    }*/
  }
};

int MessageChecker::isValid(char* msg, std::vector<std::string>* msg_tab){
  /*
  char* beggining=...
  if(strcmp(beginning,"$")){
    std::cout<<"Mauvais début, on renvoie une demande"<<std::endl;
  }else{
    std::cout<<"bon début"<<std::endl;
  }
  
  pch = strtok(NULL, ";");
  std::cout<<msg<<" msg1"<<std::endl;
  std::cout<<pch<<" pch1"<<std::endl;
  unsigned int checksum = Adler*/
  
  
  
  string wholeMsg(msg);
  int decomposition;
  decomposition = MessageChecker::decompose(wholeMsg, &msg_tab);
  

  
  if(decomposition != 0){
    std::cout<<"$? "<<msg_tab[0]<<std::endl;
    if(msg_tab[0].compare("$")!=0){
      std::cout<<"mauvais début"<<std::endl;
      return 0;
    }
  
    string string_to_Check;
    char* char_to_Check;
    int computed_checksum;
    int received_checksum;
    
    string_to_Check = msg_tab[2]+";"+msg_tab[3]+";"+msg_tab[4]+";"+msg_tab[5]; //reconstruction pour vérifier le checksum
    size_t len = string_to_Check.size();
    char_to_Check = (char*)string_to_Check.c_str();
    computed_checksum = MessageChecker::Adler32(char_to_Check, len);
    received_checksum = atoi((char*)msg_tab[1].c_str());
    
    std::cout<<"checksum :"<< computed_checksum<<std::endl;
    
    if(computed_checksum!=received_checksum){
      std::cout<<"erreur de checksum"<<std::endl;
      return 0;
    } 
  }
  else{
    std::cout<<"mal passé"<<std::endl;
    return 0;
  }
  return 1;
};

int addMessageToProcess(std::vector<std::string>* msg_tab){
  std::string type(msg_tab[4]);
  int* id;
  *id = atoi((char*)msg_tab[3].c_str());
  if(type.compare("SYSTEM")){
    Message* msg = new Message(Message::SYSTEM, msg_tab[5]);
    return 1;
  }else if(type.compare("EMERGENCY")){
    Message* msg = new Message(Message::EMERGENCY, msg_tab[5]);
    return 1;
  }else if(type.compare("CONTROL")){
    Message* msg = new Message(Message::CONTROL, msg_tab[5]);
    return 1;
  }
    return 0;
};

uint32_t MessageChecker::Adler32(char* msg, size_t len){
  
  uint32_t a=1, b=0;
  size_t index;
  for(index = 0; index<len;++index){
    a = (a+msg[index]) % MOD_ADLER;
    b = (b+a) % MOD_ADLER;
  }
  return (b<<16)|a;
};

int MessageChecker::decompose(string str, std::vector<std::string>* buffer){
  std::size_t pos =1;
  std::size_t len;
  std::size_t found;
  string a;
  
  found =str.find(";", pos);
  for(int i = 0; i<5;i++){
    
    if(found!=std::string::npos){
      len = found-pos+1;
      a =str.substr(found-len,len);
      (*buffer)[i]= a;
      pos += len + 1;
      found =str.find(";", pos);
      
    }else{
      return 0;
    }
    
  }
  found =str.find("\r\n", pos);
  if(found!=std::string::npos){
    len = found-pos+1;
    a =str.substr(found-len,len);
    (*buffer)[5]= a;
  }else{
    return 0;
  }
  return 1;
  
};

