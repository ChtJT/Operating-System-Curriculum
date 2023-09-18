#include "receiver.h"
#include "semaphoremanager.h"
#include <QRandomGenerator>
#include <QDebug>

Receiver::Receiver(BufferPool *bufferPool, QObject *parent)
    : QThread(parent), m_bufferPool(bufferPool) {}

void Receiver::onMessageToSend(const QString &msg) {
    Q_UNUSED(msg);

    // Introduce a random delay
    QThread::msleep(QRandomGenerator::global()->bounded(200, 500));

    // Use semaphore for synchronized access
    SemaphoreManager::bufferPoolSemaphore.acquire();
    QString fetchedMsg = m_bufferPool->fetchMessage();
    SemaphoreManager::bufferPoolSemaphore.release();

    if (!fetchedMsg.isEmpty()) {
        qDebug() << "Receiver fetched: " << fetchedMsg;
    }

    // Introduce another random delay
    QThread::msleep(QRandomGenerator::global()->bounded(200, 500));
}
