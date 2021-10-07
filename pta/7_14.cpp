#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*哈希表插入，找最大值*/

struct PhoneNum
{
    long long num;
    int cnt;
    PhoneNum() : num(0), cnt(1) {}
};

int hashMethod(int P, long long key)
{
    return key % P;
}

int conflict(int P, int basePos, int i)
{
    return (basePos + i) % P;
}

void insert(long long num, PhoneNum *pn, int P)
{
    int basePos, newPos, i = 0;
    bool isExist = false;
    newPos = basePos = hashMethod(P, num);
    while(pn[newPos].num != 0)
    {
        if(pn[newPos].num == num)
        {
            isExist = true;
            ++pn[newPos].cnt;
            break;
        }
        newPos = conflict(P, basePos, ++i);
    }
    if(!isExist)
        pn[newPos].num = num;
}

void ex7_14()
{
    int i, N, P, maxCnt = 0;
    long long start, end, minMaddog;
    vector<long long> vec;
    cin >> N;
    P = (2 * N) / 0.75;
    PhoneNum pn[P];
    for(i = 0; i < N; i++)
    {
        cin >> start >> end;
        insert(start, pn, P);
        insert(end, pn, P);
    }
    for(i = 0; i < P; i++)
    {
        if(maxCnt < pn[i].cnt)
            maxCnt = pn[i].cnt;
    }
    for(i = 0; i < P; i++)
    {
        if(maxCnt == pn[i].cnt)
            vec.push_back(pn[i].num);
    }
    minMaddog = vec[0];
    for(long long n : vec)
    {
        if(minMaddog > n)
            minMaddog = n;
    }
    if(vec.size() > 1)
        cout << minMaddog << " " << maxCnt << " " << vec.size() << endl;
    else
        cout << minMaddog << " " << maxCnt << endl;
}