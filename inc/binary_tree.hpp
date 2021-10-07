#ifndef __BINARY_TREE_H
#define __BINARY_TREE_H

#include <vector>
#include "linkedlist.hpp"
#include "stack_queue.hpp"

/*普通二叉树*/

template<class T>
struct TreeNode{
    T data;
    int balance_factor;  // 构建平衡二叉树时使用，为以当前结点的平衡因子
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode(): balance_factor(0), left(nullptr), right(nullptr) {} 
};

/*注：为了封装树结点，因此定义了一些私有属性的辅助方法*/
template<class T>
class BinaryTree{
    protected:
        std::vector<T> values;  // 保存遍历结果
        TreeNode<T>* root;  // 树根结点指针
        /*DFS非递归(深度优先搜索)*/
        void preOrder();  // 先序遍历(非递归)
        void inOrder();  // 中序遍历(非递归)
        void postOrder();  // 后序遍历(非递归)
        /*BFS(广度优先搜索)*/
        void levelOrder();  // 层序遍历(非递归)
        /*树高*/
        int height();  // 循环+队列实现(BFS方式)
        int height(TreeNode<T>* node);  // 递归实现(DFS方式)
        /*删除树，释放树结点所占空间*/
        void deleteTree(TreeNode<T>* node); 
    public:
        BinaryTree(): root(nullptr) {}
        ~BinaryTree() { deleteTree(root); }
        bool isEmpty() { return root == nullptr; }
        /*遍历二叉树(全为非递归方式)，func参数用于选择先序/中序/后序/层序(0~3)*/
        std::vector<T> traversal(int func);  // 循环
        /*获取二叉树高度，func参数用于选择实现方式(0:递归，1:循环+队列)*/
        int getHeight(int func){ return func==0 ? height(root) : height(); }
    /*根据动态数组创建二叉树,返回二叉树根结点指针(设置为友元是为了防止不适用该功能的BST继承该函数)*/
    friend void createTree(std::vector<T>& v, BinaryTree<T>& tree){
        SingleLinkedList<TreeNode<T>*> nodes;
        for(T data : v){
            TreeNode<T>* newNode = new TreeNode<T>;
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            nodes.insert(nodes.getLength(), newNode);
        }
        for(std::size_t i = 0; i < v.size(); i++){
            /*左孩子(以下标0开始，下标i的左孩子为2i+1)*/
            if(2 * i + 1 < v.size()){
                nodes.getVal(i)->left = nodes.getVal(2 * i + 1);
            }
            /*右孩子(以下标0开始，下标i的右孩子为2i+2)*/
            if(2 * i + 2 < v.size()){
                nodes.getVal(i)->right = nodes.getVal(2 * i + 2);
            }
        }
        tree.root =  nodes.getVal(0);
    }  
};

template<class T>
void BinaryTree<T>::deleteTree(TreeNode<T>* node){
    if(!node) 
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete(node);
}

template<class T>
std::vector<T> BinaryTree<T>::traversal(int func){
    if(isEmpty()) throw "Tree is empty.";
    if(!values.empty()) values.clear();
    switch (func){
        case 0:
            preOrder();
            break;
        case 1:
            inOrder();
            break;
        case 2:
            postOrder();
            break;
        case 3:
            levelOrder();
            break;
        default:
            throw "Traversal Method Error.";
            break;
    }
    return values;
}

/* 非递归先序遍历（无脑入栈出栈即可，注意顺序，先序为"中-左-右"，因此结点入栈时入栈顺序为"右孩子-左孩子"）
 * 循环结束条件：栈空
 * 执行步骤：先令树根结点入栈；
 *          进入循环，临时指针node指向栈顶，栈顶元素存入结果数组，出栈；
 *          若原栈顶结点右孩子不为空则该右孩子入栈；
 *          若原栈顶结点左孩子不为空则该左孩子入栈；
 */
template<class T>
void BinaryTree<T>::preOrder(){
    TreeNode<T>* node;
    Stack<TreeNode<T>*> nodes;
    nodes.push(root);
    while(!nodes.isEmpty()){
        node = nodes.getTop();
        nodes.pop();
        values.push_back(node->data);
        if(node->right)
            nodes.push(node->right);
        if(node->left)
            nodes.push(node->left);
    }
}

/* 非递归中序遍历
 * 循环结束条件：栈空且遍历到的结点为空
 * 执行步骤：先将树根结点root赋值给临时指针node；
 *          进入循环，若node非空则入栈且node指向原临时指针的左结点；
 *          否则将栈顶出栈并存入结果数组，node指向原临时指针的右结点。
 */
template<class T>
void BinaryTree<T>::inOrder(){
    Stack<TreeNode<T>*> nodes;
    TreeNode<T>* node = root;
    while(node || !nodes.isEmpty()){
        if(node){
            nodes.push(node);
            node = node->left;
        }else{
            node = nodes.getTop();
            values.push_back(node->data);
            nodes.pop();
            node = node->right;
        }
    }
}

/* 非递归后序遍历
 * “反向”的先序遍历，“反向”体现在：
 * 1、左右子树入栈顺序与先序遍历相反
 * 2、需要使用一个辅助栈来保存“反向”先序遍历的遍历结果，
 *    将遍历到的结点压入辅助栈，遍历结束后再弹出。
 */
template<class T>
void BinaryTree<T>::postOrder(){
    TreeNode<T>* node;
    Stack<T> reverse_preOrder;
    Stack<TreeNode<T>*> nodes;
    nodes.push(root);
    while(!nodes.isEmpty()){
        node = nodes.getTop();
        nodes.pop();
        reverse_preOrder.push(node->data);
        if(node->left)
            nodes.push(node->left);
        if(node->right)
            nodes.push(node->right);
    }
    while(!reverse_preOrder.isEmpty()){
        values.push_back(reverse_preOrder.getTop());
        reverse_preOrder.pop();
    }
}

/* 层序遍历
 * 利用队列的先进先出特性实现
 * 树根结点先入队
 * 当队列不空时，访问队首元素并将其出队；
 * 再将原队首元素左孩子、右孩子依次入队。
 */
template<class T>
void BinaryTree<T>::levelOrder(){
    TreeNode<T>* node;
    Queue<TreeNode<T>*> nodes;
    nodes.enQueue(root);
    while(!nodes.isEmpty()){
        node = nodes.deQueue();
        values.push_back(node->data);
        if(node->left){
            nodes.enQueue(node->left);
        }
        if(node->right){
            nodes.enQueue(node->right);
        }
    }
}

/*树高 = max(左子树高， 右子树高)+1(1是根结点高度)*/
template<class T>
int BinaryTree<T>::height(TreeNode<T>* node){
    if(!node)
        return 0;
    int l_h = height(node->left);
    int r_h = height(node->right);
    return 1 + (l_h > r_h ? l_h : r_h);
}

template<class T>
int BinaryTree<T>::height(){
    int h = 0;
    TreeNode<T>* node;
    Queue<TreeNode<T>*> nodes;
    nodes.enQueue(root);
    nodes.enQueue(nullptr);
    while(!nodes.isEmpty()){
        node = nodes.deQueue();
        if(!node){
            h++;
            if(nodes.isEmpty())
                break;
            nodes.enQueue(nullptr);
            continue;
        }
        values.push_back(node->data);
        if(node->left){
            nodes.enQueue(node->left);
        }
        if(node->right){
            nodes.enQueue(node->right);
        }
    }
    return h;
}

#endif // !__BINARY_TREE_H
