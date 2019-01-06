#include "word.h"

Word::Word()
{

}
//获取中文
QString Word::get_chinese()
{
    return ChineseWord;
}

//获取英文
QString Word::get_english()
{
    return EnglishWord;
}

//获取熟悉度
int Word::get_memory()
{
    return Memory;
}

//设入函数
void Word::set_word(QString chinese, QString english, int memory)
{
    ChineseWord=chinese;
    EnglishWord=english;
    Memory=memory;
}

