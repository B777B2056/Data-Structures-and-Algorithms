#include <iostream>
using namespace std;

struct TNode
{
    char ch;
    TNode *left, *right;
    TNode() : left(nullptr), right(nullptr) {}
};

TNode *creatTree(char *pre, char *in, TNode *root, int N)
{
    if(!N)
        return nullptr;
    int j, k, m, s = 0;
    char *leftSubPre, *leftSubIn, *rightSubPre, *rightSubIn;
    root = new TNode();
    root->ch = pre[0];
    for(j = 0; j < N; j++)
    {
        if(pre[0] == in[j])
            break;
    }
    //0~j-1左子树中序，j+1~N-1右子树中序
    leftSubIn = new char[j];
    rightSubIn = new char[N - j - 1];
    for(k = 0; k < j; k++)
    {
        leftSubIn[k] = in[k];
    }
    for(k = 0; k < N - j - 1; k++)
    {
        rightSubIn[k] = in[j + k + 1];
    }
    //构建左右子树前序
    leftSubPre = new char[j];
    rightSubPre = new char[N - j - 1];
    s = 0;
    for(k = 0; k < N; k++)
    {
        for(m = 0; m < j; m++)
        {
            if(pre[k] == leftSubIn[m])
            {
                leftSubPre[s++] = pre[k];
                break;
            }
        }
    }
    s = 0;
    for(k = 0; k < N; k++)
    {
        for(m = 0; m < N - j - 1; m++)
        {
            if(pre[k] == rightSubIn[m])
            {
                rightSubPre[s++] = pre[k];
                break;
            }
        }
    }
    //递归构建左右子树
    root->left = creatTree(leftSubPre, leftSubIn, root->left, j);
    root->right = creatTree(rightSubPre, rightSubIn, root->right, N - j - 1);
    return root;
}

int height(TNode *root)
{
    if(!root)
        return 0;
    int maxLeft = height(root->left);
    int maxRight = height(root->right);
    return 1 + (maxLeft < maxRight ? maxRight :maxLeft);
}

void ex7_23()
{
    int i, N;
    cin >> N;
    TNode *root = nullptr;
    char *preOrder = new char[N];
    char *inOrder = new char[N];
    for(i = 0; i < N; i++)
        cin >> preOrder[i];
    for(i = 0; i < N; i++)
        cin >> inOrder[i];
    root = creatTree(preOrder, inOrder, root, N);
    cout << height(root) << endl;
}