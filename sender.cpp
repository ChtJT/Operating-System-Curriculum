#include "sender.h"
#include <QThread>

Sender::Sender(BufferPool* pool, SemaphoreManager* semaphore, QObject *parent)
    : QObject(parent), bufferPool(pool), semaphoreManager(semaphore)
{
}

void Sender::send()
{
    while(shouldRun) {
        semaphoreManager->P();
        MessageNode* msg = nullptr;
        if(bufferPool->getBuffer(msg))
        {
            msg->message = QString("Message from sender %1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
            emit messageSent(msg->message);
            QThread::sleep(1);
            bufferPool->releaseBuffer(msg);
        }
        semaphoreManager->V();
    }
}
