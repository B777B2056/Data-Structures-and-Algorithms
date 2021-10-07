#include <string>
#include <iostream>
#include <stack_queue.hpp>

using namespace std;

/*栈测试：括号匹配*/
bool bracket_matching(std::string& s);  
/*栈测试：（整数）表达式求值，仅支持加减乘除四则运算*/
int opPriority(char op1, char op2);  // 辅助函数，判断运算符op1与运算符op2的优先级
int getValFromExpression(std::string& s, std::string& inversePolish);
/*双堆栈模拟队列操作*/
//注：此处s1模拟入队，s2模拟出队，故队列大小由s1决定；且s1栈容量一定要小于等于s2栈容量
// 模拟入队  
// 分为3种清空：
// 1、s1(容量较小的栈)不满：元素直接入栈s1
// 2、s1满，s2不空：队列满，不可入队
// 3、s1满，s2空：s1元素全部入栈s2，再将当前入队元素入栈s1
template<typename T>
void AddQ(time_t item, Stack<T>& s1, Stack<T>& s2)
{
    //s1不满
    if(!s1.isFull())
        s1.push(item);
    else
    {
        //s1满s2不空
        if(!s2.isEmpty())
        {   
            cout << "ERROR:Full" << endl;
            return;
        }
        //s1满s2空
        else
        {
            //s1元素全部入栈s2, 同时清空s1
            while(!s1.isEmpty())
            {
                s2.push(s1.getTop());
                s1.pop();
            }
            //再将元素入栈s1
            s1.push(item);
        }
    }
}

// 模拟出队
// 分为三种清空：
// 1、s1与s2都空：队列空，不可出队
// 2、s1不空，s2空：s1元素全部入栈s2，s2再出栈一个模拟出队
// 3、s1与s2均不空：直接从s2出栈模拟出队
template<typename T>
void DeleteQ(Stack<T>& s1, Stack<T>& s2)
{
    if(s1.isEmpty() && s2.isEmpty())
    {
        cout << "ERROR:Empty" << endl;
        return;
    }
    if(s2.isEmpty())
    {
        //s1元素全部入栈s2, 同时清空s1
        while(!s1.isEmpty())
        {
            s2.push(s1.getTop());
            s1.pop();
        }
    }
    //s2弹出一个元素，模拟出队
    cout << s2.pop() << endl;
}
