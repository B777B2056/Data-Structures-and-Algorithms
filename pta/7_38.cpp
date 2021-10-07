#include <iostream>
#include <stack>
using namespace std;

// 向下过滤
void filterDown(int *heap, int N)
{
    int i, t;
    for(i = 0; i < N; i++)
    {
        if((2 * i + 1 < N) && (2 * i + 2 < N))
        {
            if(heap[2 * i + 1] < heap[2 * i + 2])
            {
                if(heap[i] > heap[2 * i + 1])
                {
                    t = heap[i];
                    heap[i] = heap[2 * i + 1];
                    heap[2 * i + 1] = t;
                }
            }
            else
            {
                if(heap[i] > heap[2 * i + 2])
                {
                    t = heap[i];
                    heap[i] = heap[2 * i + 2];
                    heap[2 * i + 2] = t;
                }
            }
        }
        else if(2 * i + 1 < N)
        {
            if(heap[i] > heap[2 * i + 1])
            {
                t = heap[i];
                heap[i] = heap[2 * i + 1];
                heap[2 * i + 1] = t;
            }
        }
        else if(2 * i + 2 < N)
        {
            if(heap[i] > heap[2 * i + 2])
            {
                t = heap[i];
                heap[i] = heap[2 * i + 2];
                heap[2 * i + 2] = t;
            }
        }
    }
}

int erase(int *heap, int *curSize)
{
    int r = heap[0];
    heap[0] = heap[(*curSize) - 1];
    --(*curSize);
    filterDown(heap, *curSize);
    return r;
}

// 用最小堆实现
// 注意到M << N，因此建立M个最大元素的最小堆即可，否则会超时
// 先输入M个元素填充最小堆；
// 再输入N-M个元素，此时当输入元素 > 最小堆的堆顶元素时令堆顶元素等于输入元素,再向下调整；
// 输入结束后，即可得到包含M个最大元素的最小堆。
void ex7_38()
{
    int i, j, curSize = 0, N, M;
    cin >> N >> M;
    int *heap = new int[M];
    if(N < M) M = N;
    curSize = M;
    // 输入前M个元素
    for(i = 0; i < M; i++)
        cin >> heap[i];
    // 向下调整建堆
    for(i = M / 2 - 1; i >= 0; i--)
        filterDown(heap, curSize);
    // 输入后N-M个元素
    for(i = 0; i < N - M; i++)
    {
        cin >> j;
        if(j > heap[0])
        {
            heap[0] = j;
            filterDown(heap, curSize);
        }
    }
    // 最小堆元素依次入栈，逆序
    stack<int> s;
    for(i = 0; i < M; i++)
        s.push(erase(heap, &curSize));
    // 弹出元素
    cout << s.top();
    s.pop();
    while(!s.empty())
    {
        cout << " " << s.top();
        s.pop();
    }    
}
