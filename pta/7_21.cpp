#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <algorithm>
using namespace std;

/* 求前缀/后缀表达式的值
 * 从前缀表达式的末尾开始扫描（若是后缀表达式，则从头开始扫描），遇到操作数就入栈，遇到运算符则从栈中弹出两个操作数进行运算，运算结果再入栈；
 * 最后栈顶就是运算结果
 */

void ex7_21()
{
    size_t i;
    string str;
    double a, b;
    stack<double> nums;
    getline(cin, str);
    reverse(str.begin(), str.end());
    for(i = 0; i < str.length(); i++)
    {
        if((str[i] >= '0') && (str[i] <= '9'))
        {
            double n;
            string num = "";
            while((i < str.length()) && (str[i] != ' '))
            {
                num += str[i];
                i++;
            }
            reverse(num.begin(), num.end());
            stringstream ss(num);
            ss >> n;
            nums.push(n);
        }
        else if(str[i] != ' ')
        {
            if(!nums.empty())
            {
                a = nums.top();
                nums.pop();
            }
            if(!nums.empty())
            {
                b = nums.top();
                nums.pop();
            }
            switch(str[i])
            {
                case '+':
                    nums.push(a + b);
                    break;
                case '-':
                    nums.push(a - b);
                    break;
                case '*':
                    nums.push(a * b);
                    break;
                case '/':
                    if(b == 0.0)
                    {
                        cout << "ERROR";
                        return;
                    }
                    else
                        nums.push(a / b);
                    break;
            }
        }
    }
    printf("%.1f", nums.top());
    nums.pop();
}
