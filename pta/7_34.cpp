#include <iostream>
#include <queue>
using namespace std;

void ex7_34()
{
    int N, M, S, i, j;
    cin >> N;
    //构造邻接矩阵
    int adj[N][N], inOrder[N];
    bool v[N];
    for(i = 0; i < N; i++)
    {
        v[i] = false;
        inOrder[i] = 0;
        for(j = 0; j < N; j++)
            adj[i][j] = 0;
    }
    for(i = 0; i < N; i++)
    {
        cin >> M;
        for(j = 0; j < M; j++)
        {
            cin >> S;
            adj[S - 1][i] = 1;
        }
    }
    //构造入度矩阵
    for(i = 0; i < N; i++)
    {
        int cnt = 0;
        for(j = 0; j < N; j++)
        {
            if(adj[j][i] == 1)
                cnt++;
        }
        inOrder[i] = cnt;
    }
    //初始化存放入度为0的结点的容器（采用队列）
    queue<int> zeroInOrder;
    for(i = 0; i < N; i++)
    {
        if(inOrder[i] == 0)
        {
            v[i] = true;
            zeroInOrder.push(i);
        }
    }
    //进行拓扑排序
    for(i = 0; i < N; i++)
    {
        if(zeroInOrder.empty())
        {
            cout << "0" << endl;
            return;
        }
        int z = zeroInOrder.front();
        zeroInOrder.pop();
        for(j = 0; j < N; j++)
        {
            if(adj[z][j] == 1)
                inOrder[j]--;
            if(!v[j] && (inOrder[j] == 0))
            {
                v[j] = true;
                zeroInOrder.push(j);
            }
        }
    }
    cout << "1" << endl;
}