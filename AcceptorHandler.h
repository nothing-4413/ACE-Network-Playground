#ifndef ACCEPTOR_HANDLER_H
#define ACCEPTOR_HANDLER_H

#include <ace/Event_Handler.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Acceptor.h>

class ClientManager;
class WorkerTask;

class AcceptorHandler : public ACE_Event_Handler
{
public:
    AcceptorHandler(unsigned short port,ClientManager& manager,WorkerTask& worker);

    int open();

    // Reactor 通过这个函数拿到监听 socket。
    ACE_HANDLE get_handle() const override;

    // 对监听 socket 来说，可读事件表示“有新连接”。
    int handle_input(ACE_HANDLE handle) override;

    int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask) override;

private:
    unsigned short port_;
    ACE_INET_Addr listen_addr_;
    ACE_SOCK_Acceptor acceptor_;
    ClientManager manager_;
    WorkerTask& worker_;
    int next_client_id_;
};

#endif