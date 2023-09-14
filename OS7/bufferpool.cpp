#include "bufferpool.h"

BufferPool::BufferPool(int n, QObject *parent)
    : QObject(parent), m_size(n) {}

bool BufferPool::storeMessage(const QString &msg) {
    if (m_messages.size() < m_size) {
        m_messages.enqueue(msg);
        return true;
    }
    return false;
}

QString BufferPool::fetchMessage() {
    if (!m_messages.isEmpty()) {
        return m_messages.dequeue();
    }
    return QString();
}
