#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QSemaphore>
#include <QThread>
#include <QRandomGenerator>

class worker : public QObject
{
    Q_OBJECT
public:
    explicit worker(QSemaphore*sema, QList<int> *values ,QObject *parent = nullptr);

signals:
public slots:
    void run();
private:
    QSemaphore *m_sema;
    QList<int> *m_values;
};

#endif // WORKER_H
