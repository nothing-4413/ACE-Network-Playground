#include "ClientManager.h"
#include "ClientHandler.h"

void ClientManager::add(ClientHandler* client)
{
    client_.insert(client);
}

void ClientManager::remove(ClientHandler* client)
{
    client_.erase(client);
}

void ClientManager::broadcast(ClientHandler* sender,const std::string& message)
{
    for(ClientHandler* client:clients_)
    {
        if(client!=sender)
        {
            client->send_message(message);
        }
    }
}

void ClientManager::count(ClientHandler* client)
{
    return static_cast<int>(clients_.size());
}