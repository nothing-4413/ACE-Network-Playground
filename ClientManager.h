#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <ace/Thread_Mutex.h>

#include <set>
#include <string>

class ClientHandler;

class ClientManger
{
    public:
        void add(ClientHandler* client);
        void remove(ClientHandler* client);

        void broadcast_except(int sender_id,const std::string& message);
        
        int count()const;
    private:
    mutable ACE_Thread_Mutex mutex_;
        std::set<ClientHandler*> clients_;
};

#endif