#include <iostream>
using namespace std;

struct TNode
{
    int k[2];
    int left, right;
    TNode() {}
    TNode(int v1, int v2, int l, int r) : left(l), right(r) { k[0] = v1; k[1] = v2; }
};

/*子树最小值*/
int getMinSubTree(TNode *tree, int root, int index)
{
    int minV = tree[root].k[index];
    if(tree[root].left != -1)
    {
        int minLeft = getMinSubTree(tree, tree[root].left, index);
        minV = minV < minLeft ? minV : minLeft;
    }
    if(tree[root].right != -1)
    {
        int minRight = getMinSubTree(tree, tree[root].right, index);
        minV = minV < minRight ? minV : minRight;
    }
    return minV;
}

/*子树最大值*/
int getMaxSubTree(TNode *tree, int root, int index)
{
    int maxV = tree[root].k[index];
    if(tree[root].left != -1)
    {
        int maxLeft = getMaxSubTree(tree, tree[root].left, index);
        maxV = maxV > maxLeft ? maxV : maxLeft;
    }
    if(tree[root].right != -1)
    {
        int maxRight = getMaxSubTree(tree, tree[root].right, index);
        maxV = maxV > maxRight ? maxV : maxRight;
    }
    return maxV;
}

bool isBST(TNode *tree, int root)
{
    if(root == -1)
        return true;
    /*BST必须满足其任一结点均大于左子树最大值，小于右子树最小值*/
    if((tree[root].left >= 0) && (tree[root].right >= 0))
    {
        if((tree[root].k[0] < getMaxSubTree(tree, tree[root].left, 0)) || (tree[root].k[0] > getMinSubTree(tree, tree[root].right, 0)))
            return false;
    }
    else if((tree[root].left >= 0) && (tree[root].right < 0))
    {
        if(tree[root].k[0] < getMaxSubTree(tree, tree[root].left, 0))
            return false;
    }
    else if((tree[root].left < 0) && (tree[root].right >= 0))
    {
        if(tree[root].k[0] > getMinSubTree(tree, tree[root].right, 0))
            return false;
    }
    return isBST(tree, tree[root].left) && isBST(tree, tree[root].right);
}
    
bool isHeap(TNode *tree, int root)
{
    if(root == -1)
        return true;
    /*最小堆必须满足其任一结点均小于左子树与右子树最小值*/
    if((tree[root].left >= 0) && (tree[root].right >= 0))
    {
        if((tree[root].k[1] > getMinSubTree(tree, tree[root].left, 1)) || (tree[root].k[1] > getMinSubTree(tree, tree[root].right, 1)))
            return false;
    }
    else if((tree[root].left >= 0) && (tree[root].right < 0))
    {
        if(tree[root].k[1] > getMinSubTree(tree, tree[root].left, 1))
            return false;
    }
    else if((tree[root].left < 0) && (tree[root].right >= 0))
    {
        if(tree[root].k[1] > getMinSubTree(tree, tree[root].right, 1))
            return false;
    }
    return isHeap(tree, tree[root].left) && isHeap(tree, tree[root].right);
}

void ex7_31()
{
    int N, k1, k2, l, r, i, root = -1;
    cin >> N;
    //树初始化
    int *parent = new int[N];
    TNode *tree = new TNode[N];
    for(i = 0; i < N; i++)
        parent[i] = -1;
    //建树
    for(i = 0; i < N; i++)
    {
        cin >> k1 >> k2 >> l >> r;
        TNode n(k1, k2, l, r);
        tree[i] = n;
        parent[l] = i;
        parent[r] = i;
    }
    //找出根结点
    for(i = 0; i < N; i++)
    {
        if(parent[i] == -1)
            root = i;
    }
    //判断是否是笛卡尔树
    if(isBST(tree, root) && isHeap(tree, root))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}