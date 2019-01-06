#include "getdatathread.h"

GetDataThread::GetDataThread()
{

}

void GetDataThread::run()
{
    if(SWITCH)qDebug()<< "GetDataThread is running...";
    while(1){
        if(toReceive.available() == BUFFER_SIZE){
            mutex.lock();
            buffer_empty.wait(&mutex);
            mutex.unlock();
        }
        toGetData.acquire();
        mutex2.lock();
        if(SWITCH)qDebug()<< "g mutex2.lock()";
        QVariantMap msg;
        if(queueData.size() > 0){
            msg = queueData.last();
            queueData.pop_back();
        }
        mutex2.unlock();
        toReceive.release();
        buffer_full.wakeAll();
        emit dataGeted(msg);
        if(SWITCH)qDebug()<< "[G]queueData.size=" << queueData.size();

        //一秒获取一次数据，也可不用
        //sleep(1);
    }
}
