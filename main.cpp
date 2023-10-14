#include <QCoreApplication>
#include <QSemaphore>
#include <QThread>
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<int> values;
    values.resize(10);
    values.fill(0);

    QSemaphore sema(values.size());
    qInfo()<<values;

    QThread thread1;
    QThread thread2;
    thread1.setObjectName("Thread 1");
    thread2.setObjectName("Thread 2");

    worker worker1(&sema, &values);
    worker worker2(&sema, &values);
    worker1.moveToThread(&thread1);
    worker2.moveToThread(&thread2);

    QObject::connect(&thread1, &QThread::started, &worker1, &worker::run);
    QObject::connect(&thread2, &QThread::started, &worker2, &worker::run);

    thread1.start();
    thread2.start();

    return a.exec();
}
