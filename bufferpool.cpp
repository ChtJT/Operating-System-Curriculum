#include "bufferpool.h"

BufferPool::BufferPool(int n, QObject *parent)
    : QObject(parent), m_size(n), m_count(0), head(nullptr), tail(nullptr) {}

BufferPool::~BufferPool() {
    while (head) {
        MessageNode *temp = head;
        head = head->next;
        delete temp;
    }
}

bool BufferPool::storeMessage(const QString &msg) {
    if (m_count >= m_size) {
        return false;
    }

    MessageNode *node = new MessageNode{msg, nullptr};
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }

    m_count++;
    return true;
}

QString BufferPool::fetchMessage() {
    if (!head) {
        return QString();
    }

    MessageNode *temp = head;
    QString msg = temp->message;
    head = head->next;
    if (!head) {
        tail = nullptr;
    }

    delete temp;
    m_count--;
    return msg;
}
