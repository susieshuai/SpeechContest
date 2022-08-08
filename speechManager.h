#pragma once
#include <iostream>
using namespace std;

/*
设计演讲管理类
功能：
1. 提供菜单界面与用户交互
2. 对演讲比赛流程进行控制
3. 与文件的读写交互
*/
class SpeechManager
{
public:
    // 构造函数
    SpeechManager();

    // 展示菜单
    void showMenu();

    // 析构函数
    ~SpeechManager();
};