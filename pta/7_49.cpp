#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 哈希表无法通过最后一个测试点
// 观察到学生姓名由3个大写英文字母+1位数字组成，因此可以用一个26x26x26x10的四维数组快速查找目标学生
void ex7_49()
{
    unsigned int i, j, c, p, N, K;
    string name;
    cin >> N >> K;
    vector<int> course[26][26][26][10];
    for(i = 0; i < K; i++)
    {
        cin >> c >> p;
        for(j = 0; j < p; j++)
        {
            cin >> name;
            course[name[0] - 'A'][name[1] - 'A'][name[2] - 'A'][name[3] - '0'].push_back(c);
        }
    }
    for(i = 0; i < N; i++)
    {
        cin >> name;
        sort(course[name[0] - 'A'][name[1] - 'A'][name[2] - 'A'][name[3] - '0'].begin(), course[name[0] - 'A'][name[1] - 'A'][name[2] - 'A'][name[3] - '0'].end());
        cout << name << " " << course[name[0] - 'A'][name[1] - 'A'][name[2] - 'A'][name[3] - '0'].size();
        for(int c : course[name[0] - 'A'][name[1] - 'A'][name[2] - 'A'][name[3] - '0'])
            cout << " " << c;
        cout << "\n";
    }
}