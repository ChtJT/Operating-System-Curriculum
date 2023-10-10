#ifndef RECEIVER_H
#define RECEIVER_H

#include "bufferpool.h"
#include "semaphoremanager.h"
#include <QObject>

class Receiver : public QObject{
public:
    Receiver(int msgID, SemaphoreManager& semMgr, BufferPool& bufPool);
    QString receiveMessage();

private:
    int messageID;
    SemaphoreManager& semaphoreManager;
    BufferPool& bufferPool;
};

#endif // RECEIVER_H
