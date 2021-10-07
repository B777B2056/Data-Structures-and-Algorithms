#include <iostream>
using namespace std;

/* 判断图是否连通
 * 注：“图中有顶点的入度与出度均为0”不可以得到“图不连通”！！！！！！！
 *     必须通过遍历图中连通分量，对连通分量包含的顶点进行计数，看是不是等于图中顶点数来判断图是否连通。
 */
int cnt = 0;
void DFS(int **adj, bool *v, int N, int source)
{
    if(v[source]) return;
    ++cnt;
    v[source] = true;
    for(int i = 0; i < N; i++)
    {
        if(!v[i] && (adj[source][i] == 1))
            DFS(adj, v, N, i);
    }
}

/* 对于无向图，若图连通且所有顶点的度均为偶数时，则该图存在欧拉回路
 * 注：对于有向图，若图连通且每个顶点的入度等于出度，则该图存在欧拉回路
 */
void ex7_32()
{
    int i, j, a, b, N, M, answer = 1;
    cin >> N >> M;
    bool v[N] = {false};
    // 构造邻接矩阵
    int **adj = new int*[N];
    for(i = 0; i < N; i++)
        adj[i] = new int[N];
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            adj[i][j] = 0;
    }
    for(i = 0; i < M; i++)
    {
        cin >> a >> b;
        adj[a - 1][b - 1] = adj[b - 1][a - 1] = 1;
    }
    // 检查图是否连通
    DFS(adj, v, N, 0);
    if(cnt == N)
    {
        // 检查是否有度为奇数的情况
        for(i = 0; i < N; i++)
        {
            int degree = 0;
            for(j = 0; j < N; j++)
            {
                if(adj[i][j] == 1)
                    ++degree;
            }
            if(degree % 2)
            {
                answer = 0;
                break;
            } 
        }
    }
    else
        answer = 0;
    cout << answer << endl;
}