#include <iostream>
using namespace std;

/* 并查集，需要使用按规模归并和路径压缩。
 * 注：查找时需要省略掉目标元素是否在并查集内的判断，否则会超时
 */

struct UFNode
{
    int id;  
    int parent;  // 父结点（树结构的并查集, 存放当前集合的元素个数的负数）
    UFNode() : parent(-1) {}
};

// 路径压缩
int pathCompression(UFNode *a, int i)
{
    if(a[i].parent < 0)
        return i;
    else
    {
        a[i].parent = pathCompression(a, a[i].parent);
        return a[i].parent;
    }
}

// 查
int findPos(UFNode *a, int N, int id)
{
    return pathCompression(a, id);
}

// 并(按规模归并)
void unionData(UFNode *a, int N, int id1, int id2)
{
    int parent1 = findPos(a, N, id1);
    int parent2 = findPos(a, N, id2);
    if(parent1 != parent2)
    {
        // a集合元素比b多
        if(a[parent1].parent < a[parent2].parent)
        {
            a[parent1].parent += a[parent2].parent;
            a[parent2].parent = parent1;
        }
        // a集合元素比b少或相等
        else
        {
            a[parent2].parent += a[parent1].parent;
            a[parent1].parent = parent2;
        }
    }
}

void ex7_25()
{
    ios::sync_with_stdio(false);
    int N, M, S, i, j, head, now, size, max_friend = 0;
    cin >> N >> M;
    UFNode uf_set[N];
    for(i = 0; i < N; i++)
        uf_set[i].id = i + 1;
    for(i = 0; i < M; i++)
    {
        cin >> S >> head;
        for(j = 1; j < S; j++)
        {
            cin >> now;
            unionData(uf_set, N, head, now);
        }
    }
    // 计算最大集合的大小
    for(i = 0; i < N; i++)
    {
        if(uf_set[i].parent < 0)
        {
            size = -uf_set[i].parent;
            if(size > max_friend)
                max_friend = size;
        }
    }
    cout << max_friend << endl;
}