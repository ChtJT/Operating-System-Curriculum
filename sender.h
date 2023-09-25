#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include "bufferpool.h"
#include "semaphoremanager.h"

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(BufferPool* pool, SemaphoreManager* semaphore, QObject *parent = nullptr);

public slots:
    void send();
    void setShouldRun(bool value) { shouldRun = value; }
    void restart() { shouldRun = true; }


signals:
    void messageSent(const QString& message);

private:
    BufferPool* bufferPool;
    SemaphoreManager* semaphoreManager;
    bool shouldRun = true;
};

#endif // SENDER_H
