#ifndef WORD_H
#define WORD_H
#include<QString>

class Word
{
public:
    Word();
    QString get_chinese();
    QString get_english();
    int get_memory();
    void set_word(QString chinese,QString english,int memory);

private:
    QString ChineseWord;//中文
    QString EnglishWord;//英文
    int Memory;//熟练度
};

#endif // WORD_H
