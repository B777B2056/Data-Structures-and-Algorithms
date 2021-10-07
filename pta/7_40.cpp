#include <iostream>
using namespace std;

// 与7-41类似

struct Country
{
    double info[5];  // 0~4: 金牌总数，奖牌总数，人均金牌数，人均奖牌数，国家编号
    int rank[4];
};

int cmp(Country& a, Country& b, int way)
{
    int result;
    if(a.info[way] < b.info[way])
        result = 1;
    else if(a.info[way] == b.info[way])
        result = 0;
    else
        result = -1;
    if(way == 4)
        result *= -1;
    return result;
}

/*快速排序*/
void quickSort(Country *v, int l, int r, int way)
{
    if(l >= r)
        return;
    int i = l, j = r;
    Country pivot = v[l];
    while(i < j)
    {
        while((i < j) && (cmp(v[j], pivot, way) >= 0))
            j--;
        if(i < j)
            v[i++] = v[j];
        while((i < j) && (cmp(v[i], pivot, way) < 0))
            i++;
        if(i < j)
            v[j--] = v[i];
    }
    v[i] = pivot;
    quickSort(v, l, i - 1, way);
    quickSort(v, i + 1, r, way);
}

void getRank(Country *v, int N, int i)
{
    quickSort(v, 0, N - 1, i);
    v[0].rank[i] = 1;
    for(int j = 1; j < N; j++)
    {
        if(v[j].info[i] == v[j - 1].info[i])
            v[j].rank[i] = v[j - 1].rank[i];
        else
            v[j].rank[i] = j + 1;
    }
}

void ex7_40()
{
    int a, b, c, i, j, bestRank, N, M;
    cin >> N >> M;
    Country vec[N];
    for(i = 0; i < N; i++)
    {
        cin >> a >> b >> c;
        vec[i].info[0] = a;
        vec[i].info[1] = b;
        vec[i].info[2] = a / (double)c;
        vec[i].info[3] = b / (double)c;
        vec[i].info[4] = i;
    }
    for(i = 0; i < 4; i++)
        getRank(vec, N, i);
    quickSort(vec, 0, N - 1, 4);
    for(i = 0; i < M; i++)
    {
        cin >> a;
        bestRank = M + 1;
        for(j = 0; j < 4; j++)
        {
            if(vec[a].rank[j] < bestRank)
                bestRank = vec[a].rank[j];
        }
        for(j = 0; j < 4; j++)
        {
            if(bestRank == vec[a].rank[j])
                break;
        }
        if(i == 0)
            cout << bestRank << ":" << j + 1;
        else
            cout << " " << bestRank << ":" << j + 1;
    }
}