#include "MainWin.h"
#include "ui_MainWin.h"

#include <QMouseEvent>
#include <QPoint>
#include <qDebug>
#include <QDesktopWidget>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include "login.h"
#include "dictionary.h"
#include "word.h"
#include <windows.h>
#include <QCoreApplication>
#include <QTime>
using namespace std;

extern Dictionary *Dic;
extern Caretaker *Care;
extern int status;
extern int used;
QSemaphore toReceive;
QSemaphore toGetData;
QQueue<QVariantMap> queueData;
QWaitCondition buffer_full;
QWaitCondition buffer_empty;

QMutex    mutex1;
QMutex     mutex2;


//延时函数
void waitSec(float s)
{
    QTime t;
    t.start();
    while(t.elapsed()<1000*s)
        QCoreApplication::processEvents();
}

//自定义随机函数。为了保证背单词模式下四个单词是不一样的
int Random(int a,int b, int c,int WordNum)
{   qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int n = qrand()%WordNum;
    while(n==a || n==b ||n==c)
    {  n=qrand()%WordNum;
     }
    return n;
}

//刷新学习界面
void MainWin::RefreshLearn()
{
    ui->Word_btn->setStyleSheet("background-color: rgb(105,105,105,150)");

    ui->ChoiceA_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->ChoiceB_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->ChoiceC_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->ChoiceD_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->label_5->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->label_6->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->label_9->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->label_10->setStyleSheet("background-color: rgb(105,105,105,150)");

    ui->Prompt_Lb->setText("");
    ui->Back_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->Collect_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->EasyWord_btn->setStyleSheet("background-color: rgb(105,105,105,150)");

    ui->Word_btn->setText(Dic->word[CurWord]->get_english());
    ui->WordNum_LE->setText(QString::number(CurWord));

    ui->WordNum_LE->setStyleSheet("background-color: rgb(105,105,105,100)");
    ui->Correctrate_LE->setStyleSheet("background-color: rgb(105,105,105,100)");
    ui->Rank_LE->setStyleSheet("background-color: rgb(105,105,105,100)");

    float rate;
    if(CurWord==0)
        rate=0;
    else
        rate=(float(CorrectNum)/float(CurWord))*100;

    ui->Correctrate_LE->setText(QString::number(rate)+"%");
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int a = qrand()%3;   //随机生成0到3的随机数
    if(a==0){
       ui->ChoiceA_btn->setText(Dic->word[CurWord]->get_chinese());
       int b=Random(CurWord,CurWord,CurWord,Dic->Wordnum);
       ui->ChoiceB_btn->setText(Dic->word[b]->get_chinese());
       int c=Random(CurWord,b,b,Dic->Wordnum);
       ui->ChoiceC_btn->setText(Dic->word[c]->get_chinese());
       int d=Random(CurWord,b,c,Dic->Wordnum);
       ui->ChoiceD_btn->setText(Dic->word[d]->get_chinese());
      }
    else if(a==1){
       ui->ChoiceB_btn->setText(Dic->word[CurWord]->get_chinese());
       int a=Random(CurWord,CurWord,CurWord,Dic->Wordnum);
       ui->ChoiceA_btn->setText(Dic->word[a]->get_chinese());
       int c=Random(CurWord,a,a,Dic->Wordnum);
       ui->ChoiceC_btn->setText(Dic->word[c]->get_chinese());
       int d=Random(CurWord,a,c,Dic->Wordnum);
       ui->ChoiceD_btn->setText(Dic->word[d]->get_chinese());
      }
    else if(a==2){
       ui->ChoiceC_btn->setText(Dic->word[CurWord]->get_chinese());
       int a=Random(CurWord,CurWord,CurWord,Dic->Wordnum);
       ui->ChoiceA_btn->setText(Dic->word[a]->get_chinese());
       int b=Random(CurWord,a,a,Dic->Wordnum);
       ui->ChoiceB_btn->setText(Dic->word[b]->get_chinese());
       int d=Random(CurWord,a,b,Dic->Wordnum);
       ui->ChoiceD_btn->setText(Dic->word[d]->get_chinese());
      }
    else if(a==3){
        ui->ChoiceD_btn->setText(Dic->word[CurWord]->get_chinese());
        int a=Random(CurWord,CurWord,CurWord,Dic->Wordnum);
        ui->ChoiceA_btn->setText(Dic->word[a]->get_chinese());
        int b=Random(CurWord,a,a,Dic->Wordnum);
        ui->ChoiceB_btn->setText(Dic->word[b]->get_chinese());
        int c=Random(CurWord,a,b,Dic->Wordnum);
        ui->ChoiceC_btn->setText(Dic->word[c]->get_chinese());
    }

}

//刷新复习界面
void MainWin::RefreshReview()
{   ui->WordAnswer_Lb->setStyleSheet("background-color: rgb(255,255,255)");
    ui->TestWord_Lb->setText(Dic->word[CurWord]->get_chinese());
    ui->WordAnswer_Lb->setText("");
    ui->WordAnswer_Lb->setStyleSheet("background-color: rgb(0,0,0,0)");
    ui->InputAnswer_LE->setText("");
    ui->ViewAnswer_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->NextWord_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->Back_btn_2->setStyleSheet("background-color: rgb(105,105,105,150)");

}

//刷新进入界面
void MainWin::RefreshEnter()
{
    if(status==1){
        ui->ConnSta_Lb->setText("在线");
    }
    else{
        ui->ConnSta_Lb->setText("离线");
    }

    ui->menu_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->Search_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->logiin_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->Learn_btn->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->Review_btn->setStyleSheet("background-color: rgb(105,105,105,150)");

}

//刷新搜索界面
void MainWin::RefreshSearch()
{   
    ui->Search_LE->setStyleSheet("background-color: rgb(105,105,105,150)");
    //ui->Search_LE->setStyleSheet("color:white");
    ui->listWidget->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->Search_btn_2->setStyleSheet("background-color: rgb(105,105,105,150)");
    ui->Backmenu_btn->setStyleSheet("background-color: rgb(105,105,105,150)");


}

//界面初始化函数
void MainWin::InitUI()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->page->setObjectName("p1");
    ui->page->setStyleSheet("#p1{border-image:url(:/background.png)}");

    ui->page_2->setObjectName("p2");
    ui->page_2->setStyleSheet("#p2{border-image:url(:/learnPic.png)}");

    ui->page_7->setObjectName("p3");
    ui->page_7->setStyleSheet("#p3{border-image:url(:/reviewPic.png)}");

    ui->page_3->setObjectName("p4");
    ui->page_3->setStyleSheet("#p4{border-image:url(:/searchPic.png)}");

    RefreshEnter();
    RefreshLearn();
    RefreshReview();
    RefreshSearch();

}


MainWin::MainWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
    //定时器初始化
    InitUI();
    TimerInit();
    Dic->Initial();

}

MainWin::~MainWin()
{
    if(eventData != -1){
        delete receiveThread;
        delete getDataThread;
    }
    delete login;
    delete ui;
}


//-----------------------------------------------------------
//登录槽函数处理
//-----------------------------------------------------------
void MainWin::widgetReceiveSetData(const QString &ip,const QString &port,const QString &nickName)
{
    login->hide();
    this->show();
    this->nickName = nickName;
    //创建接收数据线程
    receiveThread = new ReceiveThread(ip,port,nickName);
    //当打字数据更新时，发送数据更新新号和执行相关槽函数
    connect(this,SIGNAL(updateClientDataSignal(QString)),receiveThread,SLOT(updateClientDataSlot(QString)));
    //当窗口关闭时，发送离线信号给服务端
    connect(this,SIGNAL(closeSignal()),receiveThread,SLOT(closeWidgetSlot()));

    toReceive.release(BUFFER_SIZE);

    receiveThread->start();
    //创建获取数据线程
    getDataThread = new GetDataThread();
    connect(getDataThread,SIGNAL(dataGeted(QVariantMap)),
            this,SLOT(getDataSlot(QVariantMap)));
    getDataThread->start();
}

//EventData接收槽函数
void MainWin::widgetReceiveEventData(const int &eventData)
{
    if(SWITCH)qDebug()<< eventData;
    this->eventData = eventData;
    if(eventData == -1){
        if(SWITCH)qDebug() << "eventData = -1";
        this->close();
        return ;
    }

}




//----------------------------------------------------------------
//界面事件槽函数
//--------------------------------------------------------------------
void MainWin::on_logiin_btn_clicked()
{   //新建一个登录
    login = new Login();
    login->show();
    connect(login,SIGNAL(loginSendSetData(QString,QString,QString)),this,
            SLOT(widgetReceiveSetData(QString,QString,QString)));
    connect(login,SIGNAL(loginSendEventData(int)),this,
            SLOT(widgetReceiveEventData(int)));

}

void MainWin::on_Learn_btn_clicked()
{   RefreshLearn();
    ui->stackedWidget->setCurrentIndex(1);
    if(used==1){
        Dic->restoreMemento(Care->getMemento());
        qDebug()<<"Dic->LearnNum:"<<Dic->get_LearnNum()<<"CurWord"<<CurWord;
        CurWord=Dic->get_LearnNum();
    }
    else
        used=1;
}


void MainWin::on_Review_btn_clicked()
{   RefreshReview();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWin::on_Back_btn_clicked()
{
    Care=new Caretaker;
    Memento *m= Dic->createMemento();
    m->set_state(CurWord);
    Care->setMemento(m);
    qDebug()<<"CurWord:"<<CurWord<<"Care.memento:"<<Care->getMemento().get_state();
    ui->stackedWidget->setCurrentIndex(0);
}

//不认识按钮
void MainWin::on_Abandon_btn_clicked()
{
    ui->Prompt_Lb->setText(Dic->word[CurWord]->get_chinese());
}

//选项A
void MainWin::on_ChoiceA_btn_clicked()
{
    QString s= ui->ChoiceA_btn->text();
    if(s==Dic->word[CurWord]->get_chinese()){//如果正确则设定为绿色
        ui->ChoiceA_btn->setStyleSheet("background-color: rgb(0,255,0,200)");

        waitSec(0.5);//延时0.5s 显示 然后换下一个
        CurWord++;

        CorrectNum++;
        RefreshLearn();
      }
    else{//若选择错误 则设定为红色
        ui->ChoiceA_btn->setStyleSheet("background-color: rgb(255,0,0,200)");

        ui->Prompt_Lb->setText(Dic->word[CurWord]->get_chinese());
        waitSec(0.5);//延时0.5s
        CurWord++;
        RefreshLearn();

    }

}

//选项B  注释同上
void MainWin::on_ChoiceB_btn_clicked()
{
    QString s= ui->ChoiceB_btn->text();
    if(s==Dic->word[CurWord]->get_chinese()){
        ui->ChoiceB_btn->setStyleSheet("background-color: rgb(0,255,0,200)");
        waitSec(0.5);
        CurWord++;
        CorrectNum++;
        RefreshLearn();
      }
    else{
        ui->ChoiceB_btn->setStyleSheet("background-color: rgb(255,0,0,200)");

        ui->Prompt_Lb->setText(Dic->word[CurWord]->get_chinese());
        waitSec(0.5);
        CurWord++;
        RefreshLearn();
    }
}



//选项C
void MainWin::on_ChoiceC_btn_clicked()
{
    QString s= ui->ChoiceC_btn->text();
    if(s==Dic->word[CurWord]->get_chinese()){
        ui->ChoiceC_btn->setStyleSheet("background-color: rgb(0,255,0,200)");
        waitSec(0.5);
        CurWord++;
        CorrectNum++;
        RefreshLearn();
      }
    else{
        ui->ChoiceC_btn->setStyleSheet("background-color: rgb(255,0,0,200)");

        ui->Prompt_Lb->setText(Dic->word[CurWord]->get_chinese());
        waitSec(0.5);
        CurWord++;
        RefreshLearn();
    }

}

//选项D
void MainWin::on_ChoiceD_btn_clicked()
{
    QString s= ui->ChoiceD_btn->text();
    if(s==Dic->word[CurWord]->get_chinese()){
        ui->ChoiceD_btn->setStyleSheet("background-color: rgb(0,255,0,200)");
        waitSec(0.5);
        CurWord++;
        CorrectNum++;
        RefreshLearn();
      }
    else{
        ui->ChoiceD_btn->setStyleSheet("background-color: rgb(255,0,0,200)");

        ui->Prompt_Lb->setText(Dic->word[CurWord]->get_chinese());
        waitSec(0.5);
        CurWord++;
        RefreshLearn();
    }

}

//复习界面槽函数

void MainWin::on_lineEdit_returnPressed()
{
    QString s= ui->InputAnswer_LE->text();
    if(s==Dic->word[CurWord]->get_english()){
        CurWord++;
        RefreshReview();
    }
    else{
        ui->WordAnswer_Lb->setText("The answer is wrong!");
        waitSec(0.5);
        ui->WordAnswer_Lb->setText("");

    }
}

//回到主界面
void MainWin::on_Back_btn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//查看答案按钮
void MainWin::on_ViewAnswer_btn_clicked()
{
    ui->WordAnswer_Lb->setText(Dic->word[CurWord]->get_english());
}

//下一个单词按钮
void MainWin::on_NextWord_btn_clicked()
{
    CurWord++;
    RefreshReview();
}

//计时器
void MainWin::TimerInit()
{
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerHandleSlot()));
    //三秒钟刷新一次
    timer->start(3000);
}

//定时器溢出槽函数
void MainWin::timerHandleSlot()
{   RefreshEnter();
    TimeCount += 3;
    ui->hostname_LE->setText(nickName);
    QDateTime time=QDateTime::currentDateTime();
    QString text=time.toString("hh:mm:ss");
    ui->lcdNumber->display(text);                       //时间
    QString str = tr("%1").arg(CorrectNum);             //正确个数
    QString accuracyStr;
    if(Dic->Wordnum != 0){                                    //正确率
        accuracyStr = str.setNum(((float)CorrectNum/(float)(CurWord))*100,'g',4);
        qDebug()<<CorrectNum<<CurWord<<accuracyStr;

    }
    else {
        accuracyStr = "0.00";
    }

    //发信更新数据信号到接收数据线程，通过线程的client socket将数据传送到服务器上
    QJsonObject json;
    json.insert("Header","DATA");                       //DATA:打字数据，MSG:弹幕信息；CHAT:私聊；LOGIN:登录
    json.insert("name", nickName);                      //My name
    json.insert("to","");                               //与谁私聊，另开端口
    json.insert("speed",CurWord );                     //当前背到的单词数
    json.insert("accuracy",accuracyStr);                //正确率
    json.insert("time",QString::number(TimeCount));     //在线时间(s)
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);
    qDebug()<<json_str;
    emit updateClientDataSignal(json_str);


}

bool MainWin::IsEnglish(QString &qstrSrc)
{
    QByteArray ba = qstrSrc.toLatin1();
    const char *s = ba.data();
    bool bret = true;
    while(*s)
    {
        if((*s>='A' && *s<='Z') || (*s>='a' && *s<='z'))
        {

        }
        else
        {
            bret = false;
            break;
        }
        s++;
    }
    return bret;
}

//输入函数，可以响应键盘事件
void MainWin::on_InputAnswer_LE_returnPressed()
{   QString s=ui->InputAnswer_LE->text();
    if(!IsEnglish(s)){
       QMessageBox::warning(this,("warning"), ("请输入英文！"));
       return;
    }
    if(ui->InputAnswer_LE->text()==Dic->word[CurWord]->get_english()){
        ui->WordAnswer_Lb->setStyleSheet("color:green;");
        ui->WordAnswer_Lb->setText("Correct!");

        waitSec(0.5);//延时
        CurWord++;
        RefreshReview();
    }
    else{
        ui->WordAnswer_Lb->setStyleSheet("color:red;");
        ui->WordAnswer_Lb->setText("Wrong!");
        waitSec(0.5);
        ui->WordAnswer_Lb->setText("");

    }
}

//太简单了 跳过
void MainWin::on_EasyWord_btn_clicked()
{
    CurWord++;
    RefreshLearn();
}

//搜索按钮
void MainWin::on_Search_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

//回到主界面
void MainWin::on_Backmenu_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//搜索确定按钮
void MainWin::on_Search_btn_2_clicked()
{  ui->listWidget->clear();
    string s=ui->Search_LE->text().toStdString();
    if(s!=""){

        for(int i=0;i<Dic->Wordnum;i++){
            string s1=Dic->word[i]->get_chinese().toStdString();
            string s2=Dic->word[i]->get_english().toStdString();
            if(s1.find(s) != string::npos ||s2.find(s) != string::npos){

                ui->listWidget->addItem(Dic->word[i]->get_english()+" "+Dic->word[i]->get_chinese());
            }
        }

    }
}

//主界面查看信息按钮
void MainWin::on_menu_btn_clicked()
{
    QMessageBox::information(this,("Information"), ("学号：2016212901 "));
    //RefreshEnter();
}

//-----------------------------------------------------------
//getDataThread线程从缓冲区中取出接收到信息，然后处理，显示到UI上
//-----------------------------------------------------------
bool compareQVariantMap(const QVariantMap &map1,const QVariantMap &map2)
{
    if(map1["accuracy"].toInt() > map2["accuracy"].toInt())return true;
    return false;
}

void MainWin::getDataSlot(QVariantMap jsonMap)
{
    if(SWITCH)qDebug()<< "-----------s-----------";
    if(SWITCH)qDebug()<< "Header:" << jsonMap["Header"].toString();
    if(SWITCH)qDebug()<< "rip:" << jsonMap["rip"].toString();
    if(SWITCH)qDebug()<< "speed:" << jsonMap["speed"].toString();
    if(SWITCH)qDebug()<< "name:" << jsonMap["name"].toString();
    if(SWITCH)qDebug()<< "time:" << jsonMap["time"].toString();
    if(SWITCH)qDebug()<< "-----------e-----------";

    QString header = jsonMap["Header"].toString();

    if(header == "DATA"){
        QVector<QVariantMap>::iterator iter = typerData.begin();
        int num = 0;
        while(iter != typerData.end()){

            if((*iter)["name"].toString() == jsonMap["name"].toString()){
                typerData.replace(num,jsonMap);
                break;
            }
            ++num;
            ++iter;
        }
        //不存在该用户，添加
        if(iter == typerData.end()){
            typerData.append(jsonMap);
        }
    }

    //排序
    qSort(typerData.begin(),typerData.end(),compareQVariantMap);

    int i;
    for(i=0;i<typerData.size();i++){

        if(typerData[i]["name"].toString()==nickName){
            qDebug()<<typerData[i]["name"].toString();
            break;
        }
    }
    ui->Rank_LE->setText(QString::number(i+1));

}



//-----------------------------------------------------------
//ReceiveThread
//-----------------------------------------------------------
ReceiveThread::ReceiveThread()
{

}

ReceiveThread::ReceiveThread(QString ip,QString port,QString nickName)
{
    client = new TcpClientSocket(ip,port,nickName);

    queueData.clear();

    connect(client,SIGNAL(updateClients(QString,int)),
            this,SLOT(updateQueueData(QString,int)));
}

ReceiveThread::~ReceiveThread()
{
    delete client;
}

void ReceiveThread::run()
{
    if(SWITCH)qDebug()<< "ReceiveThread is running...";
    this->exec();
}

void ReceiveThread::closeWidgetSlot()
{
    //发送断开连接
    //client->disconnected();
    if(SWITCH)qDebug()<< "closeWidgetSlot";
}

void ReceiveThread::updateClientDataSlot(QString jsonStr)
{   qDebug()<<"updateClientDataSlot";
    int length = 0;
    if((length = client->write(jsonStr.toUtf8(),jsonStr.length())) != jsonStr.length())
    {
        //可能是没有开启服务端的原因，这里可以做下处理
        if(SWITCH) QMessageBox::warning( NULL,("Warning"), ("网络异常！"));
        return;
    }
}

void ReceiveThread::updateQueueData(QString msg,int len)
{
    //超过了设置的最大连接数
    if(toGetData.available() == BUFFER_SIZE){
        mutex1.lock();
        buffer_full.wait(&mutex1);
        mutex1.unlock();
    }

    toReceive.acquire();
    mutex2.lock();
    if(SWITCH)qDebug()<< "r mutex2.lock";
    QJsonParseError jsonError;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(msg.left(len).toUtf8(),&jsonError);

    if(jsonError.error == QJsonParseError::NoError){
        if(jsonResponse.isObject()){
            if(SWITCH)qDebug()<< "[receivethread] is object";
            QJsonObject obj = jsonResponse.object();
            QVariantMap jsonMap = obj.toVariantMap();
            queueData.push_back(jsonMap);
        }
    }
    if(SWITCH)qDebug()<< "[R]queueData.size=" << queueData.size();

    mutex2.unlock();
    toGetData.release();
    buffer_empty.wakeAll();
}

//-----------------------------------------------------------
//GetDataThread
//-----------------------------------------------------------
GetDataThread::GetDataThread()
{

}

void GetDataThread::run()
{   //qDebug()<<"GetDataThread::run()";
    if(SWITCH)qDebug()<< "GetDataThread is running...";
    while(1){
        if(toReceive.available() == BUFFER_SIZE){
            mutex1.lock();
            buffer_empty.wait(&mutex1);
            mutex1.unlock();
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




