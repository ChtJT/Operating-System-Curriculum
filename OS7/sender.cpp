#include "sender.h"
#include <QRandomGenerator>

Sender::Sender(BufferPool *bufferPool, int id, QObject *parent)
    : QThread(parent), m_bufferPool(bufferPool), m_id(id) {}

void Sender::run() {
    while (true) {
        QThread::sleep(QRandomGenerator::global()->bounded(2, 5));

        QString msg = QString("Message from Sender %1").arg(m_id);

        SemaphoreManager::bufferPoolSemaphore.acquire();
        bool success = m_bufferPool->storeMessage(msg);
        SemaphoreManager::bufferPoolSemaphore.release();

        if (success) {
            emit messageToSend(msg);
        }
    }
}
