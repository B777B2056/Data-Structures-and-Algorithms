#ifndef __SET_H
#define __SET_H

#include <vector>
#include <functional>
#include <iostream>

/*并查集(Union-Find Set)*/
template<typename T>
struct SetNode
{
    T data;
    int father;  // 指向并查集树结构该处结点的父结点
};

template<typename T>
class UnionFindSet
{
    private:
        std::vector<SetNode<T> > set; //并查集
        int pathCompression(int index);  //路径压缩算法
    public:
        //创建并查集数组
        UnionFindSet(std::vector<std::vector<T> >& sets);
        ~UnionFindSet() {}
        //集合并操作(将两个数据所在集合进行并操作)
        void unionData(T a, T b, bool usePathCom);
        //集合查找操作(查找数据属于哪个集合)
        int findData(T x);
        //集合查找操作，采用路径压缩
        int findDataPathCompression(T x);
        //打印并查集树结构
        void printUFTree();
};

/* 构建并查集数组
 * sets为二维数组，每个元素为一个集合(一维数组)
 */
template<typename T>
UnionFindSet<T>::UnionFindSet(std::vector<std::vector<T> >& sets)
{
    for(int i = 0; i < sets.size(); i++)
    {
        int i_father = set.size();
        SetNode<T> node_f;
        node_f.data = sets[i][0];
        node_f.father = -sets[i].size();
        set.push_back(node_f);
        for(int j = 1; j < sets[i].size(); j++)
        {
            SetNode<T> node;
            node.data = sets[i][j];
            node.father = i_father;
            set.push_back(node);
        }
    }
}

/* 集合并操作(将两个数据所在集合进行并操作)
 * 归并的基本思路：先找到两个元素所在的集合，再将b元素所在集合合并在a元素所在集合中
 * 优化方法：按秩(Rank,即树高)归并、按规模(Size)归并
 * 注：本处采用按规模归并，参数usePathCom指示是否采用路径压缩算法，true为采用路径压缩算法
 * 1、按秩归并
 *    树高小的树贴到树高更高的树上，并更新树高；
 *    每棵树根结点的father结点保存树高，根结点.father = -树高；
 *    注意两树同高的情况，归并后新树高=原树高+1
 * 2、按规模归并
 *    元素数量小的树贴到元素数量更多的树上，并更新该集合的元素数量；
 *    每棵树根结点的father结点保存元素数量，根结点.father = -元素数量
 */
template<typename T>
void UnionFindSet<T>::unionData(T a, T b, bool usePathCom)
{
    int father_a, father_b;
    if(usePathCom)
    {
        father_a = findDataPathCompression(a);
        father_b = findDataPathCompression(b);
    }
    else
    {
        father_a = findData(a);
        father_b = findData(b);
    }
    if(father_a >= 0 && father_b >= 0)
    {
        if(father_a == father_b) return;  //两元素属于同一集合
        if(set[father_a].father > set[father_b].father)
        {
            set[father_b].father += set[father_a].father;
            set[father_a].father = father_b; 
        }
        else
        {
            set[father_a].father += set[father_b].father;
            set[father_b].father = father_a;
        }
    }
}

/* 集合查找操作(查找数据属于哪个集合,即该集合所在树结构的根结点)
 * 返回值为该元素所在集合的树结构的根结点的索引,若为-1则说明未找到该元素
 * 思路：先查找到目标元素所在位置，即树的非根结点，再向上查找到树的根结点即可 
 */ 
template<typename T>
int UnionFindSet<T>::findData(T x)
{
    /*查找该元素所在的位置*/
    int i;
    for(i = 0; i < set.size(); i++)
    {
        if(set[i].data == x)
            break;
    }
    /*未查找到该元素，返回-1*/
    if(i >= set.size()) return -1;
    /*从目标元素结点位置向上查找其所在树的根节点*/
    while(i < set.size() && set[i].father >= 0)
    { 
        i = set[i].father; 
    }
    return i;
}

/* 采用路径压缩的并查集查找操作
 * 
 */
template<typename T>
int UnionFindSet<T>::findDataPathCompression(T x)
{
    /*查找该元素所在的位置*/
    int i;
    for(i = 0; i < set.size(); i++)
    {
        if(set[i].data == x)
            break;
    }
    /*未查找到该元素，返回-1*/
    if(i >= set.size()) return -1;
    /*路径压缩*/
    i = pathCompression(i);
    return i;
}

template<typename T>
int UnionFindSet<T>::pathCompression(int index)
{
    return set[index].father < 0 ? index : set[index].father = pathCompression(set[index].father);
}

template<typename T>
void UnionFindSet<T>::printUFTree()
{
    /*打印并查集树结构*/
    for(int m = 0; m < set.size(); m++)
    {
        std::cout << "Data = " << set[m].data << ", Index = " << m << ", Father = " << set[m].father << std::endl;
    }
}

#endif
