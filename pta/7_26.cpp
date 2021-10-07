#include <iostream>
#include <string.h>
using namespace std;

struct MsgNode
{
    char msg[11];
    int priority;
};

void insertVal(MsgNode *heap, char *s, int p, int *curSize)
{
    int i;
    MsgNode temp;
    strcpy(heap[*curSize].msg, s);
    heap[*curSize].priority = p;
    for(i = (*curSize); i > 0; i = (i - 1) / 2)
    {
        if(heap[i].priority < heap[(i - 1) / 2].priority)
        {
            temp = heap[i];
            heap[i] = heap[(i - 1) / 2];
            heap[(i - 1) / 2] = temp;
        }
    }
    (*curSize)++;
}

void deleteVal(MsgNode *heap, int *curSize)
{
    if((*curSize) <= 0)
    {
        printf("EMPTY QUEUE!\n");
        return;
    }
    int i = 0, child;
    MsgNode t;
    printf("%s\n", heap[0].msg);
    heap[0] = heap[--(*curSize)];
    while(2 * i + 1 < *curSize)
    {
        child = 2 * i + 1;
        if((2 * i + 2 < *curSize) && (heap[2 * i + 1].priority > heap[2 * i + 2].priority))
            child = 2 * i + 2;
        if(heap[i].priority > heap[child].priority)
        {
            t = heap[i];
            heap[i] = heap[child];
            heap[child] = t;
            i = child;
        }
        else
            break;
    }
}

void ex7_26()
{
    int i, N, p, curSize = 0;
    char command[4], msg[11];
    scanf("%d", &N);
    MsgNode *heap = new MsgNode[N];
    for(i = 0; i < N; i++)
    {
        scanf("%s", command);
        if(command[0] == 'P')
        {
            scanf("%s %d", msg, &p);
            insertVal(heap, msg, p, &curSize);
        }
        else
            deleteVal(heap, &curSize);
    }
    delete []heap;
}
