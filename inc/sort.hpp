#ifndef __SORT_H
#define __SORT_H

/*稳定的排序算法的含义：经过排序后，相同的元素之间相对顺序不变，则排序算法稳定*/

/* 冒泡排序
 * 最坏情况时间复杂度：O(n^2)
 * 特点：稳定的排序算法
 * 思路：每次从头比较相邻两元素，若前一个元素严格大于后一个元素，则二者交换位置（相当于找出最大值后扔到最底下）；一共进行N-1轮。
 */
template<typename T>
void bubbleSort(int N, T *array)
{
    int i, j;
    for(i = 0; i < N - 1; i++)
    {
        for(j = 0; j < N - i - 1; j++)
        {
            //比较相邻两元素，若前一个元素严格大于后一个元素，则二者交换位置
            if(array[j] > array[j + 1])
            {
                T temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

/* 插入排序
 * 最坏情况时间复杂度：O(n^2)
 * 特点：稳定的排序算法；当序列基本有序时排序很快
 * 思路：每一步将一个待排序的数据与前面已经排好序的有序序列每个元素进行比较，再插入到有序序列的合适位置中，直到插完所有元素为止。
 */
template<typename T>
void insertSort(int N, T *array)
{
    int i, j;
    T temp;
    for(i = 1; i < N; i++)
    {
        temp = array[i];
        for(j = i - 1; (j >= 0) && (temp < array[j]); j--)
            array[j + 1] = array[j];
        array[j + 1] = temp;
    }
}

/* 希尔排序
 * 是插入排序的改进算法
 * 特点：不稳定的排序算法；平均时间复杂度依赖于增量序列的选取。（这里采用Hibbard序列）
 * 思路：自定义一个增量序列D（所有元素严格递增，首元素为1），从D中最后一个元素开始（即D中最大元素），
 *       以D[k]为间隔进行插入排序，直到遍历完增量序列D。
 */
template<typename T>
void shellSort(int N, T *array)
{
    int i, j, k, sizeH = N, Hibbard[N];
    T temp;
    // 构造Hibbard序列(Hibbard[0] = 1, Hibbard[k] = 2 * Hibbard[k - 1] + 1)
    Hibbard[0] = 1;
    for(k = 1; k < N; k++)
    {
        Hibbard[k] = 2 * Hibbard[k - 1] + 1;
        if(Hibbard[k] >= N)
        {
            sizeH = k;
            break;
        }
    }
    for(k = sizeH - 1; k >= 0; k--)
    {
        // 进行Hibbard[k]间隔插入排序
        for(i = Hibbard[k]; i < N; i+=Hibbard[k])
        {
            temp = array[i];
            for(j = i -  Hibbard[k]; (j >= 0) && (temp < array[j]); j-= Hibbard[k])
                array[j + Hibbard[k]] = array[j];
            array[j + Hibbard[k]] = temp;
        }
    }
}

/* 选择排序
 * 平均时间复杂度与如何选定最小元素有关。若使用最小堆，则平均时间复杂度为O(N*logN)；若线性扫描，则为O(N^2)。
 * 思路：每次选出无序序列中的最小元素（有序序列为0~i-1，i~N-1为无序序列），将最小元素与有序序列末元素交换位置。
 */
template<typename T>
void selectionSort(int N, T *array)
{
    int i, j, minPos;
    // 进行排序
    for(i = 0; i < N; i++)
    {
        minPos = i;
        for(j = i; j < N; j++)
        {
            if(array[minPos] > array[j])
                minPos = j;
        }
        T temp = array[minPos];
        array[minPos] = array[i];
        array[i] = temp;
    }
}

/*堆的向下过滤：用于将已构建好的完全二叉树调整为堆*/
template<typename T>
void filterDown(int heapSize, T *array)
{
    int i = 0, child;
    while(2 * i + 1 < heapSize)
    {
        // child保存当前结点的最大子结点位置，初始化为左子结点位置
        child = 2 * i + 1;
        // 若右结点存在且右子结点更大，则最大子结点为右子结点
        if((2 * i + 2 < heapSize) && (array[2 * i + 1] < array[2 * i + 2]))
            child = 2 * i + 2;
        // 如果父结点小于最大子结点，则交换位置；否则无需交换，跳出循环
        if(array[i] < array[child])
        {
            T t = array[i];
            array[i] = array[child];
            array[child] = t;
            i = child;
        }
        else
            i++;
    }
}

/* 堆排序
 * 利用了堆这种数据结构，是对选择排序的一种改进
 * 任何情况下时间复杂度均为O(N*logN)
 * 特点：原地排序
 * 思路：1、首先将原数组调整为最大堆(从第一个非叶子节点开始向下过滤)；
 *       2、考虑到排序后的数组，最大元素在索引N-1位置，因此将最大堆中顶点与数组N-1位置的元素交换位置，
 *          并将交换位置后的数组N-1位置的元素排除在堆之外（相当于删除堆的顶点，同时也进行了原地排序）；
 *       3、将堆中剩余元素调整为最大堆(向下过滤)；
 *       4、 回到第2步，直到堆空。
 */
template<typename T>
void heapSort(int N, T *array)
{
    int i, j, parent, heapSize = N;
    T temp;
    // 原地建堆
    for(i = (N - 2) / 2; i >= 0; i--)
    {
        filterDown(heapSize, array);
    }
    // 进行排序
    for(i = N - 1; i >= 0; i--)
    {
        // 将堆顶与无序序列的末尾元素交换
        temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        // 缩小堆的大小
        --heapSize;
        // 将剩余元素重新调整为最大堆(向下过滤)
        filterDown(heapSize, array);
    }
}

/*快速排序选取主元并调换主元与数组倒数第二个元素的位置*/
template<typename T>
int getBaseIndex(T *array, int start, int end)
{
    int mid = (start + end) / 2;
    T temp;
    if(array[start] > array[end])
    {
        temp = array[start];
        array[start] = array[end];
        array[end] = temp;
    }
    if(array[start] > array[mid])
    {
        temp = array[start];
        array[start] = array[mid];
        array[mid] = temp;
    }
    if(array[mid] > array[end])
    {
        temp = array[mid];
        array[mid] = array[end];
        array[end] = temp;
    }
    // 将主元与数组倒数第二个元素交换位置，方便后序划分左右子集
    temp = array[mid];
    array[mid] = array[end - 1];
    array[end - 1] = temp;
    return array[end - 1];
}

/* 快速排序的递归实现
 * 注意划分子集时的循环条件！！！浙大MOOC上的条件错误
 */
template<typename T>
void quickSortHelper(T *array, int start, int end)
{
    if(start < end)
    {
        T temp;
        // 选取主元。此处用的方法是取原数组首元素、中间元素与末尾元素的中位数，并将三者按从小到大排列
        int pivot = getBaseIndex(array, start, end);
        // 划分两个子集：在范围[start, end]范围内，将<=array[mid]的元素放在其左边，其余的放在右边
        int i = start, j = end - 1;  // 左、右子数组位置指针
        while(i < j)
        {
            // 找到左子数组大于等于主元的位置
            while(array[++i] < pivot);  
            // 找到右子数组小于等于主元的位置
            while(array[--j] > pivot);  
            // 交换二者位置，使二者均满足：左子数组 <= 主元 <= 右子数组
            if(i < j)
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        // 将主元放置在左、右子数组中间位置（索引i处）
        temp = array[i];
        array[i] = array[end - 1];
        array[end - 1] = temp;
        // 左子数组递归
        quickSortHelper(array, start, i - 1);
        // 右子数组递归
        quickSortHelper(array, i + 1, end);
    }
}

/* 快速排序 
 * 平均时间复杂度O(N*logN)
 * 思路：首先选取一个主元，将原数组按照大于主元（右区间）与小于等于主元（左区间）分成两个部分
 *       对两个区间的子数组递归调用快速排序
 * 递归退出条件：子数组只有一个元素
 */
template<typename T>
void quickSort(int N, T *array)
{
    quickSortHelper(array, 0, N - 1);
}

/* 两个有序序列的归并操作
 * 思路：初始化位置指针i与j为各自的首元素索引；
 *       while(i与j均未指到各自数组末尾)
 *          若a[i]<=b[j]，i右移一位（i++）；
 *          若a[i]>b[j]，j右移一位（j++）；
 *          哪个指针动了，就把其指向的元素放入临时数组里。
 *       再将各自数组中的剩余元素全部复制到临时数组空余的后半段中；
 *       最后将临时数组的元素导回到原始数组中。
 * @parm 
 *      left: 左侧子数组起始位置
 *      right: 右侧子数组起始位置
 *      rightEnd: 右侧子数组终止位置
 */
template<typename T>
void merge(int left, int right, int rightEnd, T *array, T *temp)
{
    // 数组a、b、temp的位置指针
    int i = left, j = right, k = left;  
    // 谁小就移动谁的指针
    while((i <= right - 1) && (j <= rightEnd))
    {
        if(array[i] < array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }
    // 若a中还有元素，则将其复制到temp内
    while(i <= right - 1)
        temp[k++] = array[i++];
    // 若b中还有元素，则将其复制到temp内
    while(j <= rightEnd)
        temp[k++] = array[j++];
    // 临时数组导回到原始数组中
    for(i = left; i <= rightEnd; i++)
        array[i] = temp[i];
}

/*归并排序递归实现*/
template<typename T>
void mergeSortHelper(int left, int rightEnd, T *array, T *temp)
{
    // 当待排子序列只剩一个元素时停止递归(即：left == rightEnd)
    if(left < rightEnd)
    {
        // 找数组中间位置
        int center = (left + rightEnd) / 2;
        // 对左侧子数组进行递归排序，得到左侧的有序序列
        mergeSortHelper(left, center, array, temp);
        // 对右侧子数组进行递归排序，得到右侧的有序序列
        mergeSortHelper(center + 1, rightEnd, array, temp);
        // 对得到的两个有序序列进行归并操作
        merge(left, center + 1, rightEnd, array, temp);
    }
}

/* 归并排序
 * 特点：任何情况下时间复杂度均为O(N*logN)，空间复杂度为O(N)，不是原地排序的算法
 * 思路（递归版本）：每次从数组中间划分，对左右两个子数组进行递归排序，得到有序的两个子序列后再将二者归并
 */
template<typename T>
void mergeSort(int N, T *array)
{
    T *temp = new T[N];
    mergeSortHelper(0, N - 1, array, temp);
    delete []temp;
}

/* 表排序（本初处的实现基于冒泡排序）
 * 使用场景：普通排序算法通常都需要交换待排序元素，若每个待排序元素大小很大时交换他们则会耗费很长时间
 * 思路：建立一个表，存放指向各个元素的位置指针，排序时只交换位置指针
 * 时间复杂度取决于其基于什么排序算法实现
 */
template<typename T>
int *tableSort(int N, T *array)
{
    int i, j;
    // 初始化表
    static int *table = new int[N];
    for(i = 0; i < N; i++)
        table[i] = i;
    // 进行冒泡排序，只交换各位置指针而不实际交换元素位置
    for(i = 0; i < N - 1; i++)
    {
        for(j = 0; j < N - i - 1; j++)
        {
            //比较相邻两元素，若前一个元素严格大于后一个元素，则二者交换位置
            if(array[table[j]] > array[table[j + 1]])
            {
                int temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
    // 返回表
    return table;
}

/* 桶排序
 * 平均时间复杂度为O(N)
 * 第一个超过O(N*logN)的排序算法，可以实现按关键字排序
 * 主要步骤：分配——>排序——>收集
 * 普通例子：设待排序数组内元素范围为0~100，则构建101个“桶”（桶由链表构成，即构建大小为101的指针数组，每个数组存放链表头结点）
 *       接下来扫描待排序数组，将待排序元素放入对应的桶中即可
 * 按关键字排序的例子：按关键字构建桶，再对桶内每个元素排序（例如将0~100分为10个范围，将各个待排序元素按范围放入桶中，再对桶中的元素排序）
 * 优化方法：基数排序（MSD（主元优先）、LSD（次元优先））
 */
// template<typename T>
// void bucketSort(int N, T *array)
// {
//     int i, n, j = 0, minV = array[0], maxV = array[0];
//     struct LNode
//     { 
//         T data; 
//         LNode *next; 
//         LNode() : next(nullptr) {}
//     };  // 链表结点定义
//     // 根据某种分桶原则得到的桶数组大小
//     n = getBucketSize();
//     // 建立桶数组
//     LNode *bucket[n];  
//     // 扫描数组，放入桶内(分配)
//     for(i = 0; i < N; i++)
//     {
//         LNode *t, *newNode;
//         // 搜索到链表尾部(根据某种分桶原则得到当前桶的索引)
//         int index = getIndex();
//         for(t = bucket[index]; t->next != nullptr; t = t->next);
//         // 从尾部插入结点
//         newNode = new LNode();
//         newNode->data = array[i];  
//         t->next = newNode;
//     }
//     // 对每个桶中的元素进行排序（排序）
//     for(i = 0; i < n; i++)
//     {
//          sort(bucket[i]);
//     }
//     // 将桶内元素依次导回至原数组（收集）
//     for(i = 0; i < n; i++)
//     {
//         for(LNode *t = bucket[i]->next; t != nullptr; t = t->next)
//         {
//             array[j++] = t->data;
//         }
//     }
// }

#endif
