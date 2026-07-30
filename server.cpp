#include<ace/INET_Addr.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Stream.h>
#include <ace/Event_Handler.h>
#include <ace/Reactor.h>
#include <ace/OS_NS_string.h>

#include<iostream>

const unsigned short PORT = 9000;
const int BUFFER_SIZE = 4096;

class ClientHandler:public ACE_Event_Handler
{
    public:
        explicit ClientHandler(ACE_SOCK_Stream stream):stream_(stream){}

        ACE_HANDLE get_handle()const override
        {
            return stream_.get_handle();
        }

        int handle_input(ACE_HANDLE fd)override
        {
            char buffer[BUFFER_SIZE];
            ACE_OS::memset(buffer,0,sizeof(buffer));

            ssize_t n = stream.recv(buffer,sizeof(buffer)-1);
            
            if(n>0)
            {
                std::cout << "recevied:"<<buffer<<std::endl;

                if(stream.send_n(buffer,n)!=n)
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

        int handle_close(ACE_HANDLE handle,ACE_Reactor_Mask close_mask)override
        {
            std::cout<<"closing client handler"<<std::endl;

            stream_.close()

            delete this;
            
            return 0;
        }
    private:
        ACE_SOCK_Stream stream_;
};

class AcceporHandler : public ACE_Event_Handler
{
    public:
        explicit AcceptorHandler(unsigned short port):listen_addr_(port){}

        int open()
        {
            if(acceptor.open(listen_addr_,1)==-1)
            {
                std::cerr<<"failed to listen"<<std::endl;
                return 1;
            }

            std::cout<<"reactor echo server listening on port"<<PORT<<std::endl;
            return 0;
        }

        ACE_HANDLE get_line()const override
        {
            return acceptor_.getline();
        }

        inr handle_input(ACE_HANDLE fd)override
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
        
        int handle_close(ACE_HANDLE handle,ACE_Reactor_Mask close_mask)override
        {
            acceptor_.close();
            return 0;
        }
    private:
        ACE_INET_Addr listen_addr_;
        ACE_SOCK_Acceptor acceptor_;
};

int main()
{

    AcceptorHandler acceptor_handler(PORT);

    if(acceptor_handler.open()==-1)
    {
        return 1;
    }
    
    if(ACE_Reactor::instance()->register_handler(&acceptor_handler,ACE_Event_Handlerd::READ_MASK)==-1)
    {
        std::cerr<<"register acceptor handler failed"<<std::endl;
        return 1;
    }

    std::cout<<"event loop started"<<std::endl;

    ACE_Reactor::instance()->run_reactor_event_loop();
    
    return 0;
}
