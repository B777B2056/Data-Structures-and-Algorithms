#ifndef __STACK_QUEUE_H
#define __STACK_QUEUE_H

#include <iostream>
/*结点定义*/
template<class T>
struct  SQNode{
    T val;
    SQNode<T>* next;
};

/*栈(先进后出，尾插尾删)*/
template<class T>
class Stack{
    private:
        SQNode<T>* head;
        SQNode<T>* top;  // 栈顶指针
    public:
        Stack();  // 生成带头结点的链式存储结构的空堆栈(最大深度为maxSize)
        ~Stack();  // 释放所有动态内存
        void printStack();  // 打印栈
        void push(T val);  // 将元素压入堆栈
        void pop();  // 弹出栈顶元素
        T getTop(){ return top->val; }  // 返回栈顶元素
        bool isEmpty(){ return top == nullptr; }  //判断堆栈是否为空
};

/*队列(先进先出，头删尾插)*/
template<class T>
class Queue{
    private:
        SQNode<T>* head;  // 队列头指针（head->next为队列首元素指针）
        SQNode<T>* last;  // 队列尾部指针
    public:
        Queue();  // 生成带头结点的链式存储结构的空队列(最大容量为maxSize)
        ~Queue();  //释放所有动态内存
        void printQueue();  // 打印队列
        void enQueue(T val);  // 将元素val插入队列尾部
        T deQueue();  // 将队列头部元素删除并返回
        bool isEmpty(){ return head->next == nullptr; }  //判断队列是否为空
};

/*双端队列*/
template<class T>
class Deque{
    private:
        SQNode<T>* head;  // 队列头指针（head->next为队列首元素指针）
        SQNode<T>* last;  // 队列尾部指针
    public:
        Deque();
        ~Deque();
        void printDeque();  // 打印双端队列
        void pushLeft(T val);  // 向双端队列左端压入元素
        void pushRight(T val);  // 向双端队列右端压入元素
        T popLeft();  // 弹出双端队列左端元素
        T popRight();  // 弹出双端队列右端元素
        bool isEmpty(){ return head->next == nullptr; }  //判断队列是否为空
};

template<class T>
Stack<T>::Stack(){
    head = new SQNode<T>();
    head->next = nullptr;
    top = nullptr;
}  

template<class T>
Stack<T>::~Stack(){
    while(head != nullptr){
        SQNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template<class T>
void Stack<T>::printStack(){
    for(SQNode<T>* temp =head->next; temp != nullptr; temp = temp->next){
        if(temp->next != nullptr)
            std::cout << temp->val << "->";
        else
            std::cout << temp->val << "\n";
    }
}    

template<class T>
void Stack<T>::push(T val){
    top = new SQNode<T>();
    top->val = val;
    top->next = head->next;
    head->next = top;
} 

template<class T>
void Stack<T>::pop(){
    if(isEmpty())
        throw "Stack is Empty.";
    head->next = head->next->next;
    delete top;
    top = head->next;
}  

template<class T>
Queue<T>::Queue(){
    head = new SQNode<T>();
    head->next = nullptr;
    last = head;
}  

template<class T>
Queue<T>::~Queue(){
    while(head != nullptr){
        SQNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
}  

template<class T>
void Queue<T>::printQueue(){
    for(SQNode<T>* temp = head->next; temp != nullptr; temp = temp->next){
        if(temp->next != nullptr)
            std::cout << temp->val << "->";
        else
            std::cout << temp->val << "\n";
    }
}   

/*尾插*/
template<class T>
void Queue<T>::enQueue(T val){
    SQNode<T>* node = new SQNode<T>();
    node->val = val;
    node->next = nullptr;
    last->next = node;
    last = node;
} 

/*头删*/
template<class T>
T Queue<T>::deQueue(){
    if(isEmpty())
        throw "Queue is Empty.";
    SQNode<T>* t = head->next;
    T val = t->val;
    head->next = head->next->next;
    t->next = nullptr;
    delete t;
    if(isEmpty())
        last = head;
    return val;
}

template<class T>
Deque<T>::Deque(){
    head = new SQNode<T>();
    head->next = nullptr;
    last = head;
}

template<class T>
Deque<T>::~Deque(){
    while(head != nullptr){
        SQNode<T>* t = head;
        head = head->next;
        delete t;
    }
}

template<class T>
void Deque<T>::printDeque(){
    for(SQNode<T>* temp = head->next; temp != nullptr; temp = temp->next){
        if(temp->next != nullptr)
            std::cout << temp->val << "->";
        else
            std::cout << temp->val << "\n";
    }
}

template<class T>
void Deque<T>::pushLeft(T val){
    SQNode<T>* newNode = new SQNode<T>();
    newNode->val = val;
    newNode->next = head->next;
    if(head->next == nullptr) 
        last = newNode;
    head->next = newNode;
}

template<class T>
void Deque<T>::pushRight(T val){
    SQNode<T>* newNode = new SQNode<T>();
    newNode->val = val;
    newNode->next = nullptr;
    last->next = newNode;
    last = newNode;
}

template<class T>
T Deque<T>::popLeft(){
    if(isEmpty())
        throw "Deque is Empty.";
    SQNode<T>* t = head->next;
    T val = t->val;
    head->next = head->next->next;
    delete t;
    return val;
}

template<class T>
T Deque<T>::popRight(){
    if(isEmpty())
        throw "Deque is Empty.";
    SQNode<T>* t;
    T val = last->val;
    for(t = head->next; t->next != last; t = t->next);
    t->next = nullptr;
    delete last;
    last = t;
    return val;
}

#endif // !__STACK_QUEUE_H
