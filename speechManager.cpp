#include "speechManager.h"

// 构造函数
SpeechManager::SpeechManager()
{
    this->initSpeech();
}

// 展示菜单
void SpeechManager::showMenu()
{
    cout << "********************************************" << endl;
    cout << "*************  欢迎参加演讲比赛 ************" << endl;
    cout << "*************  1.开始演讲比赛  *************" << endl;
    cout << "*************  2.查看往届记录  *************" << endl;
    cout << "*************  3.清空比赛记录  *************" << endl;
    cout << "*************  0.退出比赛程序  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

// 退出系统
void SpeechManager::exitSystem()
{
    cout << "欢迎下次使用！" << endl;
    exit(0);
}

// 初始化属性
void SpeechManager::initSpeech()
{
    // 容器置空
    this->round1.clear();
    this->round2.clear();
    this->winners.clear();
    this->speakers.clear();
    // 第一轮
    this->round = 1;
}

// 析构函数
SpeechManager::~SpeechManager()
{
}