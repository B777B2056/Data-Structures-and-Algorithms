#include <stdio.h>
#include <string.h>
#include<math.h>

void ex7_43()
{
    int N, P, i, len, start, base, cur, cof, conflict, isRep;
    char key[9];
    scanf("%d %d", &N, &P);
    int v[P];
    char hashTable[P][9];
    for(i = 0; i < P; i++)
        v[i] = 0;
    for(i = 0; i < N; i++)
    {
        scanf("%s", key);
        //关键字重复标志初始化
        isRep = 0;
        //移位映射
        len = strlen(key);
        start = (len >= 3) ? (len - 3) : 0;
        base = 0;
        while(key[start] != '\0')
        {
            base += (key[start] - 'A') * pow(32, len - start - 1);
            ++start;
        }
        //除留取余哈希
        base %= P;
        //平方探测
        cof = 0;
        cur = base;
        conflict = 0;
        while(v[cur])
        {
            if(strcmp(key, hashTable[cur]) == 0)
            {
                isRep = 1;
                break;
            }
            if(++conflict % 2)
                cof = (((conflict + 1) / 2) * ((conflict + 1) / 2));
            else
                cof = -((conflict / 2) * (conflict / 2));
            cur = base + cof;
            if(cur < 0)
                cur = P + cur % P;
            if(cur >= P)
                cur %= P; 
        }
        base = cur;
        //关键字未重复保存哈希结果
        if(!isRep)
        {
            v[base] = 1;
            strcpy(hashTable[base], key);
        }
        if(i == 0)
            printf("%d", base);
        else
            printf(" %d", base);
    }
}
