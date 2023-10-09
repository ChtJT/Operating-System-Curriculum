#include <QApplication>
#include "mainwindow.h"
#include "sender.h"
#include "receiver.h"
#include "semaphoremanager.h"
#include "bufferpool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建必要的对象
    SemaphoreManager semMgr;
    BufferPool bufPool;
    Sender sender(2, semMgr, bufPool);
    Receiver receiver(2, semMgr, bufPool);


    MainWindow w(sender, receiver);
    w.show();

    return a.exec();
}
