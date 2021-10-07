#include "../inc/linkedlist.hpp"
#include "../inc/stack_queue.hpp"
#include "../inc/application.hpp"

bool bracket_matching(std::string& s){
    Stack<char> a;
    for(char c : s){
        if(c == '(' || c == '{' || c == '[')
            a.push(c);
        if(c == ')' || c == '}' || c == ']'){
            if(a.isEmpty()) return false;
            switch(c){
                case ')':
                    if(a.getTop() == '(') 
                        a.pop();
                    break;
                case '}':
                    if(a.getTop() == '{') 
                        a.pop();
                    break;
                case ']':
                    if(a.getTop() == '[') 
                        a.pop();
                    break;
            }
        }
    }
    return a.isEmpty();
}

/*  运算符优先级
 *  op1 > op2 : 1
 *  op1 == op2 : 0
 *  op1 < op2 : -1
 */
inline int opPriority(char op1, char op2){
    if(op1 == '+' || op1 == '-'){
        if(op2 == '+' || op2 == '-') 
            return 0;
        else 
            return -1;
    }else{
        if(op2 == '+' || op2 == '-') 
            return 1;
        else 
            return 0;
    }
}

int getValFromExpression(std::string& s, std::string& inversePolish){
    /*检查括号匹配情况*/
    if(!bracket_matching(s))
        throw "Wrong bracket.";
    int n1, n2;
    std::string exp_last = "$";
    Stack<int> nums;  // 操作数栈
    Stack<char> ops;  // 运算符栈
    /*将输入的中缀表达式转换为后缀表达式*/
    for(char c : s){
        if(c >= '0' && c <= '9'){
            exp_last += c;
        }else if(c == '('){
            ops.push(c);
        }else if(c == ')'){
            /*遇到右括号，则运算符栈一直出栈，直至遇到左括号后停止*/
            if(c == ')'){
                while(ops.getTop() != '('){
                        exp_last += ops.getTop();
                        ops.pop();
                }
                ops.pop();  // 弹出左括号
            }
        }else{
            if(ops.isEmpty())
                ops.push(c);
            else{
                /*c运算符优先级<=栈顶运算符优先级*/
                while(opPriority(c, ops.getTop()) < 1 && ops.getTop() != '('){
                    exp_last += ops.getTop();
                    ops.pop();
                    /*很重要！！！必须检查运算符栈是否为空！！！！！！*/
                    if(ops.isEmpty())
                        break;
                }
                ops.push(c);   
            }
        }
    }
    while(!ops.isEmpty()){
        exp_last += ops.getTop();
        ops.pop();
    }
    inversePolish = exp_last;
    //std::cout << s << "\'s Inverse Polish expression is " << exp_last << endl;
    /* 计算后缀表达式的值
     * 从左到右扫描后缀表达式;
     * 如果遇到一个操作数，将其压入栈中，如果遇到一个操作符，则从栈中弹出两个操作数，计算结果，然后把结果入栈;
     * 直到遍历完后缀表达式，则计算完成;
     * 此时的栈顶元素即为计算结果。
     */
    for(char c : exp_last){
        if(c >= '0' && c <='9'){
            nums.push(c - '0');
        }else{
            if(nums.isEmpty()) continue;
            n1 = nums.getTop();
            nums.pop();
            n2 = nums.getTop();
            nums.pop();
            switch(c){
                case '+':
                    nums.push(n2 + n1);
                    break;
                case '-':
                    nums.push(n2 - n1);
                    break;
                case '*':
                    nums.push(n2 * n1);
                    break;
                case '/':
                    nums.push(n2 / n1);
                    break;
            }
        }
    }
    return nums.getTop();
}