#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <vector>
#include <iostream>

/*结点数据结构*/
template<class T>
struct LinkedNode{
    /*值域*/
    T val;
    /*指针域*/
    LinkedNode<T>* prev;
    LinkedNode<T>* next; 
};

/*模板类*/
template<class T>
class SingleLinkedList{
    private:
        LinkedNode<T>* head;
    public:
        SingleLinkedList();
        ~SingleLinkedList();
        void printLinked();  //打印链表
        bool isEmpty();  // 判断线性表是否为空
        unsigned int getLength();  // 返回线性表的长度
        void insert(int index, T val);  // 将数据val插入到第i个位置（i=0，1，2...）
        int search(T target);  // 搜索线性表中与target相同值的元素，返回第一次出现的该元素序号
        void remove(T target);  // 删除目标元素
        T getVal(int index);  // 根据索引返回元素值
        void reverse();  // 链表原地反转
};

template<class T>
class DoubleLinkedList{
    private:
        LinkedNode<T>* head;
        LinkedNode<T>* last;
    public:
        DoubleLinkedList(std::vector<T> &v);
        ~DoubleLinkedList();
        void printLinked();  
        bool isEmpty();  
        unsigned int getLength();  
        void insert(int index, T val);  
        int search(T target);  
        void remove(T target);  
        T getVal(int index);
        void reverse();
};

template<class T>
class CircularLinkedList{
    private:
        LinkedNode<T>* head;
    public:
        CircularLinkedList(std::vector<T> &v);
        ~CircularLinkedList();
        void printLinked();  
        bool isEmpty();  
        unsigned int getLength();  
        void insert(int index, T val);  
        int search(T target);  
        void remove(T target);  
        T getVal(int index);
};

/*单向链表*/
// 构造函数
template<class T>
SingleLinkedList<T>::SingleLinkedList(){
    head = new LinkedNode<T>();
    head->next = nullptr;
}  

//析构函数
template<class T>
SingleLinkedList<T>::~SingleLinkedList(){
    while(head != nullptr){
        LinkedNode<T>* t = head;
        head = head->next;
        delete t;
    }
}

//打印链表
template<class T>
void SingleLinkedList<T>::printLinked(){
    for(LinkedNode<T>* temp = head->next; temp != nullptr; temp = temp->next){
        if(temp->next != nullptr)
            std::cout << temp->val << "->";
        else
            std::cout << temp->val << "\n";
    }
}

// 返回线性表的长度
template<class T>
unsigned int SingleLinkedList<T>::getLength(){
    LinkedNode<T>* temp;
    unsigned int length = 0;
    for(temp = head->next; temp != nullptr; temp = temp->next)
        length++;
    return length;
}  

// 根据索引返回元素值
template<class T>
T SingleLinkedList<T>::getVal(int index){
    if(index >= getLength())
        throw "Index out of range.";
    int i = 0;
    LinkedNode<T>* temp;
    for(temp = head->next; i != index; temp = temp->next, i++);
    return temp->val;
} 

// 搜索线性表中与target相同值的元素，返回第一次出现的该元素序号(返回-1说明该值不存在于链表中)
template<class T>
int SingleLinkedList<T>::search(T target){
    int i = 0;
    for(LinkedNode<T>* temp = head->next; temp != nullptr; temp = temp->next, i++){
        if(temp->val == target){
            return i;
        }
    }
    return -1;
} 

// 判断线性表是否为空
template<class T>
bool SingleLinkedList<T>::isEmpty() { return head->next == nullptr; } 

// 将数据val插入到第i个位置（i=0，1，2...） 
template<class T>
void SingleLinkedList<T>::insert(int index, T val){
    if(index > getLength())
        throw "Index out of range.";
    LinkedNode<T>* newNode = new LinkedNode<T>;
    newNode->val = val;
    if(index == 0){
        newNode->next = head->next;
        head->next = newNode;
        return;
    }
    LinkedNode<T>* temp = head->next;
    for(int i = 0; i < index - 1; i++){
        if(i >= index - 1) break;
        else temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
} 

// 删除目标元素
template<class T>
void SingleLinkedList<T>::remove(T target){
    bool isFound = false;
    LinkedNode<T>* temp = head;
    while(temp->next != nullptr){
        if(temp->next->val == target){
            isFound = true;
            temp->next = temp->next->next;
        }else{
            temp = temp->next;
        }
    }
    if(!isFound)
        throw "Not Found the Target Value.";
}  

//原地反转单链表(重要)
template<class T>
void SingleLinkedList<T>::reverse(){
    LinkedNode<T>* temp;
    LinkedNode<T>* slow = head->next;
    LinkedNode<T>* quick = slow->next;
    while(quick != nullptr){
        temp = quick->next;
        quick->next = slow;
        slow = quick;
        quick = temp;
    }
    head->next->next = nullptr;
    head->next = slow;
}

/*双向链表*/
// 构造函数
template<class T>
DoubleLinkedList<T>::DoubleLinkedList(std::vector<T> &v){
    head = new LinkedNode<T>();
    last = new LinkedNode<T>();
    LinkedNode<T>* node = new LinkedNode<T>();
    head->prev = nullptr;
    head->next = nullptr;
    node = head;
    for(std::size_t i = 0; i < v.size(); i++){
        LinkedNode<T>* newNode = new LinkedNode<T>();
        newNode->val = v[i];
        newNode->prev = node;
        newNode->next = nullptr;
        node->next = newNode;
        node = node->next;
        if(i == v.size() - 1)
            last = node;
    }
}  

// 析构函数
template<class T>
DoubleLinkedList<T>::~DoubleLinkedList(){
    while(head != nullptr){
        LinkedNode<T>* t = head;
        head = head->next;
        delete t;
    }
}

//打印链表
template<class T>
void DoubleLinkedList<T>::printLinked(){
    LinkedNode<T>* temp;
    for(temp = head->next; temp != nullptr; temp = temp->next){
        if(temp->next != nullptr)
            std::cout << temp->val << "<->";
        else
            std::cout << temp->val << "\n";
    }
}

// 返回线性表的长度
template<class T>
unsigned int DoubleLinkedList<T>::getLength(){
    int length = 0;
    LinkedNode<T>* temp;
    for(temp = head->next; temp != nullptr; temp = temp->next)
        length++;
    return length;
}  

// 根据索引返回元素值
template<class T>
T DoubleLinkedList<T>::getVal(int index){
    if(index >= getLength())
        throw "Index out of range.";
    int i = 0;
    LinkedNode<T>* temp;
    for(temp = head->next; i != index; temp = temp->next, i++);
    return temp->val;
}

// 搜索线性表中与target相同值的元素，返回第一次出现的该元素序号(返回-1说明该值不存在于链表中)
template<class T>
int DoubleLinkedList<T>::search(T target){
    int i = 0;
    LinkedNode<T>* temp;
    for(temp = head->next; temp != nullptr; temp = temp->next, i++){
        if(temp->val == target){
            return i;
        }
    }
    return -1;
}  

// 判断线性表是否为空
template<class T>
bool DoubleLinkedList<T>::isEmpty() { return head->next == nullptr; }  

// 将数据val插入到第i个位置（i=0，1，2...）
template<class T>
void DoubleLinkedList<T>::insert(int index, T val){
    if(index > getLength())
        throw "Index out of range.";
    else if(index == getLength()){
        LinkedNode<T>* newNode = new LinkedNode<T>();
        newNode->val = val;
        newNode->prev = last;
        newNode->next = nullptr;
        last->next = newNode;
        last = newNode;
    }else{
        int i = 0;
        LinkedNode<T>* temp;
        for(temp = head->next; i < index - 1; temp = temp->next, i++);
        LinkedNode<T>* newNode = new LinkedNode<T>();
        newNode->val = val;
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
}  

// 删除目标元素
template<class T>
void DoubleLinkedList<T>::remove(T target){
    bool isFound = false;
    for(LinkedNode<T>* temp = head->next; temp != nullptr; temp = temp->next){
        if(temp->val == target){
            isFound = true;
            /*删除目标结点*/
            temp->prev->next = temp->next;
            if(temp->next != nullptr)
                temp->next->prev = temp->prev;
            /*更新尾结点*/
            if(temp == last)
                last = temp->prev;
        }
    }
    if(!isFound)
        throw "Not Found the Target Value.";
}  

//原地反转双链表
template<class T>
void DoubleLinkedList<T>::reverse(){
    LinkedNode<T>* reverse_head = new LinkedNode<T>();
    reverse_head->prev = nullptr;
    reverse_head->next = last;
    head->next->prev = nullptr;  // 断开原链表表头结点与第一个数据结点间的反向指针
    for(LinkedNode<T>* t = last; t != nullptr; t = t->next){
        if(t == last){
            t->next = t->prev;
            t->prev = reverse_head;
        }else{
            LinkedNode<T>* temp = t->prev;
            t->prev = t->next;
            t->next = temp;
        }
    }
    last = head->next;
    head = reverse_head;
}

/*单向环形链表ADT*/
// 构造函数
template<class T>
CircularLinkedList<T>::CircularLinkedList(std::vector<T> &v){
    head = new LinkedNode<T>();
    LinkedNode<T>* node;
    head->next = nullptr;
    node = head;
    for(int i = 0; i < v.size(); i++){
        LinkedNode<T>* newNode = new LinkedNode<T>();
        newNode->val = v[i];
        newNode->next = nullptr;
        node->next = newNode;
        node = node->next;
        if(i == v.size() - 1)
            node->next = head->next;
    }
}  

// 析构函数
template<class T>
CircularLinkedList<T>::~CircularLinkedList(){
    LinkedNode<T>* temp = head->next; 
    while(temp->next != head->next){
        LinkedNode<T>* t = temp->next;
        delete temp;
        temp = t;
    }
    delete head;
}

// 打印链表
template<class T>
void CircularLinkedList<T>::printLinked(){
    LinkedNode<T>* temp;
    for(temp = head->next; temp->next != head->next; temp = temp->next){
        std::cout << temp->val << "->";
    }
    std::cout << temp->val << "<-" << head->next->val << "\n";
}

// 返回环形单向链表的长度
template<class T>
unsigned int CircularLinkedList<T>::getLength(){
    int length = 1;
    for(LinkedNode<T>* temp = head->next; temp->next != head->next; temp = temp->next)
        length++;
    return length;
} 

// 根据索引返回元素值（index%length为一圈里的索引）
template<class T>
T CircularLinkedList<T>::getVal(int index){
    int length = getLength();
    if(length == 0)
        throw "Index out of range.";
    index %= length;
    int i = 0;
    LinkedNode<T>* temp;
    for(temp = head->next; i != index; i++, temp = temp->next);
    return temp->val;
}  

// 搜索线性表中与target相同值的元素，返回第一次出现的该元素序号(返回-1说明该值不存在于链表中)
template<class T>
int CircularLinkedList<T>::search(T target){
    int index = 0;
    LinkedNode<T>* temp = head->next;
    while(true){
        if(temp->val == target)
            return index;
        index++;
        temp = temp->next;
        if(temp == head)
            break;
    }
    return -1;
}

// 判断线性表是否为空
template<class T>
bool CircularLinkedList<T>::isEmpty() { return head->next == nullptr; }  

// 将数据val插入到第i个位置（i=0，1，2...）
template<class T>
void CircularLinkedList<T>::insert(int index, T val){
    int length = getLength();
    if(length == 0)
        throw "Index out of range.";
    index %= length;
    int i = 0;
    LinkedNode<T>* temp;
    for(temp = head->next; i < index - 1; i++, temp = temp->next);
    LinkedNode<T>* newNode = new LinkedNode<T>();
    newNode->val = val;
    newNode->next = temp->next;
    temp->next = newNode;
}  

// 删除目标元素
template<class T>
void CircularLinkedList<T>::remove(T target){
    bool isFound = false;
    LinkedNode<T>* temp = head->next;
    while( temp->next != head->next){
        if(temp->next->val == target){
            isFound = true;
            temp->next = temp->next->next;
        }else{
            temp = temp->next;
        }
    }
    if(!isFound)
        throw "Not Found the Target Value.";
}

#endif // !__LINKEDLIST_H
