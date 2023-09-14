#ifndef SEMAPHOREMANAGER_H
#define SEMAPHOREMANAGER_H

#include <QSemaphore>

class SemaphoreManager {
public:
    static QSemaphore bufferPoolSemaphore;
};

#endif // SEMAPHOREMANAGER_H
