#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <QObject>
#include <QString>

// Define the node structure for the linked list
struct MessageNode {
    QString message;
    MessageNode *next;
};

class BufferPool : public QObject {
    Q_OBJECT
public:
    explicit BufferPool(int n, QObject *parent = nullptr);
    ~BufferPool();

    bool storeMessage(const QString &msg);
    QString fetchMessage();

private:
    int m_size;
    int m_count;
    MessageNode *head;
    MessageNode *tail;
};

#endif // BUFFERPOOL_H
