#include "WorkerTask.h"
#include "ChatMessage.h"
#include "ClientManager.h"

#include <ace/Message_Block.h>

#include <iostream>
#include <sstream>

WorkerTask::WorkerTask(ClientManager& manager):manager_(manager){}

int WorkerTask::open()
{
    return this->activate();
}

int WorkerTask::stop()
{
    ACE_Message_Block* stop_msg = new ACE_Message_Block(0);
    this->putq(stop_msg);

    return this->wait();
}

int WorkerTask::enqueue_chat_message(int sender_id,const std::string& text)
{
    ChatMessage* chat = new ChatMessage(send_id,text);

    ACE_Message_Block* block = new ACE_Message_Block(sizeof(ChatMessage*));

    *reinterpret_cast<ChatMessage**>(block->wr_ptr()) = chat;
    block->wr_ptr(sizeof(ChatMessage));

    return this->putq(block);
}

int WorkerTask::svc()
{
    std::cout<<"worker thread started"<<std::endl;

    while(true)
    {
        ACE_Message_Block* block = 0;

        if(this->getq(block)==-1)
        {
            continue;
        }

        if(block->length()==0)
        {
            block->release();
            break;
        }

        ChatMessage* chat = *reinterpret_cast<ChatMessage**>(block->rd_ptr());

        std::ostringstream out;
        out<<"client #"<<chat->sender_id<<":"<<chat->text;

        manager_.broadcast_except(chat->sender_id,out.str());

        delete chat;
        block->release();
    }

    std::cout<<"worker thread stopped"<<std::endl;
    return 0;
}