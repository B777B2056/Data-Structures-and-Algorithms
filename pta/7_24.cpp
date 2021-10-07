#include <iostream>
#include <string>
using namespace std;

/*二叉搜索树的应用*/

struct Seed
{
    string name, lowerName;
    int cnt;
    Seed *left, *right;
    Seed(string n, string ln) : name(n), lowerName(ln), cnt(1), left(nullptr), right(nullptr) {}
};

Seed *bstInsert(string name, string lowerName, Seed *root)
{
    if(!root)
    {
        root = new Seed(name, lowerName);
    }
    else
    {
        if(name < root->name)
            root->left = bstInsert(name, lowerName, root->left);
        else if(name > root->name)
            root->right = bstInsert(name, lowerName, root->right);
        else
            ++root->cnt;
    }
    return root;
}

void inOrder(Seed *root, int N)
{
    if(!root)
        return;
    inOrder(root->left, N);
    printf("%s %.4f%%\n", root->name.c_str(), (double)100 * root->cnt / N);
    inOrder(root->right, N);
}

int main()
{
    int i, N;
    string name, lowerName;
    scanf("%d", &N);
    getchar();
    Seed *root = nullptr;
    for(i = 0; i < N; ++i)
    {
        getline(cin, name);
        lowerName = "";
        for(char ch : name)
        {
            if(ch >= 'A' && ch <= 'Z')
                lowerName += (ch - 'A' + 'a');
            else
                lowerName += ch;
        }
        root = bstInsert(name, lowerName, root);
    }
    inOrder(root, N);
    return 0;
}