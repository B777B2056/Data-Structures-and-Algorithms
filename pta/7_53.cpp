#include <iostream>
using namespace std;

void ex7_53()
{
    int i, j, mid, N;
    cin >> N;
    int a1[N], a2[N];
    for(i = 0; i < N; i++)
        cin >> a1[i];
    for(j = 0; j < N; i++)
        cin >> a2[i];
    i = j = 0;
    while(i + j < N - 1)
    {
        if(a1[i] < a2[j])
            i++;
        else
            j++;
    }
    mid = a1[i] < a2[j] ? a1[i] : a2[j];
    cout << mid << endl;
}