#include <iostream>
using namespace std;
#include "speechManager.h"
#include <ctime>

// 测试打印12名选手
void test01(map<int, Speaker> &speakers)
{
    int i = 1;
    for (map<int, Speaker>::iterator it = speakers.begin(); it != speakers.end(); it++)
    {
        cout << "第" << i << "名选手信息：" << endl;
        cout << "编号：" << it->first << "\t姓名" << it->second.name << "\t成绩：" << it->second.score[0] << "\t" << it->second.score[1] << endl;
        i++;
    }
}

int main()
{
    // 添加随机数种子
    srand((unsigned int)time(NULL));

    // 创建管理类对象
    SpeechManager sm;

    // test01(sm.speakers);

    cout << "请输入您的选择" << endl;

    int choice = 0;

    while (true)
    {
        sm.showMenu();
        cin >> choice;
        switch (choice)
        {
        case 0: // 退出系统
            sm.exitSystem();
            break;

        case 1: // 开始比赛
            sm.startSpeech();
            break;

        case 2: // 往届记录
            sm.showRecord();
            break;

        case 3: // 清空记录
            /* code */
            break;

        default:
            system("clear");
            break;
        }
    }

    return 0;
}
