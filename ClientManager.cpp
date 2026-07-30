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

void ClientManager::count(ClientHandler* client)
{
    return static_cast<int>(clients_.size());
}