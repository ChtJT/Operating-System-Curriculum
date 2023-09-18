#include "sender.h"
#include "semaphoremanager.h"
#include <QRandomGenerator>
#include <QDebug>

Sender::Sender(BufferPool *bufferPool, int id, QObject *parent)
    : QThread(parent), m_bufferPool(bufferPool), m_id(id) {}

void Sender::run() {
    while (true) {
        // Introduce a random delay
        QThread::msleep(QRandomGenerator::global()->bounded(200, 500));

        QString msg = QString("Message from Sender %1").arg(m_id);

        // Use semaphore for synchronized access
        SemaphoreManager::bufferPoolSemaphore.acquire();
        bool stored = m_bufferPool->storeMessage(msg);
        SemaphoreManager::bufferPoolSemaphore.release();

        if (stored) {
            emit messageToSend(msg);
        }

        // Introduce another random delay
        QThread::msleep(QRandomGenerator::global()->bounded(200, 500));
    }
}
