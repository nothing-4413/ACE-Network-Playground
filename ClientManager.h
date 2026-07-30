#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <set>
#include <string>

class ClientHandler;

class ClientManger
{
    public:
        void add(ClientHandler* client);
        void remove(ClientHandler* client);

        void broadcast(ClientHandler* sender,const std::string& message);
        
        int count()const;
    private:
        std::set<ClientHandler*> clients_;
};

#endif