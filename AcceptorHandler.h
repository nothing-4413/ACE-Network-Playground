#ifndef ACCEPTOR_HANDLER_H
#define ACCEPTOR_HANDLER_H

#include <ace/Event_Handler.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Acceptor.h>

// AcceptorHandler 代表“服务端监听 socket”。
//
// 它不负责处理客户端消息。
// 它只做一件事：
// 有新连接来时 accept，然后创建 ClientHandler。
class AcceptorHandler : public ACE_Event_Handler
{
public:
    explicit AcceptorHandler(unsigned short port);

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
};

#endif