#include<ace/INET_Addr.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Stream.h>
#include <ace/OS_NS_string.h>

#include<iostream>

int main()
{
    const unsigned short port = 9000;
    const int buffer_size = 4096;

    ACE_INET_Addr listen_addr(port);

    ACE_SOCK_Acceptor acceptor;

    if(acceptor.open(listen_addr,1)==-1)
    {
        std::cerr<<"listen failed"<<std::endl;
        return 1;
    }
    
    std::cout<<"server listening on port"<<port<<std::endl;

    while(true)
    {
        ACE_SOCK_Stream client_stream;
        ACE_INET_Addr client_addr;
        
        std::cout<<"waiting for client..."<<std::endl;

        if(acceptor.accept(client_stream,&client_addr)==-1)
        {
            std::cerr<<"accept falied"<<std::endl;
            continue;
        }

        std::cout<<"client connected"<<std::endl;

        char buffer[buffer_size];

        while(true)
        {
            ACE_OS::memset(buffer,0,sizeof(buffer));

            ssize_t n = client_stream.recv(buffer,sizeof(buffer)-1);
            
            if(n>0)
            {
                std::cout << "recevied:"<<buffer<<std::endl;

                if(client_stream.send_n(buffer,n)!=n)
                {
                    std::cerr<<"send failed"<<std::endl;
                    break;
                }
            }
            else if(n==0)
            {
                std::cout<<"client disconnected" <<std::endl;
                break;
            }
            else
            {
                std::cerr<"recv failed"<<std::endl;
                break;
            }
        }
        clien_stream.close();
    }
    return 0;
}
