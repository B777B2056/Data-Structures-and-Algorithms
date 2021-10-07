#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node *next;
    Node() : next(nullptr) {}
};

Node *findVal(int i, int val, Node *h1)
{
    for(Node *t1 = h1; t1 !=nullptr; t1 = t1->next)
    {
        if(t1->val == val)
        {
            if(!i)
                printf("%d", val);
            else
                printf(" %d", val);
            return t1;
        }    
    }
    return nullptr;
}

void ex7_52()
{
    int n, i = 0;
    Node *h1, *t, *t1;
    h1 = new Node();
    t1 = h1;
    while(true)
    {
        scanf("%d", &n);
        if(n == -1)
            break;
        Node *t = new Node();
        t->val = n;
        t1->next = t;
        t1 = t1->next;
    }
    t1 = h1->next;
    while(true)
    {
        scanf("%d", &n);
        if(n == -1)
            break;
        t = findVal(i, n, t1);
        if(t)
        {
            t1 = t->next;
            i++;
        }
    }
    if(!i)
        printf("NULL");
    printf("\n");
}