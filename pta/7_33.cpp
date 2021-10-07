#include <iostream>
using namespace std;

int cnt = 0;
// 注意看何时输出，明白递归的执行次序
void DFS(int start, int N, int **adjMatrix, bool *visted)
{
    if(visted[start])
        return;
    visted[start] = true;
    if(!cnt)
        cout << start + 1;
    else
        cout << " " << start + 1;
    cnt++;
    for(int i = 0; i <N; i++)
    {
        if(!visted[i] && adjMatrix[start][i])
        {
            DFS(i, N, adjMatrix, visted);
            if(!cnt)
                cout << start + 1;
            else
                cout << " " << start + 1;
        }
    }
}

void ex7_33()
{
    int N, M, S, i, j, v1, v2;
    cin >> N >> M >> S;
    int **adjMatrix = new int*[N];
    bool visted[N] = {false};
    for(i = 0; i < N; i++)
        adjMatrix[i] = new int[N];
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
            adjMatrix[i][j] = 0;
    }
    for(i = 0; i < M; i++)
    {
        cin >> v1 >> v2;
        adjMatrix[v1 - 1][v2 - 1] = adjMatrix[v2 - 1][v1 - 1] = 1;
    }
    DFS(S - 1, N, adjMatrix, visted);
    if(cnt != N)
    cout << " 0";
}