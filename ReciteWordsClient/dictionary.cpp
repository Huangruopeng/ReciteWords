#include "dictionary.h"
#include "word.h"
#include <fstream>
#include <exception>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
extern Dictionary *Dic;

//重载函数，读到单词中
ifstream & operator >> (ifstream & in,Word *w)
{
    string chinese,english,s;
    int memory;

        in>>english>>chinese;
        qDebug()<<QString::fromStdString(chinese)<<QString::fromStdString(english);//memory;

        w->set_word(QString::fromStdString(chinese),QString::fromStdString(english),0); //,memory);

        return in;

}

Dictionary::Dictionary()
{

}

//词典初始化
void Dictionary::Initial()
{   qDebug()<<"进入词典初始化";
    ifstream in;
    try{
            in.open("C:/Users/Rocair/Desktop/Dictionary1.txt");//暂时先用绝对路径
            //qDebug()<<"打开";
            if(!in)
              throw invalid_argument("文件打开错误,可能要改一下路径。\n源码位置dictionary.cpp 35行左右");
          }
        catch(exception &e){
           QMessageBox::warning( NULL,("Warning"), (QString::fromStdString(e.what())));
          }

    string nn;
    in>>nn;
    int n=QString::fromStdString(nn).toInt();
    qDebug()<<n;//读入单词数量
    Wordnum=n;
    for(int i=0;i<Wordnum;i++){
        Word *w=new Word;
        in>>w;
        Dic->word.push_back(w);
    }


}
