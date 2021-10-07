#include <iostream>
#include <vector>
using namespace std;

// 不用排序
void ex7_13()
{
    int i, minV, maxV, N;
    cin >> N;
    int a[N];
    for(i = 0; i < N; i++)
        cin >> a[i];
    minV = maxV = a[0];
    for(i = 1; i < N; i++)
    {
        if(minV > a[i])
            minV = a[i];
        if(maxV < a[i])
            maxV = a[i];
    }
    int count[maxV - minV + 1];
    for(i = 0; i < maxV - minV + 1; i++)
        count[i] = 0;
    for(i = 0; i < N; i++)
        count[a[i] - minV]++;
    for(i = 0; i < maxV - minV + 1; i++)
    {
        if(count[i])
        {
            cout << i + minV << ":" << count[i] << "\n";
        }
    }
}