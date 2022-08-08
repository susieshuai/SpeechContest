#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"

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

    // 退出系统
    void exitSystem();

    // 初始化属性
    void initSpeech();

    // 创建12个选手
    void createSpeaker();

    // 析构函数
    ~SpeechManager();

    // 成员属性
    // 第一轮选手编号 12人
    vector<int> round1;
    // 第二轮选手编号 6人
    vector<int> round2;
    // 胜出选手 3人
    vector<int> winners;
    // 编号-选手表
    map<int, Speaker> speakers;
    // 第几轮
    int round;
};