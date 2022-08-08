#include "speechManager.h"

// 构造函数
SpeechManager::SpeechManager()
{
    // 初始化容器和属性
    this->initSpeech();
    // 创建12个选手
    this->createSpeaker();
    // 加载往届记录
    this->loadRecord();
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

// 创建选手
void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < 12; i++)
    {
        // 创建具体选手
        Speaker speaker;

        string name = "选手";
        name += nameSeed[i];

        speaker.name = name;
        speaker.score[0] = 0;
        speaker.score[1] = 0;

        // 加入选手名单
        this->speakers.insert(make_pair(i + 10001, speaker));
        // 加入第一轮编号
        this->round1.push_back(i + 10001);
    }
}

// 开始比赛
void SpeechManager::startSpeech()
{
    // 第一轮
    // 1.1 抽签
    this->speechDraw();
    // 1.2 比赛
    this->speechContest();
    // 1.3 显示晋级结果
    this->showScore();

    // 第二轮
    this->round++;
    // 2.1 抽签
    this->speechDraw();
    // 2.2 比赛
    this->speechContest();
    // 2.3 显示比赛结果
    this->showScore();
    // 2.4 保存结果至文件
    this->saveRecord();

    cout << "本届比赛结束" << endl;
}

// 抽签
void SpeechManager::speechDraw()
{
    cout << "第" << this->round << "轮的选手正在抽签" << endl;
    cout << "顺序如下：" << endl;

    if (this->round == 1)
    {
        random_shuffle(this->round1.begin(), this->round1.end());
        for (vector<int>::iterator it = this->round1.begin(); it != this->round1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        random_shuffle(this->round2.begin(), this->round2.end());
        for (vector<int>::iterator it = this->round2.begin(); it != this->round2.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}

class MyCompare
{
public:
    bool operator()(double d1, double d2) const
    {
        return d1 > d2;
    }
};

// 比赛
void SpeechManager::speechContest()
{
    cout << "第" << this->round << "轮比赛正式开始" << endl;

    // 准备一个临时容器存放小组成绩
    multimap<double, int, MyCompare> tempGroupScores;
    /*
    1. 这里的greater<double>是模板声明类型，不加括号；而sort中的greater<double>()是对象，要加括号。
    2. >>之间一定要加括号，不然报错，但是vscode会自动修正，所以自定义了一个仿函数来实现降序排列。
    */
    // multimap<double, int, greater<double>> tempGroupScores;

    // 统计已演讲的人数
    int cnt = 0;

    // 当前比赛人员
    vector<int> curSpeakers;
    if (this->round == 1)
    {
        curSpeakers = round1;
    }
    else
    {
        curSpeakers = round2;
    }

    // 遍历所有选手编号进行比赛
    for (vector<int>::iterator it = curSpeakers.begin(); it != curSpeakers.end(); it++)
    {
        cnt++;
        // 10个评委打分
        deque<double> scores;
        for (int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f; // [600, 1000]小数
            // cout << score << " ";
            scores.push_back(score);
        }
        // cout << endl;

        // 从大到小排序
        sort(scores.begin(), scores.end(), greater<double>());
        scores.pop_front();
        scores.pop_back();

        double sum = accumulate(scores.begin(), scores.end(), 0.0f);
        double avg = sum / (double)scores.size();

        // 将平均分放入map里
        this->speakers[*it].score[this->round - 1] = avg;

        // 打印每个选手成绩
        // cout << "编号：" << *it << "\t姓名：" << this->speakers[*it].name << "\t成绩：" << avg << endl;

        // 将数据放入临时容器中
        tempGroupScores.insert(make_pair(avg, *it));

        // 每六个人取出前三名
        if (cnt % 6 == 0)
        {
            cout << "第" << cnt / 6 << "小组名次：" << endl;
            for (multimap<double, int, MyCompare>::iterator it = tempGroupScores.begin(); it != tempGroupScores.end(); it++)
            {
                cout << "编号：" << it->second
                     << "\t姓名：" << this->speakers[it->second].name
                     << "\t成绩：" << this->speakers[it->second].score[this->round - 1]
                     << endl;
            }

            // 取走前三名放入下一个容器中
            int n = 0;
            for (multimap<double, int, MyCompare>::iterator it = tempGroupScores.begin(); it != tempGroupScores.end() && n < 3; it++, n++)
            {
                if (this->round == 1)
                {
                    round2.push_back(it->second);
                }
                else
                {
                    winners.push_back(it->second);
                }
            }

            // 一组比完了，小组容器要清空
            tempGroupScores.clear();
        }
    }
    cout << "第" << this->round << "轮比赛结束" << endl;
}

// 显示比赛结果
void SpeechManager::showScore()
{
    cout << "第" << this->round << "轮晋级选手信息：" << endl;

    vector<int> v;
    if (this->round == 1)
    {
        v = round2;
    }
    else
    {
        v = winners;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "编号：" << *it
             << "\t姓名：" << this->speakers[*it].name
             << "\t成绩：" << this->speakers[*it].score[this->round - 1]
             << endl;
    }
    cout << endl;
}

// 保存比赛结果
void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app); // 追加方式写文件

    // 写入前三名
    for (vector<int>::iterator it = this->winners.begin(); it != this->winners.end(); it++)
    {
        ofs << *it << "," << this->speakers[*it].score[1] << ",";
    }
    ofs << endl;

    ofs.close();
    cout << "记录保存成功" << endl;
}

// 读取记录
void SpeechManager::loadRecord()
{
    ifstream ifs("speech.csv", ios::in);

    // 文件不存在
    if (!ifs.is_open())
    {
        this->fileIsEmpty = true;
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    // 文件为空
    char c;
    ifs >> c;
    if (ifs.eof())
    {
        this->fileIsEmpty = true;
        cout << "文件为空" << endl;
        ifs.close();
        return;
    }

    // 读文件
    this->fileIsEmpty = false;
    ifs.putback(c); // 将上面读取的单个字符再放回来

    string data;
    int index = 0;

    while (ifs >> data)
    {
        // cout << data << endl;
        // 10005,83.6125,10007,82.7375,10008,80.725,
        vector<string> v; // 临时存放一届的数据

        int pos = -1; // 查到”，“位置的变量
        int start = 0;

        while (true)
        {
            pos = data.find(",", start);
            if (pos == -1)
            {
                break;
            }
            string temp = data.substr(start, pos - start);
            v.push_back(temp);
            start = pos + 1;
        }

        this->record.insert(make_pair(index, v));
        index++;
    }

    ifs.close();

    // 测试结果map数据
    // for (map<int, vector<string>>::iterator it = this->record.begin(); it != this->record.end(); it++)
    // {
    //     cout << it->first << "冠军编号" << it->second[0] << endl;
    // }
}

// 显示记录
void SpeechManager::showRecord()
{
    for (int i = 0; i < this->record.size(); i++)
    {
        cout << "第" << i + 1 << "届" << endl;
        cout << "冠军编号：" << this->record[i][0] << "\t成绩：" << this->record[i][1] << endl;
        cout << "亚军编号：" << this->record[i][2] << "\t成绩：" << this->record[i][3] << endl;
        cout << "季军编号：" << this->record[i][4] << "\t成绩：" << this->record[i][5] << endl;
    }
}

// 析构函数
SpeechManager::~SpeechManager()
{
}