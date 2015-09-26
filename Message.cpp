#include<string>


Message::Message(msg_type type_; std::string* content_, int* id_):type(type_), content(content_), id(id_){};

Message::~Message(){};

Message::msg_type Message::getType(){
  return type;
};

std::string* Message::getContent(){
  return content;
};

int* Message::getId(){
  return id;
};