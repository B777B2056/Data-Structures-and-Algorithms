#include <iostream>
#include <queue>
using namespace std;

// 先将数字插入小顶堆，每次再取两个最小的元素相加并插入小顶堆，最后的和就是答案

void ex7_29()
{
    int a, b, i, m, ans = 0, N;
    priority_queue<int, vector<int>, greater<int> > q;
    cin >> N;
    for(i = 0; i < N; i++)
    {
        cin >> m;
        q.push(m);
    }
    while(!q.empty())
    {
        a = q.top();
        q.pop();
        if(!q.empty())
        {
            b = q.top();
            q.pop();
            q.push(a + b);
            ans += (a + b);
        }
    }
    cout << ans << endl;
}