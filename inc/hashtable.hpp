#ifndef __HASH_H
#define __HASH_H

#include <iostream>

/*选择解决冲突的方法*/
enum HashMethod{LinearDetection, SquareDetection, SeparateChaining};  

/* 基于数组的简单哈希表实现（key类型暂时只能为int，M为value类型）
 * 装载因子默认为0.75
 */
template<typename M>
class HashTable
{
    protected:
        /*保存的数据的状态枚举(空，已删除，已填充)*/
        enum Status{EMPTY, FILLED, DELETED};
        /*键-值对*/
        struct Data
        {
            int key;
            M value;
            Status st;
            Data() : st(EMPTY) {}
            Data(int k, M v, Status s) : key(k), value(v), st(s) {}
        };
        /*链表结点定义（用于分离链接法）*/
        struct LNode
        {
            Data kvp;
            LNode *next;
            LNode() : next(nullptr) {}
        };
        HashMethod me;
        int tableSize;  // 哈希表数组的长度
        int elemSize;  // 哈希表中实际存放的元素个数
        double alpha;  // 装载因子
        Data *array;  // 存放各键值对的数组（针对采用开放定址法的哈希表）
        LNode **lists;  // 存放各链表头结点的数组（针对采用分离链接法的哈希表）
        /*哈希方法（散列函数）*/
        int hashMethod(int keyWord);
        /*解决key冲突的方法*/
        int linearDetection(int base, int i);  // 开放定址法之线性探测法（开放定址法包括线性探测法、平方探测法与双散列法）
        int squareDetection(int base, int i);  // 开放定址法之平方探测法
        void separateChaining(int base, Data& val);  // 分离链接法（在产生key冲突的位置采用链表保存冲突的键-值对）

    public:
        HashTable(int size, double loadFactor = 0.75, HashMethod m = SeparateChaining);
        ~HashTable();
        void insert(int key, M value);  // 插入一个键值对
        int find(int key, M *value);  // 返回键值为key的value值
        bool erase(int key);  // 删除键值为key的某个键-值对
};

/* 初始化哈希表数组长度与装载因子
 */
template<typename M>
HashTable<M>::HashTable(int size, double loadFactor, HashMethod m) 
    : elemSize(size), alpha(loadFactor), me(m)
{
    array = new Data[tableSize];
    lists = new LNode*[tableSize];
    tableSize = elemSize / alpha;
    for(int i = 0; i < tableSize; i++)
    {
        lists[i] = new LNode();
        (lists[i]->kvp).st = EMPTY;
    }
}

template<typename M>
HashTable<M>::~HashTable()
{
    delete []array;
    for(int i = 0; i < tableSize; i++)
    {
        while(lists[i])
        {
            LNode *temp = lists[i]->next;
            delete lists[i];
            lists[i] = temp;
        }
    }
    delete []lists;
}

/* 哈希方法
 * 采用除留取余法(对键-值对的内存地址除留取余)
 */
template<typename M>
inline
int HashTable<M>::hashMethod(int key)
{
    return key % tableSize;
}

/* 线性探测法解决key冲突
 * 冲突次数i为基于原始位置进行偏移，每次正向偏移i（向右），i为冲突发生的次数
 * 返回经过调整后的索引值
 * 注意：是基于原始位置偏移！原始位置不可改变！
 * 特点：表中所有位置均可探测到，但容易产生“聚集现象”
 * 开放定址法基本公式：newPos = (basePos + d(i)) % tableSize，其中d(i)为关于冲突次数i的具体方法
 */
template<typename M>
inline
int HashTable<M>::linearDetection(int base, int i)
{
    int newPos = (base + i) % tableSize;
    return newPos;
}

/* 平方探测法解决key冲突
 * 冲突次数i为基于原始位置进行偏移，奇数则正向偏移+i^2（向右），为偶数则反向偏移-i^2（向左）
 * 返回经过调整后的索引值
 * 注意：是基于原始位置偏移！原始位置不可改变！
 * 特点：缓解了线性探测的聚集现象，但可能会发生一种情况————表中有空位但是无法探测到。
 *      （本处的处理方法是在插入时检测探测到的新位置是否等于起始位置，若等于则抛出异常）
 */
template<typename M>
int HashTable<M>::squareDetection(int base, int i)
{
    int cof, newPos;  // cof为单次偏移量
    // cof计算公式：考虑到一个变量i对应两个偏移量，因此写为如下形式
    // 例子：
    // conflict: 1     2     3      4  
    // +-i^2:  -1 1  -4 4  -9 9  -16 16
    cof = ((i % 2) ? (((i + 1) / 2) * ((i + 1) / 2)) : (- (i / 2) * (i / 2)));
    newPos = (base + cof) % tableSize;
    return newPos;
}

/* 分离链接法解决key冲突
 * 在产生key冲突的位置采用链表保存冲突的键-值对
 * 将冲突的键-值对挂在对应链表的后面
 */
template<typename M>
void HashTable<M>::separateChaining(int base, Data& val)
{
    LNode *h = lists[base];
    LNode *v = new LNode();
    v->kvp = val;
    while(h->next)
        h = h->next;
    h->next = v;
}

/*向哈希表中插入一个键-值对*/
template<typename M>
void HashTable<M>::insert(int key, M value)
{
    // 检查该key是否已存在，若已存在则什么都不做
    M v;
    if(find(key, &v) == -1)
    {
        Data k(key, value, FILLED);
        // 生成初始哈希值
        int basePos = hashMethod(key);
        if(this->me == LinearDetection)
        {
            // 初始化新位置
            int newPos = basePos;
            // 初始化冲突次数
            int conflict = 0;  
            // 开放定址法解决冲突
            while(array[newPos].st == FILLED)
                newPos = linearDetection(basePos, ++conflict);  
            array[newPos] = k;
            array[newPos].st = FILLED;
            std::cout << "key = " << key << ", postion = " << newPos << "\n";
        }
        else if(this->me == SquareDetection)
        {
            // 初始化新位置
            int newPos = basePos;
            // 初始化冲突次数
            int conflict = 0;  
            // 开放定址法解决冲突
            while(array[newPos].st == FILLED)
            {
                newPos = squareDetection(basePos, ++conflict);  
                if(newPos == basePos)
                    throw "ERROR: Square Detection FAILED.";  // 平方探测失效
            }
            array[newPos] = k;
            array[newPos].st = FILLED;
            std::cout << "key = " << key << ", postion = " << newPos << "\n";
        }
        else
        {
            // 分离链接法解决冲突
            if(lists[basePos]->next)
                separateChaining(basePos, k);
            // 若不存在冲突，则在头结点后挂上新结点
            else
            {
                LNode *ln = new LNode();
                ln->kvp = k;
                lists[basePos]->next = ln;
            }
        }
    }
}

/* 返回键值为key的value值 */
template<typename M>
int HashTable<M>::find(int key, M *value)
{
    // 生成初始哈希值
    int basePos = hashMethod(key);  
    if(this->me == LinearDetection)
    {
        // 初始化偏移量
        int newPos = basePos;
        // 初始化冲突次数
        int conflict = 0;
        // 保存basePos初始值
        int s = basePos;
        // 开放定址法寻找目标key
        while(key != array[newPos].key)
        {
            newPos = linearDetection(basePos, ++conflict);
            // 返回原点了，说明该key不存在后续语句无需执行
            if(newPos == s)
            {
                value = nullptr;
                return -1;
            }
        }
        // 检查目标key的状态，若为已删除则查找失败
        if(array[newPos].st == DELETED)
        {
            value = nullptr;
            return -1;
        }
        else
        {
            *value =  array[newPos].value;
            return newPos;
        }
    }
    else if(this->me == SquareDetection)
    {
        // 初始化偏移量
        int newPos = basePos;
        // 初始化冲突次数
        int conflict = 0;
        // 保存basePos初始值
        int s = basePos;
        // 开放定址法寻找目标key
        while(key != array[newPos].key)
        {
            newPos = squareDetection(basePos, ++conflict);
            // 返回原点了，说明该key不存在后续语句无需执行
            if(newPos == s)
            {
                value = nullptr;
                return -1;
            }
        }
        // 检查目标key的状态，若为已删除则查找失败
        if(array[newPos].st == DELETED)
        {
            value = nullptr;
            return -1;
        }
        else
        {
            *value =  array[newPos].value;
            return newPos;
        }
    }
    else
    {
        // 在对应链表中查找对应key
        for(LNode *t = lists[basePos]; t != nullptr; t = t->next)
        {
            if((t->kvp).key == key)
            {
                // 检查目标key的状态，若为已删除则查找失败
                if((t->kvp).st == DELETED)
                {
                    value = nullptr;
                    return -1;
                }
                else
                {
                    *value = (t->kvp).value;
                    return basePos;
                }
            }
        }
        // 该key不存在
        return -1;
    }
}

/* 删除键值为key的某个键-值对
 * 1、针对采用“开放定址法”解决冲突的哈希表
 *    为防止删除某个键-值对后导致断链，所以采用“懒惰删除”法
 *    即：并不真正的删除该元素，只是把该元素的访问标志数组设置为false，让新的元素可以覆盖它
 * 2、针对采用“分离链接法”解决冲突的哈希表
 *    将相应链表结点删除即可
 */
template<typename M>
bool HashTable<M>::erase(int key)
{
    // 生成初始哈希值
    int basePos = hashMethod(key);  
    if(this->me == LinearDetection || this->me == SquareDetection)
    {
        M v;
        int pos = find(key, &v);
        if(pos == -1)
            return false;
        else
            array[pos].st = DELETED;  // 置访问标志为DELETED
        return true;
    }
    else
    {
        // 在对应链表中查找对应key
        for(LNode *t = lists[basePos]; t != nullptr; t = t->next)
        {
            if(t->next)
            {
                if((t->next->kvp).key == key)
                {
                    LNode *temp = t->next;
                    t->next = t->next->next;
                    delete temp;
                    return true;
                }
            }
        }
        return false;
    }
}

#endif
