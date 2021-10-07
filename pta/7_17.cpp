#include <iostream>
#include <stack>
using namespace std;

/*递归求解汉诺塔*/
void recursion(int N, char a, char b, char c)
{
    if(N == 0)
        return;
    recursion(N - 1, a, c, b);
    cout << a << " -> " << c << endl;
    recursion(N - 1, b, a, c);
}

/*用栈模拟系统栈，将递归转换为循环。*/
struct Para
{
    int N;
    char a, b, c;
    Para(int n, char i, char j, char k) : N(n), a(i), b(j), c(k) {}
};

void solution(int N, char a, char b, char c)
{
    stack<Para> s;
    /*模拟函数参数初始化*/
    s.push(Para(N, a, b, c));
    while(!s.empty())
    {
        Para m = s.top();
        s.pop();
        if(m.N == 1)
            cout << m.a << " -> " << m.c << endl;
        else
        {
            /*注意，函数参数入栈时的顺序，与递归相反*/
            s.push(Para(m.N - 1, m.b, m.a, m.c));
            s.push(Para(1, m.a, m.b, m.c));
            s.push(Para(m.N - 1, m.a, m.c, m.b));
        }
    }
}

void ex7_17()
{
    int N;
    scanf("%d", &N);
    solution(N, 'a', 'b', 'c');
}
