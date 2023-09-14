#include "receiver.h"

Receiver::Receiver(BufferPool *bufferPool, QObject *parent)
    : QThread(parent), m_bufferPool(bufferPool) {}

void Receiver::run() {
    exec();
}

void Receiver::onMessageToSend(const QString &msg) {
    Q_UNUSED(msg)
    SemaphoreManager::bufferPoolSemaphore.acquire();
    QString fetchedMsg = m_bufferPool->fetchMessage();
    SemaphoreManager::bufferPoolSemaphore.release();

    if (!fetchedMsg.isEmpty()) {
        // Process the message as required
        qDebug() << "Received:" << fetchedMsg;
    }
}
