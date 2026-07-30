#ifndef WORKER_TASK_H
#define WORKER_TASK_H

#include <ace/Task.h>

#include <string>

class ClientManager;

class WorkerTask:public ACE_Task<ACE_MT_SYNCH>
{
    public:
        explicit WorkerTask(ClientManager& manager);

        int open();
        int stop();

        int wnqueue_chat_message(int sender_id,const std::string& text);

        int svc()override;
    private:
        ClientManager& manager_;
}

#endif