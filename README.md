# ACE Network Playground

一个用于学习 C++ ACE 网络库的小型分模块项目。

项目从最简单的 TCP Echo Server 开始，逐步引入 Reactor、Handler 拆分、连接管理、广播聊天室和工作线程模型，帮助理解 ACE 的常见使用方式。

## 学习目标

- 使用 `ACE_SOCK_Acceptor` 编写 TCP 服务端
- 使用 `ACE_SOCK_Connector` 编写 TCP 客户端
- 使用 `ACE_SOCK_Stream` 收发 TCP 数据
- 使用 `ACE_Reactor` 实现事件驱动
- 使用 `ACE_Event_Handler` 封装 socket 事件
- 使用 `ACE_Task` 分离网络 IO 和业务处理

## 模块说明

### module_01_blocking_echo

阻塞式 Echo Server。

重点理解：

```text
ACE_INET_Addr
ACE_SOCK_Acceptor
ACE_SOCK_Connector
ACE_SOCK_Stream
```

这一模块用于理解 ACE 对 TCP socket 的基础封装。

### module_02_reactor_echo

Reactor 版 Echo Server。

重点理解：

```text
ACE_Reactor
ACE_Event_Handler
handle_input()
handle_close()
```

这一模块把阻塞式 `accept()` / `recv()` 改成事件驱动模型。

### module_03_acceptor_handler

拆分 Acceptor 和 ClientHandler。

重点理解：

```text
AcceptorHandler 处理新连接
ClientHandler 处理客户端数据
```

这是 ACE 网络程序中很常见的代码组织方式。

### module_04_connection_manager

加入连接管理器。

重点理解：

```text
ClientManager
add()
remove()
count()
```

这一模块用于管理多个在线客户端连接。

### module_05_broadcast_chat

实现多客户端广播聊天室。

重点理解：

```text
客户端发送消息
服务端遍历在线客户端
消息广播给其他客户端
```

这一模块把连接管理真正用起来。

### module_06_task_worker

加入 `ACE_Task` 工作线程。

重点理解：

```text
Reactor 线程负责网络 IO
WorkerTask 线程负责业务处理
ACE_Message_Block 在线程之间传递消息
```

这一模块用于理解 ACE 的异步任务模型。

## 推荐学习顺序

```text
01 阻塞式 TCP
02 Reactor 事件驱动
03 Handler 职责拆分
04 客户端连接管理
05 广播聊天室
06 ACE_Task 工作线程
```

## 编译方式

每个模块都可以单独编译：

```bash
cmake -S . -B build
cmake --build build
```

运行时先启动服务端，再启动客户端：

```bash
./build/server
./build/client
```

Windows 下可执行文件通常在：

```text
build/Debug/server.exe
build/Debug/client.exe
```

## 核心理解

ACE 网络编程的主线可以概括为：

```text
ACE_SOCK_* 负责封装 socket
ACE_Event_Handler 负责封装事件处理逻辑
ACE_Reactor 负责分发 IO 事件
ACE_Task 负责异步业务处理
```

学完这些模块后，应能读懂一个基础 ACE TCP 服务端的结构。

