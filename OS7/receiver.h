#ifndef RECEIVER_H
#define RECEIVER_H

#include <QThread>
#include <QDebug>
#include "bufferpool.h"
#include "semaphoremanager.h"

class Receiver : public QThread {
    Q_OBJECT

public:
    explicit Receiver(BufferPool *bufferPool, QObject *parent = nullptr);

    void run() override;

public slots:
    void onMessageToSend(const QString &msg);

private:
    BufferPool *m_bufferPool;
};

#endif // RECEIVER_H
