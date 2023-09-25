#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMutex>

// Define the node structure for the linked list
struct MessageNode {
    QString message;
    MessageNode *next;
};

class BufferPool : public QObject{
    Q_OBJECT
public:
    explicit BufferPool(int n, int m);
    ~BufferPool();
    bool getBuffer(MessageNode*& msgNode);
    bool releaseBuffer(MessageNode*& msgNode);
    int getUsedBuffers() const { return usedBuffers; }
signals:
    void bufferChanged(const QString& status);
    void buffersUsedChanged(int usedBuffers);
private:
    int m_size;
    int usedBuffers;
    QMutex mutex;
    MessageNode *head;
    MessageNode *tail;

};

#endif // BUFFERPOOL_H
