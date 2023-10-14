#include "worker.h"

worker::worker(QSemaphore *sema, QList<int> *values, QObject *parent)
    : QObject{parent}
{
    m_sema = sema;
    m_values = values;
}

void worker::run()
{
    qInfo()<<"Run" <<QThread::currentThread();
    int max = QRandomGenerator::global()->bounded(1, m_values->size());
    qInfo()<<"gettting" <<max<<QThread::currentThread();

    m_sema->acquire(max);
    qInfo()<<"Aquired"<<m_sema->available()<<QThread::currentThread();
    for(int i =0; i<max; i++){
        qInfo()<<"modify"<<i<<QThread::currentThread();
        int value = QRandomGenerator::global()->bounded(100);
        m_values->replace(i, value);
    }

    qInfo()<<"release"<<max<<QThread::currentThread();

    m_sema->release(max);
}

