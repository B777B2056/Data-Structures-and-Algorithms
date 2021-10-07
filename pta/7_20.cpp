#include <iostream>
#include <stack>
using namespace std;

int priority(char op1, char op2)
{
    if((op1 == '+') || (op1 == '-'))
    {
        if((op2 == '+') || (op2 == '-'))
            return 0;  // op1==op2
        else
            return -1;  // op1<op2
    }
    else
    {
        if((op2 == '+') || (op2 == '-'))
            return 1;  // op1>op2
        else
            return 0;  // op1==op2
    }
}

void ex7_20()
{
    int tag = 0;
    stack<char> ops;  // 运算符栈
    string str;
    getline(cin, str);
    for(size_t i = 0; i < str.length(); i++)
    {
        // 遇到操作数则直接输出(本题分割操作符与运算符特别繁琐，因为要包含操作数是正负数以及小数的情况)
        if((str[i]>='0'&&str[i]<='9')||str[i]=='.'
		 ||((str[i-1]=='('||str[i-1]=='+'||str[i-1]=='-'||str[i-1]=='*'||str[i-1]=='/')&&str[i]=='-')//判断其是负数 
		 ||(i==0&&str[i]=='-')//判断其是负数 
		 ||(i==0&&str[i]=='+')//判断其是正数 
		 ||((str[i-1]=='('||str[i-1]=='+'||str[i-1]=='-'||str[i-1]=='*'||str[i-1]=='/')&&str[i]=='+'))
        {
			if(tag==0)
            {
				if(str[i]=='+')
                {
					i++;
					cout << str[i];
				} 
                else 
                    cout << str[i];
				tag = 1;
			}
            else
            {
				if(str[i]=='+')
                    continue;
				else 
                    cout << " " << str[i];
			}
			i++;
			while(i<str.length())
            {
				if((str[i]>='0'&&str[i]<='9')||str[i]=='.')
                {
					cout << str[i];
					i++;
				}else{
					i--;
					break;
				}
			}
		}
        // 重点看运算符怎么处理
        else
        {
            // 若运算符栈为空或为左括号时，则当前运算符入栈
            if(ops.empty() || (str[i] == '('))
                ops.push(str[i]);
            else
            {
                // 若遇到右括号，一直pop，输出，直到遇到左括号
                if(str[i] == ')')
                {
                    while((!ops.empty()) && (ops.top() != '('))
                    {
                        cout << " " << ops.top();
                        ops.pop();
                    }
                    ops.pop();  // 弹出左括号
                }
                // 若遇到普通运算符，则比较当前运算符与栈顶运算符的优先级
                // 当前运算符优先级 < 栈顶运算符优先级：一直出栈，直到栈顶运算符优先级小于当前运算符优先级或者遇到左括号；然后将当前运算符入栈
                // 当前运算符优先级 > 栈顶运算符优先级: 当前运算符入栈
                else
                {
                    if(priority(str[i], ops.top()) != 1)
                    {
                        while((!ops.empty()) && (priority(str[i], ops.top()) != 1))
                        {
                            if(ops.top() == '(')
                                break;
                            cout << " " << ops.top();
                            ops.pop();
                        }
                    }
                    ops.push(str[i]);
                }
            }
        }
    }
    // 栈中剩余运算符出栈
    while(!ops.empty())
    {
        cout << " " << ops.top();
        ops.pop();
    }
}