#include <iostream>
#include <stack>
using namespace std;

/* 图的边权与点权同时最优的问题
 * 注意看是怎么统计不同最短路径条数的，以及发现相同距离的最短路径时怎么更新其他目标量的
 * 各个数组怎么初始化特别重要！！！！！！！！！
 */

void ex7_35()
{
    int N, M, S, D, i, j, k, w;
    cin >> N >> M >> S >> D;
    /*声明*/
    int dist[N], path[N], pointWeightSum[N], numOfHelp[N], numOfPath[N], adj[N][N];
    bool v[N];
    /*输入救援队数量（即：点权）*/
    for(i = 0; i < N; i++)
        cin >> numOfHelp[i];
    /*填充邻接矩阵*/
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            adj[i][j] = __INT_MAX__;
    }
    for(i = 0; i < M; i++)
    {
        cin >> j >> k >> w;
        adj[j][k] = adj[k][j] = w;
    }
    /*初始化*/
    for(i = 0; i < N; i++)
    {
        dist[i] = __INT_MAX__;
        if(adj[S][i] < __INT_MAX__)
            dist[i] = adj[S][i];
        path[i] = S;
        pointWeightSum[i] = numOfHelp[i];
        numOfPath[i] = 1;
        v[i] = false;
    }
    v[S] = true;
    path[S] = -1;
    pointWeightSum[S] = numOfHelp[S];
    numOfPath[S] = 1;
    dist[S] = 0;
    /*迪加斯特拉算法求最短路径并计算救援队数量*/
    while(true)
    {
        int minVertex = -1, minDist = __INT_MAX__;
        for(i = 0; i < N; i++)
        {
            if(!v[i] && (dist[i] < minDist))
            {
                minDist = dist[i];
                minVertex = i;
            }
        }
        if(minVertex == -1) break;
        v[minVertex] = true;
        for(i = 0; i < N; i++)
        {
            if(!v[i] && (adj[minVertex][i] < __INT_MAX__))
            {
                // 情况1、有比之前找到的更短的路径，更新最短路径，更新路径上的点权和
                //     此时到达i的最短路径条数等于到达最小结点的最短路径条数
                if(dist[minVertex] + adj[minVertex][i] < dist[i])
                {
                    dist[i] = dist[minVertex] + adj[minVertex][i];
                    path[i] = minVertex;
                    numOfPath[i] = numOfPath[minVertex];
                    pointWeightSum[i] = pointWeightSum[minVertex] + numOfHelp[i];
                }
                // 情况2、产生相同距离的路径，更新路径上的点权和与最短路径条数
                //     此时到达i的最短路径条数等于到达最小结点的最短路径条数与之前到达i的最短路径条数之和
                else if(dist[minVertex] + adj[minVertex][i] == dist[i])
                {
                    numOfPath[i] += numOfPath[minVertex];
                    if(pointWeightSum[minVertex] + numOfHelp[i] > pointWeightSum[i])
                    {
                        path[i] = minVertex;
                        pointWeightSum[i] = pointWeightSum[minVertex] + numOfHelp[i];
                    }
                }
            }
        }
    }
    cout << numOfPath[D] << " " << pointWeightSum[D] + numOfHelp[S] << endl;  // 最终的点权和还需加上起始点的点权
    stack<int> s;
    while(D != -1)
    {
        s.push(D);
        D = path[D];
    }
    cout << s.top();
    s.pop();
    while(!s.empty())
    {
        cout << " " << s.top();
        s.pop();
    }
}