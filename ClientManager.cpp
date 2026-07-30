#include "ClientManager.h"
#include "ClientHandler.h"

void ClientManager::add(ClientHandler* client)
{
    ACE_Guard<ACE_Thread_Mutex>guard(mutex_);
    client_.insert(client);
}

void ClientManager::remove(ClientHandler* client)
{
    ACE_Guard<ACE_Thread_Mutex>guard(mutex_);
    client_.erase(client);
}

void ClientManager::broadcast(int sender_id,const std::string& message)
{
    for(ClientHandler* client:clients_)
    {
        if(client->id()!=sender_id)
        {
            client->send_message(message);
        }
    }
}

void ClientManager::count(ClientHandler* client)
{
    ACE_Guard<ACE_Thread_Mutex>guard(mutex_);
    return static_cast<int>(clients_.size());
}