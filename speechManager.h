#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>

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

    // 开始比赛 - 比赛全过程控制函数
    void startSpeech();

    // 抽签
    void speechDraw();

    // 比赛
    void speechContest();

    // 显示比赛结果
    void showScore();

    // 保存比赛结果
    void saveRecord();

    // 读取记录
    void loadRecord();

    // 显示记录
    void showRecord();

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

    // 判断文件是否为空
    bool fileIsEmpty;

    // 往届记录
    // >> 编译问题：指定新版本，如-std=c++11
    map<int, vector<string>> record;
};