#include "AcceptorHandler.h"
#include "ClientManager.h"
#include "WorkerTask.h"

#include <ace/Event_Handler.h>
#include <ace/Reactor.h>

#include <iostream>

int main()
{

    const unsigned short port = 9000;

    ClientManger manager;
    WorkerTask worker(manage)

    if(worker.open()==-1)
    {
        std::cerr<<"start worker failed"<<std::endl;
        return 1;
    }

    AcceptorHandler acceptor_handler(port,manager,worker);

    if(acceptor_handler.open()==-1)
    {
        return 1;
    }

    if(ACE_Reactor::instance()->register_handler(&acceptor_handler,ACE_Event_Handler::READ_MASK)==-1)
    {
        std::cerr<<"register acceptor handler failed"<<std::endl;
        return 1;
    }

    std::cout <<"reactor event loop started"<<std::endl;

    ACE_Reactor::instance()->run_reactor_event_loop();

    worker.stop();

    return 0;
}
