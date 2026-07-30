#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <ace/Event_Handler.h>
#include <ace/SOCK_Stream.h>

// ClientHandler 代表“一个客户端连接”。
//
// 在 ACE Reactor 模型里：
// 一个 socket 通常对应一个 ACE_Event_Handler。
class ClientHandler : public ACE_Event_Handler
{
public:
    explicit ClientHandler(ACE_SOCK_Stream stream);

    // Reactor 通过 get_handle() 获取这个 handler 关心的 socket。
    ACE_HANDLE get_handle() const override;

    // 当客户端 socket 可读时，Reactor 调用 handle_input()。
    int handle_input(ACE_HANDLE handle) override;

    // 当连接关闭、出错、handler 被移除时，Reactor 调用 handle_close()。
    int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask) override;

private:
    ACE_SOCK_Stream stream_;
};

#endif