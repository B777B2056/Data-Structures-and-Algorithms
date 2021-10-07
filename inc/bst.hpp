#ifndef __BST_H
#define __BST_H

#include "binary_tree.hpp"

/*非平衡二叉搜索树*/

template <class T>
class BinarySearchTree : public BinaryTree<T>{
    protected:
        TreeNode<T>* insertHelper(TreeNode<T>* root, T target);
    public:
        BinarySearchTree() {}
        ~BinarySearchTree() { this->deleteTree(this->root); }
        /*按值查找，返回对应的结点指针*/
        TreeNode<T>* find(T target);
        /*查找最小值*/
        T getMin();
        /*查找最大值*/
        T getMax();
        /*插入结点*/
        void insert(T val);
        /*删除结点*/
        void erase(T target);
};

template <class T>
TreeNode<T>* BinarySearchTree<T>::find(T target){
    TreeNode<T>* temp = this->root;
    while(temp){
        if(target < temp->data)
            temp = temp->left;
        else if(target > temp->data)
            temp = temp->right;
        else
            return temp;
    }
    return nullptr;
}

template <class T>
T BinarySearchTree<T>::getMin(){
    TreeNode<T>* temp = this->root;
    while(temp->left){
        temp = temp->left;
    }
    return temp->data;
}

template <class T>
T BinarySearchTree<T>::getMax(){
    TreeNode<T>* temp = this->root;
    while(temp->right){
        temp = temp->right;
    }
    return temp->data;
}

/* 递归插入结点
 * 目标值小于当前结点值就往当前结点左子树插
 * 目标值大于当前结点值就往当前结点右子树插
 * 相等则什么都不做
 */
template <class T>
TreeNode<T>* BinarySearchTree<T>::insertHelper(TreeNode<T>* root, T target){
    if(!root){
        root = new TreeNode<T>();
        root->data = target;
    }else{
        if(target < root->data)
            root->left = insertHelper(root->left, target);
        if(target > root->data)
            root->right = insertHelper(root->right, target);
    }
    return root;
}

template <class T>
void BinarySearchTree<T>::insert(T val){
    this->root = insertHelper(this->root, val);
}

/* 删除目标结点(非递归)
 * father用于保存目标结点的父结点
 * 情况1：目标结点为叶结点
 *        父结点指向目标结点改为nullptr，删除目标结点
 * 情况2：目标结点有一个孩子
 *        用存在的这个孩子替换目标结点
 * 情况3：目标结点有两个孩子
 *        可以用目标结点左子树最大值的结点或者右子树最小值结点代替目标结点
 *        这里实现的是用目标结点左子树最大值的结点代替
 *        临时指针p记录目标结点左子树最大值的结点的父结点
 *        将目标结点的值用左子树最大值替换，再删除左子树最大值的结点
 */
template <class T>
void BinarySearchTree<T>::erase(T target){
    TreeNode<T>* father = nullptr;
    TreeNode<T>* temp = this->root;
    while(temp){
        if(target < temp->data){
            father = temp;
            temp = temp->left;
        }
        else if(target > temp->data){
            father = temp;
            temp = temp->right;
        }
        else{
            if(!temp->left && !temp->right){
                (father->left == temp) ? (father->left = nullptr) : (father->right = nullptr);
                delete temp;
            }else if(temp->left && temp->right){
                /*用待删除结点左子树最大值替换待删除结点的值*/
                TreeNode<T>* p;  // 记录左子树最大值所在结点的父结点
                TreeNode<T>* t = temp->left;
                while(t->right){
                    p = t;
                    t = t->right;
                }
                /*待删除结点的值被其左子树最大值所替换*/
                temp->data = t->data;
                /*删除待删除结点左子树最大值所在结点*/
                p->right = nullptr;
                delete t;
            }else{
                if(temp->left){
                    (father->left == temp) ? (father->left = temp->left) : (father->right = temp->left);
                }else{
                    (father->left == temp) ? (father->left = temp->right) : (father->right = temp->right);
                }
                delete temp;
            }
            return;
        }
    }
    throw "Not find target.";
}

#endif // !__BST_H