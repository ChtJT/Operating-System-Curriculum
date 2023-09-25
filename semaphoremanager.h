#ifndef SEMAPHOREMANAGER_H
#define SEMAPHOREMANAGER_H

#include <QSemaphore>

class SemaphoreManager {
public:
    SemaphoreManager(int value=1);
    ~SemaphoreManager();
    void P();
    void V();
private:
    QSemaphore semaphore;

};

#endif // SEMAPHOREMANAGER_H
