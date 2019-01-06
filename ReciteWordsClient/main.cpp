#include "MainWin.h"
#include <QApplication>
#include "dictionary.h"
#include <QDebug>
#include <windows.h>


Dictionary *Dic;
Caretaker *Care;
int status=0;
int used=0;
Dictionary* Dictionary::_mpDic = NULL;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Dic=new Dictionary;
    Dic->Initial();

    MainWin *w=new MainWin;  
    w->show();

    return a.exec();
}

//自定义异常处理类
class MyException
{
public:
    MyException(const QString &message):message(message){}
    ~MyException(){}
    const QString &getMessage()const{return message;}
private:
    QString message;

};
