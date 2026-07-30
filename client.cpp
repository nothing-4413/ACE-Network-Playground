#include <ace/INET_Addr.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <ace/OS_NS_string.h>

#include<iostream>
#include<string>

int main()
{
    const unsigned short port = 9000;
    const char* host = "127.0.0.1";
    const int buffer_size = 4096;

    ACE_INET_Addr server_addr(port,host);

    ACE_SOCK_Connectpr connector;

    ACE_SOCK_Stream stream;

    if(connector.connect(stream,server_addr)==-1)
    {
        std::cerr<<"connect failed"<<std::endl;
        return 1;
    }

    std::cout<<"connected to server"<<std::endl;
    std::cout<<"type text,or type quit to exit"<<std::endl;

    std::string line;
    char buffer[buffer_size];

    while(std::getline(std::cin,line))
    {
        if(line=="quit")
        {
            break;
        }

        line+="\n";

        if(stream.send_n(line.data(),line.size())!=static_cast<ssize_t>(line.size()))
        {
            std::cerr<<"send failed"<<std::endl;
            break;
        }

        ACE_OS::memset(buffer,0,sizeof(buffer));

        ssize_t n =stream.recv(buffer,sizeof(buffer)-1);

        if(n>0)
        {
            std::cout<<"echo:"<<buffer;
        }
        else if(n==0)
        {
            std::cout<<"server closed connection"<<std::endl;
            break;
        }
        else
        {
            std::cerr<"recv failed"<<std::endl;
            break;
        }
    }
    stream.close();
    return 0;
}