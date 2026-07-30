#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <set>

class ClientHandler;

class ClientManger
{
    public:
        void add(ClientHandler* client);
        void remove(ClientHandler* client);

        int count()const;
    private:
        std::set<ClientHandler*> clients_;
};

#endif