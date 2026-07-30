#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <ace/Event_Handler.h>
#include <ace/SOCK_Stream.h>

#include<string>

class ClientManager;
class WorkerTask;

class ClientHandler : public ACE_Event_Handler
{
public:
    ClientHandler(ACE_SOCK_Stream stream,ClientManager& manager,WorkerTask& worker,int id);


    // Reactor 通过 get_handle() 获取这个 handler 关心的 socket。
    ACE_HANDLE get_handle() const override;

    // 当客户端 socket 可读时，Reactor 调用 handle_input()。
    int handle_input(ACE_HANDLE handle) override;

    // 当连接关闭、出错、handler 被移除时，Reactor 调用 handle_close()。
    int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask) override;

    int id() const;
    
    bool send_messager(const std::string& message);

private:
    ACE_SOCK_Stream stream_;
    ClientManager& manager_;
    WorkerTask& worker_;
    int id_;
};

#endif