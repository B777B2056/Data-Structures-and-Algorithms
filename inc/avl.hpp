#ifndef __AVL_H
#define __AVL_H

#include "bst.hpp"
#include <iostream>

/*平衡二叉搜索树*/
/*注：左旋（逆时针旋转树）与右旋（顺时针旋转树）定义与陈越课本上相反！！！！！！*/
template<class T> 
class AVL : public BinarySearchTree<T>{
    private:
        void rotateLeft(TreeNode<T> **non_balance);  // 树的左旋，LL左旋一次，LR先左旋后右旋，RL先右旋后左旋
        void rotateRight(TreeNode<T> **non_balance);  // 树的右旋，RR右旋一次
    protected:
        TreeNode<T>* insertHelper(TreeNode<T>* root, T target);
    public:
        AVL() {}
        ~AVL() { this->deleteTree(this->root); }
        /*插入结点*/
        void insert(T val);
        /*删除结点*/
        void erase(T target);
};

/* 左旋(单次)，树逆时针旋转
 * 不平衡结点的左子树高度大于右子树高度(平衡因子<=-2)
 * 且
 * 新插入结点在不平衡结点的左子树的左子树上
 */
template<class T>
void AVL<T>::rotateLeft(TreeNode<T> **non_balance){
    TreeNode<T> *new_root = (*non_balance)->right;  // 新树根结点为原根结点的右子树根结点
    (*non_balance)->right = new_root->left;  // 新树根结点原来的左子树挂在原根结点的右子树位置
    new_root->left = *non_balance;  // 新树根结点左孩子为经过变换的原树根结点
    *non_balance = new_root;  // 改变树根结点指针的指向
}

/* 右旋(单次)，树顺时针旋转
 * 不平衡结点的左子树高度小于右子树高度(平衡因子>=2)
 * 且
 * 新插入结点在不平衡结点的右子树的右子树上
 */
template<class T>
void AVL<T>::rotateRight(TreeNode<T> **non_balance){
    TreeNode<T> *new_root = (*non_balance)->left;  // 新树根结点为原根结点的左子树根结点
    (*non_balance)->left = new_root->right;  // 新树根结点原来的右子树挂在原根结点的右子树位置
    new_root->right = *non_balance;  // 新树根结点右孩子为经过变换的原树根结点
    *non_balance = new_root;  // 改变树根结点指针的指向
}

template<class T>
TreeNode<T>* AVL<T>::insertHelper(TreeNode<T>* root, T target){
    if(!root){
        root = new TreeNode<T>();
        root->data = target;
    }else{
        if(target < root->data)
            root->left = insertHelper(root->left, target);
        if(target > root->data)
            root->right = insertHelper(root->right, target);
    }
    /*平衡因子计算*/
    root->balance_factor = this->height(root->left) - this->height(root->right);  
    /*树旋转*/
    if(root->balance_factor <= -2){
        if(target > root->right->data)
            /* LL旋转
             * 新增结点挂在不平衡结点的右子树的右子树上
             * 只进行一次左单旋（针对不平衡结点为根的子树）
             */
            rotateLeft(&root);
        else{
            /* RL旋转
             * 新增结点挂在不平衡结点的右子树的左子树上
             * 先进行一次右单旋（针对不平衡结点的右孩子为根的子树），再进行一次左单旋（右单旋后的根结点）
             */
            rotateRight(&(root->right));
            rotateLeft(&root);
        }
    }
    if(root->balance_factor >= 2){
        if(target < root->left->data)
            /* RR旋转
             * 新增结点挂在不平衡结点的右=左子树的左子树上
             * 只进行一次右单旋（针对不平衡结点为根的子树）
             */
            rotateRight(&root);
        else{
            /* LR旋转
             * 新增结点挂在不平衡结点的左子树的右子树上 
             * 先进行一次左单旋（针对不平衡结点的左孩子为根的子树），再进行一次右单旋（左单旋后的根结点）
             */
            rotateLeft(&(root->left));
            rotateRight(&root);
        }
    }
    return root;
}

template<class T>
void AVL<T>::insert(T val){
    this->root = insertHelper(this->root, val);
}

#endif
