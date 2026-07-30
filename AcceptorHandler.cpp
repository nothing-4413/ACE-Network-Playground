#include "AcceptorHandler.h"
#include "ClientHandler.h"

#include <ace/Reactor.h>

#include <iostream>

AcceptorHandler::AcceptorHandler(unsigned short port):port(port),listen_addr_(port){}

int AcceptorHandler::open()
{
    if(acceptor_.open(listen_addr_,1)==-1)
    {
        std::cerr << "listen failed on port " << port_ << std::endl;
        return -1;
    }

    std::cout << "server listening on port " << port_ << std::endl;
    return 0;
}

ACE_HANDLE AcceptorHandler::get_line()const
{
    return acceptor_.getline();
}

int AcceptorHandler::handle_input(ACE_HANDLE fd)
{
    ACE_SOCK_Stream client_stream;
    ACE_INET_Addr client_addr;

    if(acceptor_.accept(client_stream,&client_addr)==-1)
    {
        std::cerr<<"accept falied"<<std::endl;
        return 0;
    }

    char addr_text[256]={0};
    client_addr.addr_to_string(addr_text,sizeof(addr_text));

    std::cout<<"client connected:"<<addr_text<<std::endl;

    ClientHandler* client_handler = new ClientHandler(client_stream);

    if(ACE_Reactor::instance()->register_handler(client_handler,ACE_Event_Handler::READ_MASK)==-1)
    {
        std::cerr<<"register client handler failed"<<std::endl;
        client_stream.close();
        delete client_handler;
    }
    return 0;
}

int AcceptorHandler::handle_close(ACE_HANDLE handle,ACE_Reactor_Mask close_mask)override
{
    acceptor_.close();
    return 0;
}