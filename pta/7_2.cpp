#include <iostream>
#include <vector>
using namespace std;

/*注意0多项式处理（不要消掉0多项式）*/

struct Item
{
    int coefficient;
    int exponent;
    Item(int a, int b) : coefficient(a), exponent(b) {}
};

vector<Item> add(vector<Item> &v1, vector<Item> &v2)
{
    if(!v1.size())
        return v2;
    if(!v2.size())
        return v1;
    vector<Item> r;
    size_t i, j = 0;
    for(i = 0; i < v1.size() && j < v2.size(); i++)
    {
        if(v1[i].exponent < v2[j].exponent)
        {
            while(j < v2.size() && v1[i].exponent < v2[j].exponent)
            {
                r.push_back(Item(v2[j].coefficient, v2[j].exponent));
                j++;
            }
            if(j < v2.size())
            {
                if(v1[i].exponent == v2[j].exponent)
                {
                    if(v1[i].coefficient + v2[j].coefficient != 0)
                        r.push_back(Item(v1[i].coefficient + v2[j].coefficient, v1[i].exponent));
                }
                else
                {
                    r.push_back(Item(v1[i].coefficient, v1[i].exponent));
                    r.push_back(Item(v2[j].coefficient, v2[j].exponent));
                }
            }
            else
                r.push_back(Item(v1[i].coefficient, v1[i].exponent));
        }
        else if(v1[i].exponent > v2[j].exponent)
        {
            while(i < v1.size() && v1[i].exponent > v2[j].exponent)
            {
                r.push_back(Item(v1[i].coefficient, v1[i].exponent));
                i++;
            }
            if(i < v1.size())
            {
                if(v1[i].exponent == v2[j].exponent)
                {
                    if(v1[i].coefficient + v2[j].coefficient != 0)
                        r.push_back(Item(v1[i].coefficient + v2[j].coefficient, v1[i].exponent));
                }
                else
                {
                    r.push_back(Item(v2[j].coefficient, v2[j].exponent));
                    r.push_back(Item(v1[i].coefficient, v1[i].exponent));
                }
            }
            else
                r.push_back(Item(v2[j].coefficient, v2[j].exponent));
        }
        else
        {
            if(v1[i].coefficient + v2[j].coefficient != 0)
                r.push_back(Item(v1[i].coefficient + v2[j].coefficient, v1[i].exponent));
        }
        j++;
    }
    while(i < v1.size())
    {
        r.push_back(Item(v1[i].coefficient, v1[i].exponent));
        i++;
    }
    while(j < v2.size())
    {
        r.push_back(Item(v2[j].coefficient, v2[j].exponent));
        j++;
    }
    return r;
}

vector<Item> mul(vector<Item> &v1, vector<Item> &v2)
{
    size_t i, j;
    vector<Item> r;
    if(!v1.size() || !v2.size())
        return r;
    for(i = 0; i < v1.size(); i++)
    {
        vector<Item> temp;
        for(j = 0; j < v2.size(); j++)
            temp.push_back(Item(v1[i].coefficient * v2[j].coefficient, v1[i].exponent + v2[j].exponent));
        r = add(temp, r);
    }
    return r;
}

void ex7_2()
{
    int c, e, N, M;
    size_t i;
    // 输入
    cin >> N;
    vector<Item> v1, v2, r1, r2;
    for(i = 0; i < N; i++)
    {
        cin >> c >> e;
        v1.push_back(Item(c, e));
    }
    cin >> M;
    for(i = 0; i < M; i++)
    {
        cin >> c >> e;
        v2.push_back(Item(c, e));
    }
    // 多项式相加
    r1 = add(v1, v2);
    // 多项式相乘
    r2 = mul(v1, v2);
    if(!r1.size())
        r1.push_back(Item(0, 0));
    if(!r2.size())
        r2.push_back(Item(0, 0));
    // 输出
    cout << r2[0].coefficient << " " << r2[0].exponent;
    for(i = 1; i < r2.size(); i++)
        cout << " " << r2[i].coefficient << " " << r2[i].exponent;
    cout << endl;
    cout << r1[0].coefficient << " " << r1[0].exponent;
    for(i = 1; i < r1.size(); i++)
        cout << " " << r1[i].coefficient << " " << r1[i].exponent;
}