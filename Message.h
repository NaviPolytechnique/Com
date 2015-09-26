#ifndef Message_H_INCLUDED
#define Message_H_INCLUDED

#include<string>


class Message{
  
  
public:
  
  Message(msg_type type_, std::string* content_);
  ~Message();
  msg_type getType();
  std::string* getContent();
  int* getId();
  
  enum msg_type {SYSTEM, CONTROL, EMERGENCY};
  
  
private:
  
  std::string* content;
  int* id;
  Message::msg_type type;
}; 


#endif