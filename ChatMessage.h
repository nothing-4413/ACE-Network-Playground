#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <string>

struct ChatMessage
{
    int sender_id;
    std::string text;

    ChatMessage(int id,const std::string& msg):sender_id(id),text(msg){}

};

#endif