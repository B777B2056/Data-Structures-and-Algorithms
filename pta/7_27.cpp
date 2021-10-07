#include <iostream>
#include <string>
using namespace std;

/*记录每个人的父亲就行*/

struct People
{
    string name;
    int father;
    int spaceCnt;
    People() : father(-1), spaceCnt(0) {}
};

void ex7_27()
{
    int i, k, cnt, N, M;
    char command;
    string name, str, x, y;
    cin >> N >> M;
    getchar();
    People *p = new People[N];
    for(i = 0; i < N; i++)
    {
        getline(cin, name);
        if(i == 0)
        {
            p[0].name = name;
        }
        else
        {
            // 计算有多少个空格
            for(k = 0; name[k] == ' '; k++);
            name.erase(0, k);
            p[i].spaceCnt = k;
            p[i].name = name;
            // 按照父亲名字空格比孩子少两个的原则向前遍历，寻找父亲
            for(k = i - 1; k >= 0; k--)
            {
                if(p[k].spaceCnt + 2 == p[i].spaceCnt)
                {
                    p[i].father = k;
                    break;
                }
            }
        }
    }
    for(i = 0; i < M; i++)
    {
        getline(cin, str);
        x = "";
        y = "";
        cnt = 0;
        // 分割字符串X，命令与字符串Y
        for(k = 0; k < str.length(); k++)
        {
            if(str[k] == ' ')
                cnt++;
            else
            {
                if(cnt == 0)
                    x += str[k];
                if(cnt == 2)
                    command = str[k + 2];
                if(cnt == 5)
                    y += str[k];
            }
        }
        switch(command)
        {
            case 'c':
                for(k = 0; k < N; k++)
                {
                    if(p[k].name == x)
                    {
                        if(p[p[k].father].name == y)
                            cout << "True" << endl;
                        else
                            cout << "False" << endl;
                        break;
                    }
                }
                break;
            case 'p':
                for(k = 0; k < N; k++)
                {
                    if(p[k].name == y)
                    {
                        if(p[p[k].father].name == x)
                            cout << "True" << endl;
                        else
                            cout << "False" << endl;
                        break;
                    }
                }
                break;
            case 's':
                int f1, f2;
                for(k = 0; k < N; k++)
                {
                    if(p[k].name == x)
                    {
                        f1 = p[k].father;
                        break;
                    }
                }
                for(k = 0; k < N; k++)
                {
                    if(p[k].name == y)
                    {
                        f2 = p[k].father;
                        break;
                    }
                }
                if(f1 == f2)
                    cout << "True" << endl;
                else
                    cout << "False" << endl;
                break;
            case 'd':
                for(k = 0; k < N; k++)
                {
                    if(p[k].name == x)
                    {
                        int s = p[k].father;
                        while((s != -1) && (p[s].name != y))
                            s = p[s].father;
                        if(s != -1)
                            cout << "True" << endl;
                        else
                            cout << "False" << endl;
                        break;
                    }
                }
                break;
            case 'a':
                for(k = 0; k < N; k++)
                {
                    if(p[k].name == y)
                    {
                        int s = p[k].father;
                        while((s != -1) && (p[s].name != x))
                            s = p[s].father;
                        if(s != -1)
                            cout << "True" << endl;
                        else
                            cout << "False" << endl;
                        break;
                    }
                }
                break;
        }
    }
}