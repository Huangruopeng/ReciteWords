#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <vector>

#include <QString>
#include "word.h"

using namespace std;

class Memento
{
private:
    int state;
public:
    Memento()
    {state=0;}
    int get_state()
    {return state;}
    void set_state(int n)
    {state=n;}
};

//备忘录管理员角色
class  Caretaker
{
private:
    Memento memento;
 public:
    Memento getMemento()
       {return memento;}
    void setMemento(Memento* m )
       {memento.set_state(m->get_state());}
};

class Dictionary
{
private:
    int LearnNum=0;
    int ReviewNum=0;
public:

    Dictionary();
    vector<Word*> word;
    int Wordnum;
    void Initial();


    void set_LearnNum(int n)
    {LearnNum=n;}
    void set_ReviewNum(int n)
    {ReviewNum=n;}
    int get_LearnNum()
    {return LearnNum;}
    int get_ReviewNum()
    {return ReviewNum;}
    //void setState(int n);

    //这里是备忘录实现部分 Dictionary相当于备忘录模式里的 Originator
    Memento* createMemento()
    {   Memento* m=new Memento;
        return m;}
    void restoreMemento(Memento men)
    {set_LearnNum(men.get_state());}

    //避免了不同情况实例化类对象
       Dictionary(const Dictionary& another){}
       Dictionary& operator = (const Dictionary& another){}
       static Dictionary* _mpDic;
};



#endif // DCTIONARY_H
