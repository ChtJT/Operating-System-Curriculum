#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include "bufferpool.h"
#include "semaphoremanager.h"

class Receiver : public QObject {
    Q_OBJECT

public:
    explicit Receiver(BufferPool* pool, SemaphoreManager* semaphore, QObject *parent = nullptr);

    //void run() override;

signals:
    void messageReceived(const QString& message, int poolNumber);

public slots:
    void receive();
    void setShouldRun(bool value) { shouldRun = value; }
    void restart() { shouldRun = true; }

private:
    BufferPool *m_bufferPool;
    SemaphoreManager *semaphoreManager;
    bool shouldRun = true;

};

#endif // RECEIVER_H
