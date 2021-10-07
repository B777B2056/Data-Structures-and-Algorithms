/* 前序遍历的第一个节点一定是根节点,
 * 然后根据二叉搜索树左子树小于根节点,右子树大于根节点的特点,
 * 注意：左子树、右子树在前序序列里一定是连续序列，可以通过这个分割左右子树。
 * 将数组分为三部分,  根节点 - 左子树 - 右子树, 
 * 然后对于左右子树分别递归的采用此思想分解
 */
#include <iostream>
#include <vector>
using namespace std;

vector<int> bstPost, mirrorPost;

/*检查是否是BST*/
bool checkBST(int *pre, int N)
{
    if(!N)
        return true;
    int i, il = 0, s = 0;
    /*分割左右子树（找到左右子树的分界点）*/
    for(i = 1; i < N; i++)
    {
        if(pre[i] < pre[0])
            il++;
        else
            break;
    }
    /*检查右子树中有没有小于根结点的值，若有则不是BST*/
    for(i = il + 1; i < N; i++)
    {
        if(pre[i] < pre[0])
            return false;
    }
    /*递归检查左右子树*/
    int *leftSub = new int[il];
    int *rightSub = new int[N - il - 1];
    for(i = 1; i <= il; i++)
        leftSub[s++] = pre[i];
    s = 0;
    for(i = il + 1; i < N; i++)
        rightSub[s++] = pre[i];
    bool isBST = checkBST(leftSub, il) && checkBST(rightSub, N - il - 1);
    bstPost.push_back(pre[0]);
    return isBST;
}

/*检查是否是BST镜像*/
bool checkMirrorBST(int *pre, int N)
{
    if(!N)
        return true;
    int i, il = 0,s = 0;;
    /*分割左右子树（找到左右子树的分界点）*/
    for(i = 1; i < N; i++)
    {
        if(pre[i] >= pre[0])
            il++;
        else
            break;
    }
    /*检查右子树中有没有大于等于根结点的值，若有则不是BST*/
    for(i = il + 1; i < N; i++)
    {
        if(pre[i] >= pre[0])
            return false;
    }
    /*递归检查左右子树*/
    int *leftSub = new int[il];
    int *rightSub = new int[N - il - 1];
    for(i = 1; i <= il; i++)
        leftSub[s++] = pre[i];
    s = 0;
    for(i = il + 1; i < N; i++)
        rightSub[s++] = pre[i];
    bool isMirror = checkMirrorBST(leftSub, il) && checkMirrorBST(rightSub, N - il - 1);
    mirrorPost.push_back(pre[0]);
    return isMirror;
}

void ex7_28()
{
    int i, N, *pre;
    cin >> N;
    pre = new int[N];
    for(i = 0; i < N; i++)
        cin >> pre[i];
    if(checkBST(pre, N))
    {
        cout << "YES" << endl;
        cout << bstPost[0];
        for(i = 1; i < N; i++)
            cout << " " << bstPost[i];
        cout << "\n";
    }
    else if(checkMirrorBST(pre, N))
    {
        cout << "YES" << endl;
        cout << mirrorPost[0];
        for(i = 1; i < N; i++)
            cout << " " << mirrorPost[i];
        cout << "\n";
    }
    else
        cout << "NO" << endl;
}