#ifndef __GRAPH_H
#define __GRAPH_H

#include "stack_queue.hpp"
#include "set.hpp"
#include <assert.h>
#include <iostream>
#include <vector>

enum Method{DFS, BFS, Dijkstra, Floyd, Prim, Kruskal};

/*有向带权图*/
template<typename T>
class Graph
{
    protected:
        int nodeNum, edgeNum;  // 图的结点数量，图的边数量
        T *vertex;  // 保存顶点内容的数组
        int **adjacencyMatrix;  // 图的邻接矩阵
        int *pathSingleSource, *distance;  // Dijkstra算法需要,pathSingleSource为源点到其他结点的最短路径，distance为对应的最短距离（最小权重和）
        int **pathMultipleSource, **D;  // Floyd算法需要，D为任意两顶点间最短距离，pathMultipleSource为任意两顶点间最短路径
        bool *dfs_visted, *bfs_visted;  // 第i个结点是否被访问过
        struct Edge{ int start, end, weight; };  // 边定义(用于Kruskal算法)
        int *primMST;  // prim算法最小生成树（保留父结点位置）
        Edge *kruskalMST;  // Kruskal算法最小生成树（保留父结点位置）
        void _DFS(int entrance);  // 深度优先遍历图，入参为入口结点
        void _BFS(int entrance);  // 广度优先遍历图，入参为入口结点
        void _shortestPathDijkstra(int sourceVertx);  // 图中顶点sourceVertx（源点）到其他任意结点的最短路径（Dijkstra算法）
        void _shortestPathFloyd();  // 图中任意顶点之间的最短路径（Floyd算法）
        bool _Prim(int root);  // Prim算法得到连通无环图最小生成树，更侧重结点
        bool _Kruskal();  // Kruskal算法得到连通无环图最小生成树，更侧重边，这个算法也可以用于检测图中是否有环
        
    public:
        Graph(int nodeNum, int edgeNum);  // 初始化图结构
        ~Graph();  // 销毁图对象
        void createVertx(T *data);  // 创建无边图
        void insertEdge(int begin, int end, int weight);  // 插入一条边
        void traversal(Method m);  // m用于选择遍历方式，可以遍历非连通图
        void shortestPath(int start, int end, Method m);  // 打印指定结点间的最短路径
        bool MST(int root, Method m);  // 得到图的最小生成树，并打印
        void topologicalSortAOV();  // AOV网络拓扑排序，打印排序后的结果
};

template<typename T>
Graph<T>::Graph(int nodeNum, int edgeNum) 
    : distance(nullptr), D(nullptr)
    , pathSingleSource(nullptr), pathMultipleSource(nullptr)
{
    this->nodeNum = nodeNum;
    this->edgeNum = edgeNum;
    vertex = new T[this->nodeNum];  
    dfs_visted = new bool[this->nodeNum];
    bfs_visted = new bool[this->nodeNum];
    for(int i = 0; i < this->nodeNum; i++)
    {
        dfs_visted[i] = false;
        bfs_visted[i] = false;
    }
    adjacencyMatrix = new int*[this->nodeNum];  // 先分配二维数组的外层
    for(int i = 0; i < this->nodeNum; i++)
        adjacencyMatrix[i] = new int[this->nodeNum];  // 再分配每一行的一维数组的空间
    for(int i = 0; i < this->nodeNum; i++)
    {
        for(int j = 0; j < this->nodeNum; j++)
            adjacencyMatrix[i][j] = __INT_MAX__;  // 邻接矩阵边权重初始化为无穷大
    }
}

template<typename T>
Graph<T>::~Graph()
{
    delete []vertex;
    for(int i = 0; i < this->nodeNum; i++)
        delete []adjacencyMatrix[i];
    delete []adjacencyMatrix;
}

/* 创建图的所有结点
 * 图必须有至少一个结点，但可以没有边
 */
template<typename T>
void Graph<T>::createVertx(T *data)
{
    for(int i = 0; i < nodeNum; i++)
        vertex[i] = data[i];
}

/* 插入图的一条边并更新邻接矩阵
 * begin入参为边出发结点的索引，end入参为边终止结点的索引
 * 邻接矩阵adjacencyMatrix[i][j]表示从第i个图结点到第j个图结点的边权重，若为无穷大则表示两结点没有边
 */
template<typename T>
void Graph<T>::insertEdge(int begin, int end, int weight)
{
    assert((begin >= 0 && begin < nodeNum) && (end >= 0 && end < nodeNum));
    /*填充邻接矩阵*/
    adjacencyMatrix[begin][end] = weight;
}

/*深度优先搜索遍历连通图的所有结点*/
template<typename T>
void Graph<T>::_DFS(int entrance)
{
    //若当前结点已被访问，即返回
    if(dfs_visted[entrance]) return;
    //将当前结点置为“已访问”
    dfs_visted[entrance] = true;
    //对当前结点进行操作
    std::cout << vertex[entrance] << " ";
    //遍历与当前结点连通的未访问结点，递归
    for(int i = 0; i < nodeNum; i++)
    {
        if(adjacencyMatrix[entrance][i] != __INT_MAX__)
        {
            if(!dfs_visted[i])
                _DFS(i);
        }
    }
}

/*广度优先搜索遍历连通图的所有结点*/
template<typename T>
void Graph<T>::_BFS(int entrance)
{
    //入口结点入队
    Queue<int> q;
    q.enQueue(entrance); 
    //队列不空时循环
    while(!q.isEmpty())
    {
        //结点出队
        int curNode = q.deQueue();
        //若当前结点已被访问，即返回
        if(bfs_visted[curNode]) continue;
        //将当前结点置为“已访问”
        bfs_visted[curNode] = true;
        //对当前结点进行操作
        std::cout << vertex[curNode] << " ";
        //与当前结点连通的未访问结点入队
        for(int i = 0; i < nodeNum; i++)
        {
            if(adjacencyMatrix[curNode][i] != __INT_MAX__)
            {
                if(!bfs_visted[i])
                    q.enQueue(i);
            }
        }
    }
}

/* 遍历图的所有结点，无论图是否连通
 * 将图中每个结点都当作DFS/BFS入口结点进行遍历即可
 */
template<typename T>
void Graph<T>::traversal(Method m)
{
    for(int i = 0; i < nodeNum; i++)
    {
        if(m == DFS)
            _DFS(i);
        else if(m == BFS)
            _BFS(i);
        else
            return;
    }
}

/* 迪加斯特拉算法：求图的单源最短路径
 * 注：一定不能存在负值圈（即图中有一回路权重和为负数）
 */
template<typename T>
void Graph<T>::_shortestPathDijkstra(int sourceVertx)
{
    int i;
    //新建标志数组，作用类似两个visited数组
    bool collected[nodeNum];
    for(i = 0; i < nodeNum; i++)
        collected[i] = false;
    collected[sourceVertx] = true;
    //初始化path数组(path[i]的含义：从源点到第i个结点所经过的最短路径的倒数第二个结点)
    pathSingleSource = new int[nodeNum];
    for(i = 0; i < nodeNum; i++)
        pathSingleSource[i] = -1;
    //初始化distance数组
    distance = new int[nodeNum];
    for(i = 0; i < nodeNum; i++)
        distance[i] = __INT_MAX__;
    //扫描源点的所有邻接点，源点的邻接点均初始化为与源点边上的权重
    for(i = 0; i < nodeNum; i++)
    {
        if(adjacencyMatrix[sourceVertx][i] != __INT_MAX__)
            distance[i] = adjacencyMatrix[sourceVertx][i];
    }
    while(true)
    {
        //找与当前结点最小距离且未被访问过的结点
        int minVertex = -1, min = __INT_MAX__;
        for(int i = 0; i < nodeNum; i++)
        {
            if(distance[i] < min && !collected[i])
            {
                min = distance[i];
                minVertex = i;
            }
        }
        //未找到，意味着已经查找过所有结点了，就跳出循环
        if(minVertex == -1)
            break;
        //当前最小距离结点标记为已访问
        collected[minVertex] = true;
        //遍历当前最小距离结点的所有邻接点
        //看看是否存在 源点->当前当前最小距离结点->当前最小距离结点邻接点的总距离 < 源点->当前最小距离结点的邻接点
        //若存在，且该邻接点未被访问过，则更新距离与路径
        for(i = 0; i < nodeNum; i++)
        {
            if(!collected[i] && adjacencyMatrix[minVertex][i] < __INT_MAX__)
            {
                if(distance[minVertex] + adjacencyMatrix[minVertex][i] < distance[i])
                {
                    distance[i] = distance[minVertex] + adjacencyMatrix[minVertex][i];
                    pathSingleSource[i] = minVertex;
                }
            }
        }
    }
}

/* Floyd算法，求图的多源最短路径
 * 注：一定不能存在负值圈（即图中有一回路权重和为负数）
 */
template<typename T>
void Graph<T>::_shortestPathFloyd()
{
    int i, j, k;
    //初始化D数组为邻接矩阵
    D = new int*[nodeNum];  
    for(i = 0; i < nodeNum; i++)
        D[i] = new int[nodeNum]; 
    for(i = 0; i < nodeNum; i++)
    {
        for(j = 0; j < nodeNum; j++)
            D[i][j] = adjacencyMatrix[i][j];
    }
    //path全部初始化为-1
    pathMultipleSource = new int*[nodeNum];  
    for(i = 0; i < nodeNum; i++)
        pathMultipleSource[i] = new int[nodeNum]; 
    for(i = 0; i < nodeNum; i++)
    {
        for(j = 0; j < nodeNum; j++)
            pathMultipleSource[i][j] = -1;
    }
    //寻找是否有k使得结点i->结点k->结点j的距离 < 结点i->结点j的距离成立，若成立则更新最短距离与最短路径
    for(k = 0; k < nodeNum; k++)
    {
        for(i = 0; i < nodeNum; i++)
        {
            for(j = 0; j < nodeNum; j++)
            {
                // 一定要记得判断i与k、k与j是不是邻接点！！！
                if((i != j) && (D[i][k] < __INT_MAX__) && (D[k][j] < __INT_MAX__))
                {
                    if(D[i][k] + D[k][j] < D[i][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                        pathMultipleSource[i][j] = k;
                    }
                }
            }
        }
    }
}

template<typename T>
void Graph<T>::shortestPath(int start, int end, Method m)
{
    if(m == Dijkstra)
    {
        if(!distance)
            _shortestPathDijkstra(start);
        if(distance[end] == __INT_MAX__)
        {
            std::cout << "Shortest path from " 
                      << vertex[start] << " to " 
                      << vertex[end] << " does not exist." 
                      << std::endl;
            return;
        }
        /*打印最短距离*/
        std::cout << "Start vertex: " << vertex[start] << ", End vertex: " << vertex[end] << std::endl;
        std::cout << "Minimum distance: " << distance[end] << std::endl;
        /*打印最短路径*/
        std::cout << "Shortest Path By Dijkstra: ";
        Stack<int> s;
        while(end != -1)
        {
            s.push(end);
            end =  pathSingleSource[end];
        }
        std::cout << vertex[start];
        while(!s.isEmpty())
        {
            std::cout << "->" << vertex[s.getTop()];
            s.pop();
        }
        std::cout << "\n";
    }
    else if(m == Floyd)
    {
        if(!D)
            _shortestPathFloyd();
        if(D[start][end] == __INT_MAX__)
        {
            std::cout << "Shortest path from " 
                      << vertex[start] << " to " 
                      << vertex[end] << " does not exist." 
                      << std::endl;
            return;
        }
        /*打印最短距离*/
        std::cout << "Start vertex: " << vertex[start] << ", End vertex: " << vertex[end] << std::endl;
        std::cout << "Minimum distance: " << D[start][end] << std::endl;
        /*打印最短路径*/
        std::cout << "Shortest Path By Floyd: ";
        Stack<int> s;
        while(end != -1)
        {
            s.push(end);
            end =  pathMultipleSource[start][end];
        }
        std::cout << vertex[start];
        while(!s.isEmpty())
        {
            std::cout << "->" << vertex[s.getTop()];
            s.pop();
        }
        std::cout << "\n";
    }
    else
        return;
}


/* Prim算法求最小生成树
 * 最小生成树性质：
 * 1、图内所有结点树内也都有；
 * 2、树中所有边均为图中的边，且个数为图结点数-1；
 * 3、只有连通图才有生成树；
 * 4、最小生成树是图的生成树里边权和最小的生成树。
 * 注：最小生成树只针对无向图！！！有向图的对应概念称为“最小树形图”。
 */
template<typename T>
bool Graph<T>::_Prim(int root)
{
    int i, cnt = 1;
    int dist[nodeNum];
    primMST = new int[nodeNum];
    //dist数组（保存各结点与当前prim树的距离，距离为0表示该结点已在prim树内）初始化
    for(i = 0; i < nodeNum; i++)
    {
        dist[i] = adjacencyMatrix[root][i];
    }
    dist[root] = 0;
    //prim树初始化
    for(i = 0; i < nodeNum; i++)
    {
        primMST[i] = root;
    }
    primMST[root] = -1;
    //搜索所有结点，收录满足条件的结点；即：距离当前prim树最近但未被收录的结点（未被收录的结点即dist不为0的结点）
    while(true)
    {
        int minVertex, minDist = __INT_MAX__;
        bool isFind = false;
        for(i = 0; i < nodeNum; i++)
        {
            if((dist[i] != 0) && (dist[i] < minDist))
            {
                minDist = dist[i];
                minVertex = i;
                isFind = true;
            }
        }
        if(!isFind) break;  // 已经没有满足条件的结点了，结束循环
        dist[minVertex] = 0;  //当前与prim树距离最小的结点标记为已访问(dist=0)，即将该结点收录进prim树内
        cnt++;  // 树结点计数
        //遍历当前与prim树距离最小的结点的所有邻接点中未被收录的结点
        //看看是否存在 prim树->当前最小距离结点->当前结点的邻接点中未被收录的结点的总距离 < prim树->当前结点的邻接点中未被收录的结点
        //注：prim树->当前最小距离结点->当前结点的邻接点中未被收录的结点的总距离 == 当前最小距离结点与该邻接点的边权
        //若存在，且该邻接点未被访问过，则更新该邻接点与prim树的距离与prim树
        for(i = 0; i < nodeNum; i++)
        {
            if((dist[i] != 0) && adjacencyMatrix[minVertex][i] < __INT_MAX__)
            {
                if(adjacencyMatrix[minVertex][i] < dist[i])
                {
                    dist[i] = adjacencyMatrix[minVertex][i];
                    primMST[i] = minVertex;
                }
            }
        }
    }
    //检查得到的最小生成树是否满足要求：检查所有图结点是否已收录；若不满足则说明该无向图不连通，不存在生成树，返回false。
    return cnt == nodeNum;
}

template<typename T>
bool Graph<T>::_Kruskal()
{
    /*从邻接矩阵构造边集合，采用容器（这里采用数组配合访问标志位）存储边*/
    int i, j, k = 0, collEdge = 0;
    Edge e[edgeNum];
    bool v[edgeNum];
    for(i = 0; i < edgeNum; i++)
        v[i] = false;
    for(i = 0; i < nodeNum; i++)
    {
        for(j = 0; j < nodeNum; j++)
        {
            if(adjacencyMatrix[i][j] < __INT_MAX__)
            {
                e[k].start = i;
                e[k].end = j;
                e[k].weight = adjacencyMatrix[i][j];
                k++;
            }
        }
    }
    /*并查集初始化*/
    std::vector<std::vector<int> > vec;
    for(i = 0; i < nodeNum; i++)
        vec.push_back(std::vector<int> (1, i));
    UnionFindSet<int> ufs(vec);
    /*Kruskal最小生成树初始化（存放MST内互相连接的边）*/
    k = 0;
    kruskalMST = new Edge[nodeNum - 1];
    /*Kruskal算法*/
    while(collEdge < nodeNum - 1)
    {
        /*从已有边集合中取出一条权重最小的边*/
        int minEdgeIndex, minWeightEdge = __INT_MAX__;
        bool isFind = false;
        for(i = 0; i < edgeNum; i++)
        {
            if(!v[i] && (e[i].weight < minWeightEdge))
            {
                minWeightEdge = e[i].weight;
                minEdgeIndex = i;
                isFind = true;
            }
        }
        if(!isFind) break;
        /*将权重最小边从边集合中删除：标记为已访问*/
        v[minEdgeIndex] = true;
        /*检查当前最小边的加入会不会在MST中构成回路(检查当前最小边的起始、终止结点是否在同一个集合内，若在则会构成回路)*/
        if(ufs.findData(e[minEdgeIndex].start) != ufs.findData(e[minEdgeIndex].end))
        {
            collEdge++;
            kruskalMST[k++] = e[minEdgeIndex];
            ufs.unionData(e[minEdgeIndex].start, e[minEdgeIndex].end, true);  // 将两个结点并入对应的集合
        }
    }
    //检查得到的最小生成树是否满足要求：树中边个数为图结点数-1；若不满足则说明该图有环，不存在生成树，返回false。
    return collEdge == nodeNum - 1;
}

/*打印无向图的最小生成树*/
template<typename T>
bool Graph<T>::MST(int root, Method m)
{
    if(m == Prim)
    {
        if(_Prim(root))
        {
            std::cout << "MST's root is vertex " << vertex[root] << std::endl; 
            for(int i = 0; i < nodeNum; i++)
            {
                if((i != root) && (primMST[i] >= 0))
                    std::cout << "Vertex " << vertex[i] 
                              << "\'s father node in MST is vertex " 
                              << vertex[primMST[i]] 
                              << ", edge's weight is "
                              << adjacencyMatrix[i][primMST[i]]
                              << std::endl; 
            }
            return true;
        }
        else
        {
            std::cout << "The graph is not full connected, it has no MST." << std::endl;
            return false;
        }
    }
    if(m == Kruskal)
    {
        if(_Kruskal())
        {
            for(int i = 0; i < nodeNum - 1; i++)
            {
                std::cout << "Vertex " << vertex[kruskalMST[i].start]
                          << " to Vertex " << vertex[kruskalMST[i].end]
                          << ", edge's weight is "
                          << kruskalMST[i].weight
                          << std::endl;
            }
            return true;
        }
        else
        {
            std::cout << "The graph at least has one circle, it does not have MST." << std::endl;
            return false;
        }
    }
    return false;
}

/* AOV网络拓扑排序（AOV网络中，顶点保存活动信息）
 * 核心思想：寻找入度为0的结点，每次输出一层这些结点；再调整各结点入度，重复这一过程直到完成对所有结点的操作或者没有入度为0的结点为止。
 * 注：AOV网络一定是有向无环图！
 */
template<typename T>
void Graph<T>::topologicalSortAOV()
{
    /*访问标记数组与存放入度为0的结点的容器（这里采用队列）*/
    bool v[nodeNum];
    Queue<int> zeroInDegree;
    /*通过邻接矩阵计算各结点的入度（采用邻接表的方式对于求入度更合适）*/
    int i, j, indegree[nodeNum];
    for(i = 0; i < nodeNum; i++)
    {
        v[i] = false;
        indegree[i] = 0;
    }
    for(i = 0; i < nodeNum; i++)
    {
        /*计算各结点的入度(列在外层循环，行在内层循环)*/
        for(j = 0; j < nodeNum; j++)
        {
            if(adjacencyMatrix[j][i] < __INT_MAX__)
                indegree[i]++;
        }
        /*入度为0的结点入队*/
        if(indegree[i] == 0)
        {
            v[i] = true;
            zeroInDegree.enQueue(i);
        }
    }
    /*寻找入度为0的结点并打印，再更新其余结点的入度*/
    for(i = 0; i < nodeNum; i++)
    {
        /*如果不存在入度为0的结点，那么说明图中有环，不可以进行拓扑排序*/
        if(zeroInDegree.isEmpty())
        {
            std::cout << "The graph at least has one circle, it cannot be sorted by topological.\n";
            break;
        }
        /*入度为0的结点出队*/
        int m = zeroInDegree.deQueue();
        std::cout << vertex[m] << " ";
        /*更新其余结点的入度(即当前入度为0结点的邻接点的入度减1)*/
        for(j = 0; j < nodeNum; j++)
        {
            if(adjacencyMatrix[m][j] < __INT_MAX__)
                indegree[j]--;
        }
        /*扫描一遍，将入度为0的且未访问过的新结点入队*/
        for(j = 0; j < nodeNum; j++)
        {
            if(!v[j] && (indegree[j] == 0))
            {
                v[j] = true;
                zeroInDegree.enQueue(j);
            }
        }
    }
}

#endif
