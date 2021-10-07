#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

enum status{EMPTY, FILLED};

struct Passenger
{
    int range;
    char id[19];
    status st; 
    Passenger() : range(0), st(EMPTY) {}
};

// 截取身份证号中的前16为位（再多的话会超时），对表长取余后作为key
int hashMethod(const int P, const char *key)
{
    int i;
    long long r;
    string birthday = "";
    for(i = 0; i < 16; i++)
        birthday += key[i];
    stringstream ss(birthday);
    ss >> r;
    return r % P;
}

// 线性探测法解决冲突
inline
int conflict(const int P, const int i, const int basePos)
{
    return (basePos + i) % P;
}

void ex7_45()
{
    int i, j, size, basePos, newPos, N, K, M, R;
    char id[19];
    scanf("%d %d", &N, &K);
    size = N / 0.75;  // 0.75为装载因子
    Passenger hashTable[size];
    for(i = 0; i < N; i++)
    {
        scanf("%s %d", id, &R);
        if(R < K)
            R = K;
        j = 0;
        newPos = basePos = hashMethod(size, id);
        while(hashTable[newPos].st == FILLED)
        {
            if(strcmp(hashTable[newPos].id, id) == 0)
                break;
            newPos = conflict(size, ++j, basePos);
        }
        strcpy(hashTable[newPos].id, id);
        hashTable[newPos].range += R;
        hashTable[newPos].st = FILLED;
    }
    scanf("%d", &M);
    for(i = 0; i < M; i++)
    {
        scanf("%s", id);
        j = 0;
        bool isFind = true;
        newPos = basePos = hashMethod(size, id);
        while(strcmp(hashTable[newPos].id, id) != 0)
        {
            newPos = conflict(size, ++j, basePos);
            if(newPos == basePos)
            {
                isFind = false;
                break;
            }
        }
        if(isFind)
            printf("%d\n", hashTable[newPos].range);
        else
            printf("No Info\n");
    }
}
