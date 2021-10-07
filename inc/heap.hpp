#ifndef __HEAP_H
#define __HEAP_H

// 默认的元素大小比较函数
template<typename T>
bool defaultCmp(T a, T b) 
{ 
    return a > b; 
}  

/* 堆
 * 堆满足的条件：
 * 1、堆为完全二叉树（因而采用数组的方式存放完全二叉树）
 * 2、每个结点的元素值不小于子结点元素值(大根堆)或每个结点的元素值不大于子结点元素值(小根堆)
 */
template<typename T>
class MaxHeap{
    private:
        int curSize, maxSize;
        T *heap;
        bool (*cmp)(T a, T b);  // 返回值含义：false:a<b,true:a>=b
    public:
        MaxHeap(int m);  // 采用默认比较方法(>,<,==)
        MaxHeap(int m, bool (*cmp)(T a, T b)); // 建立空堆
        ~MaxHeap() { delete heap; }
        bool isFull() { return this->curSize > this->maxSize; }
        bool isEmpty() { return !this->curSize; }
        void insert(T value);  // 往大根堆内插入一个元素
        T eraseMaxVal();  // 从大根堆删除目标元素
};

template<typename T>
MaxHeap<T>::MaxHeap(int m) 
    : 
    curSize(0), maxSize(m)
{
    heap = new T[m];
    this->cmp = defaultCmp;
}

template<typename T>
MaxHeap<T>::MaxHeap(int m, bool (*cmp)(T a, T b)) 
    : 
    curSize(0), maxSize(m)
{
    heap = new T[m];
    this->cmp = cmp;
}

/* 插入一个元素（向上过滤）
 * 1、将新入元素放在末尾
 * 2、比较新入元素与其父结点的大小
 * 3、若新入元素>父结点，则将其与父结点换位置
 * 4、重复第三步，直至完全二叉树成为堆
 */
template<typename T>
void MaxHeap<T>::insert(T value)
{
    if(isFull())
        throw "Heap is Full.";
    T temp;
    heap[curSize] = value;
    for(int i = curSize; i > 0; i = (i - 1) / 2)
    {
        if(heap[i] > heap[(i - 1) / 2])
        {
            temp = heap[i];
            heap[i] = heap[(i - 1) / 2];
            heap[(i - 1) / 2] = temp;
        }
    }
    ++curSize;
}
/* 删除最大堆的最大元素（向下过滤）
 * 1、将末尾元素移动到根结点位置（末尾元素一定小于原堆中的所有父结点）
 * 2、堆大小减1
 * 3、找出新根结点左右孩子较大的那个，若父结点小于最大子结点，与较大的孩子互换位置
 * 4、重复第三步，直至完全二叉树成为堆
 */
template<typename T>
T MaxHeap<T>::eraseMaxVal()
{
    int i = 0, child;
    if(isEmpty())
        throw "Heap is empty.";
    T maxVal = heap[0];
    heap[0] = heap[--curSize];
    // 注意循环条件：堆一定是完全二叉树，所以如果某个结点存在子结点，则其一定有左子结点。
    while(2 * i + 1 < curSize)
    {
        // child保存当前结点的最大子结点位置，初始化为左子结点位置
        child = 2 * i + 1;
        // 若右结点存在且右子结点更大，则最大子结点为右子结点
        if((2 * i + 2 < curSize) && (heap[2 * i + 1] < heap[2 * i + 2]))
            child = 2 * i + 2;
        // 如果父结点小于最大子结点，则交换位置，检索其子结点
        if(heap[i] < heap[child])
        {
            T t = heap[i];
            heap[i] = heap[child];
            heap[child] = t;
            i = child;
        }
        else
            i++;
    }
    return maxVal;
}

#endif
