#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*用自己写的快排，最后一个测试点会超时*/

// void getMid(int *a, int l, int r)
// {
//     int t, midIndex, mid = (l + r) / 2;
//     if((a[l] >= a[mid]) && (a[l] <= a[r]))
//         midIndex = l;
//     else if((a[r] >= a[mid]) && (a[r] <= a[l]))
//         midIndex = r;
//     else
//         midIndex = mid;
//     t = a[midIndex];
//     a[midIndex] = a[l];
//     a[l] = t;
// }

// void quickSort(int *a, int l, int r)
// {
//     if(l < r)
//     {
//         int i = l, j = r;
//         getMid(a, l, r);
//         int pivot = a[l];
//         while(i < j)
//         {
//             while((i < j) && (a[j] >= pivot))
//                 j--;
//             if(i < j)
//                 a[i++] = a[j];
//             while((i < j) && (a[i] < pivot))
//                 i++;
//             if(i < j)
//                 a[j--] = a[i];
//         }
//         a[i] = pivot;
//         quickSort(a, l, i - 1);
//         quickSort(a, i + 1, r);
//     }
// }

void ex7_39()
{
    ios::sync_with_stdio(false);
    int i, j, N, M;
    long long maxGain = 0;
    // 输入
    cin >> N;
//     int a[N];
    vector<int> a(N);
    for(i = 0; i < N; i++)
        cin >> a[i];
    cin >> M;
//     int b[M];
    vector<int> b(M);
    for(i = 0; i < N; i++)
        cin >> b[i];
    // 各自排序（降序）
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
//     quickSort(a, 0, N - 1);
//     quickSort(b, 0, M - 1);
    // 计算小于0时的最大收益
    i = j = 0;
    while((i < N) && (j < M))
    {
        if((a[i] >= 0) || (b[j] >= 0))
            break;
        maxGain += (a[i++] * b[j++]);
    }
    // 计算大于0时的最大收益
    i = N - 1;
    j = M - 1;
    while((i >= 0) && (j >= 0))
    {
        if((a[i] <= 0) || (b[j] <= 0))
            break;
        maxGain += (a[i--] * b[j--]);
    }
    cout << maxGain << endl;
}