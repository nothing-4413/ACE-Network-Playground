#include "ClientHandler.h"

#include <ace/OS_NS_string.h>

#include <iostream>

namespace
{
    const int BUFFER_SIZE = 4096:
}

ClientHandler::ClientHandler(ACE_SOCK_Stream stream):stream_(stream){}

ACE_HANDLE ClientHandler::get_handle()const
{
    return stream_.get_handle();
}

int ClientHandler::handle_input(ACE_HANDLE handle)
{
    char buffer[BUFFER_SIZE];
    ACE_OS::memset(buffer,0,sizeof(buffer));

    ssize_t n = stream.recv(buffer,sizeof(buffer)-1);
    
    if(n>0)
    {
        std::cout << "recevied:"<<buffer<<std::endl;

        if(stream_.send_n(buffer,n)!=n)
        {
            std::cerr<<"send failed"<<std::endl;
            return -1;
        }
        return 0;
    }
    if(n==0)
    {
        std::cout<<"client disconnected" <<std::endl;
    }
    else
    {
        std::cerr<"recv failed"<<std::endl;
    }
    return -1;
}

int ClientHandler::handle_close(ACE_HANDLE handle,ACE_Reactor_Mask close_mask)
{
    std::cout<<"closing client handler"<<std::endl;

    stream_.close()

    delete this;
    
    return 0;
}
