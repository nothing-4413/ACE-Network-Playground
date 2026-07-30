#include "ClientHandler.h"
#include "ClientManager.h"
#include "WorkerTask.h"

#include <ace/OS_NS_string.h>

#include <iostream>
#include <sstream>

namespace
{
    const int BUFFER_SIZE = 4096:
}

ClientHandler::ClientHandler(ACE_SOCK_Stream stream,ClientManager& manager,WorkerTask& worker,int id):stream_(stream),manager_(manager),worker_(worker),id_(id){}

ACE_HANDLE ClientHandler::get_handle()const
{
    return stream_.get_handle();
}

int ClientHandler::id()const
{
    return id_;
}

bool ClientHandler::send_message(const std::string& message)
{
    return stream_.send_n(message.data(),message.size())==static_cast<ssize_t>(message.size());
}

int ClientHandler::handle_input(ACE_HANDLE handle)
{
    char buffer[BUFFER_SIZE];
    ACE_OS::memset(buffer,0,sizeof(buffer));

    ssize_t n = stream.recv(buffer,sizeof(buffer)-1);
    
    if(n>0)
    {
        std::string text(buffer,static_cast<std::size_t>(n));

        std::cout << "client #" << id_ << " says: " << buffer << std::endl;
        
        worker_.enqueue_chat_message(id_,text);

        send_message("[server] message queued\n");

        return 0;
    }
    if(n==0)
    {
        std::cout<<"client #" <<id_<<"disconnected"<<std::endl;
    }
    else
    {
        std::cerr<"recv failed for client #"<<id_<<std::endl;
    }
    return -1;
}

int ClientHandler::handle_close(ACE_HANDLE handle,ACE_Reactor_Mask close_mask)
{
    std::cout<<"closing client #"<<id_<<std::endl;
    
    manager_.remove(this);
    
    std::ostringstream out;
    out<<"[server] client #"<<id_<<"left,online clients:"<<message_.count()-1<<"\n";
    
    manager_.broadcast(id_,out.str());
    
    stream_.close()

    delete this;
    
    return 0;
}
