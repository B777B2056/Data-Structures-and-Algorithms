#ifndef __HOFFMAN_H
#define __HOFFMAN_H

#include <map>
#include <string>
#include "heap.hpp"

#include <iostream>

//带权树结点
struct WeightNode
{
    char data;
    int weight;  // 权重
    WeightNode *left, *right;

    WeightNode() : left(nullptr), right(nullptr) {}
};

/*哈夫曼编码*/
class HuffmanCode
{
    private:
        //赫夫曼树根结点
        WeightNode *root;
        //路径
        std::string path = "";
        //编码密码本
        std::map<char, std::string> encodeBook;
        //解码密码本(key=该字符的编码，value=该字符)
        std::map<std::string, char> decodeBook;
        //用0和1替换赫夫曼树上的权重，准备编码(0换左孩子权重，1换右孩子权重)
        void replaceWeight(WeightNode *node);
        //寻找某字符在赫夫曼树里对应的路径
        void findPath(WeightNode *node);
        //释放树内存的辅助函数
        void deleteHelper(WeightNode *node);
    public:
        HuffmanCode() : root(nullptr) {}
        ~HuffmanCode() { this->deleteHelper(this->root); }
        //根据文本生成一颗哈夫曼树(各字母所占权重由该函数负责计算)
        void generateHuffmanTree(std::map<char, int>& char_freq);
        //将原文本编码为哈夫曼编码，编码后内容储存在target中
        std::string encode(const std::string& text);
        //将哈夫曼编码解码为原文本
        std::string decode(std::string& code);
};

//哈夫曼树结点比较函数
bool cmp(WeightNode *a, WeightNode*b)
{
    return a->weight < b->weight;
}

/* 根据权重创建哈夫曼树
 * 1、各树结点按权重大小排序(从小到大)，本方法里树结点插入小根堆；
 * 当小根堆不空时：
 * 2、取堆中权重最小的两个树结点(将二者从堆中弹出)，二者中权重最小的为左孩子结点，权重次小的为右孩子结点；
 * 3、以二者权重之和构造二者的父结点；
 * 4、二者父结点插入堆。
 * 循环结束后，赫夫曼树根结点为堆中存在的最后一个元素。
 */
void HuffmanCode::generateHuffmanTree(std::map<char, int>& char_freq)
{
    //创建各字符对应的树结点,存入小根堆(比较规则与大根堆相反就是小根堆)
    MaxHeap<WeightNode *> heap(char_freq.size(), cmp);
    std::map<char, int>::iterator iter;
    for(iter = char_freq.begin(); iter != char_freq.end(); iter++)
    {
        WeightNode *node = new WeightNode();
        node->data = iter->first;
        node->weight = iter->second;
        heap.insert(node);
    }
    //创建哈夫曼树
    while(!heap.isEmpty())
    {  
        WeightNode *lchild = heap.eraseMaxVal();
        if(heap.isEmpty())
        {
            root = lchild;
            break;
        }
        WeightNode *father = new WeightNode();
        WeightNode *rchild = heap.eraseMaxVal();
        father->data = '-';
        father->weight = lchild->weight + rchild->weight;
        father->left = lchild;
        father->right = rchild;
        heap.insert(father);
    }
}

std::string HuffmanCode::encode(const std::string& text)
{
    //替换权重
    replaceWeight(root);
    //构造密码本(对每个字符寻找从树根结点到其叶结点的路径，走过的路径的权重组合就是该字符的哈夫曼编码)
    findPath(root);
    //打印密码本
    std::cout << "Code Book:" << std::endl;
    std::map<std::string, char> ::iterator iter;
    for(iter = decodeBook.begin(); iter != decodeBook.end(); iter++)
        std::cout << "Char: " << iter->second << ", Code: " << iter->first << std::endl;
    //编码
    std::string s = "";
    for(int i = 0; i < text.length(); i++)
    {
        std::map<char, std::string> ::iterator iter;
        iter = encodeBook.find(text[i]);
        if(iter != encodeBook.end())
            s += iter->second;
    }
    return s;
}

void HuffmanCode::replaceWeight(WeightNode *node)
{
    if(!node) return;
    if(node->left)
    {
        node->left->weight = 0;
        replaceWeight(node->left);
    }
    if(node->right)
    {
        node->right->weight = 1;
        replaceWeight(node->right);
    }
}

//重要！二叉树遍历寻找到所有叶结点的路径
void HuffmanCode::findPath(WeightNode *node)
{
    if(!node) 
        return;
    if(node != root)
    {
        path += std::to_string(node->weight);
        //遍历到叶结点时填充密码本
        if(!node->left && !node->right)
        {
            encodeBook[node->data] = path;
            decodeBook[path] = node->data;
            path = path.substr(0, path.length() - 1);
        }
    }
    findPath(node->left);
    findPath(node->right);   
}

std::string HuffmanCode::decode(std::string& code)
{
    int i, j;
    std::string m = "";
    std::string text = "";
    for(i = 0; i < code.length(); i += j)
    {
        j = 0;     
        std::map<std::string, char> ::iterator iter;
        while(i + j < code.length())
        {
            m += code[i + j];
            iter = decodeBook.find(m);
            //找到该编码
            if(iter != decodeBook.end())
            {
                m = "";
                text += iter->second;
                break;
            }
            j++;
        }
        j++;
    }
    return text;
}

void HuffmanCode::deleteHelper(WeightNode *node)
{
    if(!node) return;
    deleteHelper(node->left);
    deleteHelper(node->right);
    delete node;
}

#endif
