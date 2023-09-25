#include "receiver.h"
#include <QThread>

Receiver::Receiver(BufferPool* pool, SemaphoreManager* semaphore, QObject *parent)
    : QObject(parent), m_bufferPool(pool), semaphoreManager(semaphore) {}

void Receiver::receive() {
    while (shouldRun) {
        semaphoreManager->P();

        MessageNode* msgNode = nullptr;
        if (m_bufferPool->getBuffer(msgNode) && msgNode) {
            emit messageReceived(msgNode->message,10);
            m_bufferPool->releaseBuffer(msgNode);
        }

        semaphoreManager->V();

        // Simulate a delay in receiving the message
        QThread::sleep(1);
    }
}
