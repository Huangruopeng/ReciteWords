#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QTextEdit>

#include "login.h"
#include "receivethread.h"
#include "getdatathread.h"
#include "tcpclientsocket.h"

#define BUFFER_SIZE   100                   //最大100个用户的缓冲数据
#define SWITCH   0

class ReceiveThread;
class GetDataThread;

namespace Ui {
class MainWin;
class ReceiveThread;
class GetDataThread;
}

class MainWin : public QWidget
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0);
    void RefreshLearn();//刷新学习界面
    void RefreshReview();//刷新复习界面
    void RefreshEnter();//刷新进入界面
    void RefreshSearch();//刷新搜索界面
    void InitUI();//初始化界面
    bool IsEnglish(QString &qstrSrc);//判断是否英文

    ~MainWin();

private:
    Ui::MainWin *ui;
    Login *login;

    int CurWord=0;
    int CorrectNum=0;
    unsigned long TimeCount=0;//使用时间
    QVector<QVariantMap> typerData;//收到的数据
signals:
    void closeSignal();
    void updateClientDataSignal(QString);

//登录相关
private:    
     QString nickName;//昵称
     int eventData;//事件

private slots:
      void widgetReceiveSetData(const QString&,const QString&,const QString&);//收到数据
      void widgetReceiveEventData(const int&);//接收到事件
      void TimerInit();//计时器初始化

//线程相关
private:
    ReceiveThread * receiveThread;
    GetDataThread * getDataThread;

//窗口处理数据槽函数
private slots:
      void getDataSlot(QVariantMap);

      void timerHandleSlot();

      void on_logiin_btn_clicked();

      void on_Learn_btn_clicked();

      void on_Review_btn_clicked();

      void on_Back_btn_clicked();

      void on_Abandon_btn_clicked();

      void on_ChoiceA_btn_clicked();

      void on_ChoiceB_btn_clicked();

      void on_ChoiceC_btn_clicked();

      void on_ChoiceD_btn_clicked();

      void on_lineEdit_returnPressed();

      void on_Back_btn_2_clicked();

      void on_ViewAnswer_btn_clicked();

      void on_NextWord_btn_clicked();

      void on_InputAnswer_LE_returnPressed();

      void on_EasyWord_btn_clicked();

      void on_Search_btn_clicked();

      void on_Backmenu_btn_clicked();

      void on_Search_btn_2_clicked();

      void on_menu_btn_clicked();


};

#endif // MAINWIN_H
