#include <iostream>
using namespace std;

inline
int hashF(int key, int P)
{
    return key % P;
}

inline
int linear(int base, int P)
{
    base++;
    if(base >= P)
        base %= P;
    return base;
}

void ex7_42()
{
    int N, P, i, m, base;
    cin >> N >> P;
    int hashTable[P];
    bool v[P];
    for(i = 0; i < P; i++)
        v[i] = false;
    for(i = 0; i < N; i++)
    {
        cin >> m;
        bool isRep = false;
        base = hashF(m, P);
        while(v[base])
        {
            if(hashTable[base] == m)
            {
                isRep = true;
                break;
            }
            base = linear(base, P);
        }
        if(!isRep)
        {
            v[base] = true;
            hashTable[base] = m;
        }
        if(i == 0)
            cout << base;
        else
            cout << " " << base;
    }
    cout << "\n";
}
