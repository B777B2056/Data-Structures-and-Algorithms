#include <iostream>
using namespace std;

int findSubMax(int left, int right, int *a)
{
    if(left == right)
        return a[left] > 0 ? a[left] : 0;
    int mid = (left + right) / 2;
    int i, maxV = 0, midSubMax = 0;
    // 左侧最大子列和
    int leftSubMax = findSubMax(left, mid, a);
    // 右侧最大子列和
    int rightSubMax = findSubMax(mid + 1, right, a);
    // 横跨两边的最大子列和
    // 从mid向左扫描
    int leftSum = 0, maxLeftSum = 0;
    for(i = mid; i >= left; i--)
    {
        leftSum += a[i];
        if(leftSum > maxLeftSum)
            maxLeftSum = leftSum;
    }
    // 从mid向右扫描
    int rightSum = 0, maxRightSum = 0;
    for(i = mid + 1; i <= right; i++)
    {
        rightSum += a[i];
        if(rightSum > maxRightSum)
            maxRightSum = rightSum;
    }
    midSubMax = maxLeftSum + maxRightSum;
    if(maxV < leftSubMax)
        maxV = leftSubMax;
    if(maxV < rightSubMax)
        maxV = rightSubMax;
    if(maxV < midSubMax)
        maxV = midSubMax;
    return maxV;
}

void ex7_1()
{
    int i, N;
    bool isAllNegtiv = true;
    cin >> N;
    int *array = new int[N];
    for(i = 0; i < N; i++)
    {
        cin >> array[i];
        if(array[i] >= 0)
            isAllNegtiv = false;
    }
    if(isAllNegtiv)
        cout << "0" << endl;
    else
        cout << findSubMax(0, N - 1, array) << endl;
    delete []array;
}