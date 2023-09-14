#ifndef SENDER_H
#define SENDER_H

#include <QThread>
#include "bufferpool.h"
#include "semaphoremanager.h"

class Sender : public QThread {
    Q_OBJECT

public:
    explicit Sender(BufferPool *bufferPool, int id, QObject *parent = nullptr);

    void run() override;

signals:
    void messageToSend(const QString &msg);

private:
    BufferPool *m_bufferPool;
    int m_id;
};

#endif // SENDER_H
