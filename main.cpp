#include <iostream>
using namespace std;
#include "speechManager.h"

int main()
{
    // 创建管理类对象
    SpeechManager sm;

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
            /* code */
            break;

        case 2: // 往届记录
            /* code */
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