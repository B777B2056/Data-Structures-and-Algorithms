#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node *next;
    Node() : next(nullptr) {}
};

Node *insertVal(Node *h1, int val)
{
    Node *t1;
    for(t1 = h1->next; t1 != nullptr; t1 = t1->next)
    {
        if(t1->val <= val)
        {
            if(t1->next)
            {
                if(t1->next->val > val)
                {
                    Node *t = new Node();
                    t->val = val;
                    Node *temp = t1->next;
                    t1->next = t;
                    t->next = temp;
                    return t1;
                }
            }
            else
            {
                Node *t = new Node();
                t->val = val;
                t1->next = t;
                return t1;
            }
        }
    }
    return nullptr;
}

void ex7_51()
{
    int n;
    Node *h1, *t1;
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
    t1 = h1;
    while(true)
    {
        scanf("%d", &n);
        if(n == -1)
            break;
        t1 = insertVal(t1, n);
    }
    if(h1->next)
    {
        printf("%d", h1->next->val);
        h1 = h1->next->next;
    }
    else
    {
        printf("NULL\n");
        return;
    }
    while(h1)
    {
        printf(" %d", h1->val);
        h1 = h1->next;
    }
    printf("\n");
}