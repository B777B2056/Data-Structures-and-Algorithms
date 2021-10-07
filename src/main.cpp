#include "../inc/linkedlist.hpp"
#include "../inc/stack_queue.hpp"
#include "../inc/binary_tree.hpp"
#include "../inc/bst.hpp"
#include "../inc/avl.hpp"
#include "../inc/heap.hpp"
#include "../inc/huffman.hpp"
#include "../inc/set.hpp"
#include "../inc/graph.hpp"
#include "../inc/hashtable.hpp"
#include "../inc/kmp.hpp"
#include "../inc/sort.hpp"
#include "../inc/application.hpp"
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// #define __SINGLE_LINKED  //单向链表
// #define __DOUBLE_LINKED  //双向链表
// #define __CIRCULAR_LINKED  //环形链表
// #define __STACK  //栈
// #define __QUEUE  //队列
// #define __DEQUE  //双端队列
// #define __BRACKET_MATCHING  //括号匹配
// #define __EXPRESSION  //中缀表达式转换为后缀表达式并计算
// #define __BINARY_TREE  //二叉树
// #define __BST  //二叉搜索树
// #define __AVL  //平衡二叉搜索树
// #define __HEAP  //大根堆
// #define __HUFFMAN  //赫夫曼编码
// #define __SET  //并查集
// #define __GRAPH  //图
// #define __HASH  // 哈希表
// #define __KMP  // KMP串模式匹配算法
#define __SORT  // 排序算法

void test_single_linked();
void test_double_linked(vector<int>& v);
void test_circular_linked(vector<int>& v);
void test_stack(vector<int>& v);
void test_queue(vector<int>& v);
void test_deque(vector<int>& v);    
void test_binary_tree();
void test_bst();
void test_avl();
void test_heap();
void test_huffman();
void test_set();
void test_graph();
void test_hash();
void test_kmp();
void test_sort();

int main(){
    vector<int> v(5);
    for(size_t i = 0; i < v.size(); i++)
        v[i] = i + 1;
#ifdef __SINGLE_LINKED
    test_single_linked();
#endif

#ifdef __DOUBLE_LINKED
    test_double_linked(v);
#endif

#ifdef __CIRCULAR_LINKED
    test_circular_linked(v);
#endif

#ifdef __STACK
    test_stack(v);
#endif

#ifdef __QUEUE
    test_queue(v);
#endif

#ifdef __DEQUE
    test_deque(v);
#endif

#ifdef __BRACKET_MATCHING
    string str;
    cout << "Input String...";
    getline(cin, str);
    bool isMatch = bracket_matching(str);
    cout << (isMatch ? "The bracket is match." : "Wrong bracket") << endl;
#endif

#ifdef __EXPRESSION
    int result;
    string str, inverse;
    cout << "Input Expression(Only Support + - * /)...";
    getline(cin, str);
    result = getValFromExpression(str, inverse);
    cout << str << "\'s Inverse Polish expression is " 
         << inverse << "\n"
         << "Result = " 
         <<  result
         << endl;
#endif

#ifdef __BINARY_TREE
    test_binary_tree();
#endif

#ifdef __BST
    test_bst();
#endif

#ifdef __AVL
    test_avl();
#endif 

#ifdef __HEAP
    test_heap();
#endif 

#ifdef __HUFFMAN
    test_huffman();
#endif

#ifdef __SET
    test_set();
#endif

#ifdef __GRAPH
    test_graph();
#endif

#ifdef __HASH
    test_hash();
#endif

#ifdef __KMP
    test_kmp();
#endif

#ifdef __SORT
    test_sort();
#endif

    return 0;
}

void test_single_linked(){
    vector<char> v;
    cout << "Input Elements..."<< endl;
    for(char ch = getchar(); ch != '$'; ch = getchar())
        v.push_back(ch);
    SingleLinkedList<char> a;
    for(char val : v){
        a.insert(a.getLength(), val);
    }
    a.printLinked();
    cout << "Length = " << a.getLength() << "\n";
    cout << "Index 3's value is " << a.getVal(3) << "\n";
    cout << "Value D's index is " << a.search('D') << "\n";
    a.insert(1, 'C');
    a.printLinked();
    a.remove('D');
    a.printLinked();
    a.reverse();
    a.printLinked();
}

void test_double_linked(vector<int>& v){
    DoubleLinkedList<int> a(v);
    a.printLinked();
    cout << "Length = " << a.getLength() << "\n";
    cout << "Index 3's value is " << a.getVal(3) << "\n";
    cout << "Value 3's index is " << a.search(3) << "\n";
    a.insert(1, 2);
    a.printLinked();
    a.remove(5);
    a.printLinked();
    a.reverse();
    a.printLinked();
}

void test_circular_linked(vector<int>& v){
    CircularLinkedList<int> a(v);
    a.printLinked();
    cout << "Length = " << a.getLength() << "\n";
    cout << "Index 3's value is " << a.getVal(3) << "\n";
    cout << "Value 3's index is " << a.search(3) << "\n";
    a.insert(1, 2);
    a.printLinked();
    a.remove(5);
    a.printLinked();
}

void test_stack(vector<int>& v){
    Stack<int> s;
    for(int val : v)
        s.push(val);
    s.printStack();
    cout << "Stack Top=" << s.getTop() << "\n";
    s.pop();
    cout << "After Pop: ";
    s.printStack();
}

void test_queue(vector<int>& v){
    Queue<int> q;
    for(int val : v){
        q.enQueue(val);
        q.printQueue();
    }
    cout << "Queue Head=" << q.deQueue() << " , After Delete Head: ";
    q.printQueue();
}

void test_deque(vector<int>& v){
    Deque<int> d;
    cout << "Left Push\n";
    for(int val : v){
        d.pushLeft(val);
        d.printDeque();
    }
    cout << "Right Push\n";
    for(int val : v){
        d.pushRight(val);
        d.printDeque();
    }
    cout << "Left Head = " << d.popLeft() << "\n";
    cout << "After Pop Left: ";
    d.printDeque();
    cout << "Right Head = " << d.popRight() << "\n";
    cout << "After Pop Right: ";
    d.printDeque();
}

void test_binary_tree(){
    vector<char> v;
    cout << "Input Binary Tree..."<< endl;
    for(char ch = getchar(); ch != '$'; ch = getchar())
        v.push_back(ch);
    BinaryTree<char> tree;
    createTree(v, tree);
    for(int i = 0; i < 4; i++){
        switch (i){
            case 0:
                cout << "Pre Order:" << endl;
                break;
            case 1:
                cout << "In Order:" << endl;
                break;
            case 2:
                cout << "Post Order:" << endl;
                break;
            case 3:
                cout << "Level Order:" << endl;
                break;
        }
        v.clear();
        v = tree.traversal(i);
        for(char ch : v){
            if(ch != '#') 
                cout << ch;
        }
        cout << "\n";
    }
    cout << "Height of tree: " << tree.getHeight(1);
}

void test_bst(){
    BinarySearchTree<int> bst;
    cout << "Input Numbers..."<< endl;
    for(char ch = getchar(); ch != '$'; ch = getchar())
        bst.insert(ch - '0');
    cout << "Level Order:";
    vector<int> v = bst.traversal(3);
    for(int i : v)
        cout << i << " ";
    cout << "\nHeight of Binary Search Tree is " << bst.getHeight(0) << "\n";
    cout << "Min Value = " << bst.getMin() << endl;
    cout << "Max Value = " << bst.getMax() << endl;
    cout << "Input value which you want delete..." << endl;
    int target;
    cin >> target;
    bst.erase(target);
    cout << "After delete " << target << ", Level Order:";
    vector<int> a = bst.traversal(3);
    for(int i : a)
        cout << i << " ";
    cout << "\nHeight of Binary Search Tree is " << bst.getHeight(0) << "\n";
}

void test_avl(){
    AVL<int> a;
    cout << "Input Numbers..."<< endl;
    for(char ch = getchar(); ch != '$'; ch = getchar())
        a.insert(ch - '0');
    cout << "Level Order:";
    vector<int> m = a.traversal(3);
    for(int i : m)
        cout << i << " ";
}

void test_heap()
{
    MaxHeap<int> heap(30);
    for(char ch = getchar(); ch != '$'; ch = getchar())
        heap.insert(ch - '0');
    cout << "Max value is " << heap.eraseMaxVal() << endl;
}

void test_huffman()
{
    string code, str;
    cout << "Input Text(Warning: Each character's frequency CANNOT be repeat.)..."<< endl;
    cin >> str;
    cout << "Before encode: " << str << endl;
    map<char, int> m;
    for(int i = 0; i < str.length(); i++)
        m[str[i]] = count(str.begin(), str.end(), str[i]);
    HuffmanCode hfm;
    hfm.generateHuffmanTree(m);
    code = hfm.encode(str);
    cout << "After encode: " << code << endl;
    cout << "After decode: " << hfm.decode(code) << endl;
}

void test_set()
{
    vector<vector<int>> v = {{1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11, 12}};
    UnionFindSet<int> s(v);
    //填充完成后打印并查集树结构
    cout << "After build tree:\n";
    s.printUFTree();
    //合并完成后打印并查集树结构(朴素查找算法)
    cout << "Navie Seach:\n";
    s.unionData(2, 5, false);
    s.printUFTree();
    //合并完成后打印并查集树结构(路径压缩查找算法)
    cout << "Use Path Compression:\n";
    s.unionData(2, 5, true);
    s.printUFTree();
}

void test_graph()
{
    int node_num, edge_num, root;
    cout << "Input number of node: ";
    cin >> node_num;
    cout << "Input number of edge: ";
    cin >> edge_num;
    Graph<char> g(node_num, edge_num);
    int i;
    char vertexes[node_num];
    cout << "Input vertex in graph... ";
    for(i = 0; i < node_num; i++)
        cin >> vertexes[i];
    g.createVertx(vertexes);
    cout << "Insert edge in graph... " << endl;
    for(i = 0; i < edge_num; i++)
    {
        int begin, end, weight;
        cout << "Input begin vertex index of edge: ";
        cin >> begin;
        cout << "Input end vertex index of edge: ";
        cin >> end;
        cout << "Input weight of edge: ";
        cin >> weight;
        g.insertEdge(begin, end, weight);
    }
    cout << "DFS result: ";
    g.traversal(DFS);
    cout << "\nBFS result: ";
    g.traversal(BFS);
    int sv, ev;
    cout << "\nInput source vertex's index: ";
    cin >> sv;
    cout << "Input end vertex's index: ";
    cin >> ev;
    cout << "============= Dijkstra result =============\n";
    g.shortestPath(sv, ev, Dijkstra);
    cout << "============= Floyd result =============\n";
    g.shortestPath(sv, ev, Floyd);
    cout << "============= Warning: MST is only for UNDIRECTED Graph! =============\n";
    cout << "Input MST root index for Prim: ";
    cin >> root;
    cout << "============= MST Prim result =============\n";
    g.MST(root, Prim);
    cout << "============= MST Kruskal result =============\n";
    g.MST(root, Kruskal);
    cout << "============= Topological sort result =============\n";
    g.topologicalSortAOV();
}

void test_hash()
{
    int N, i, s, key;
    char value, ch;
    double loadF;
    HashTable<char> *ht;
    cout << "Input number of elements: ";
    cin >> N;
    cout << "Input load factor: ";
    cin >> loadF;
    cout << "Linear Detection(Input 0), Square Detection(Input 1) or Separate Chaining(Input 2)? ";
    cin >> s;
    if(s == 0)
        ht = new HashTable<char>(N, loadF, LinearDetection);
    else if(s == 1)
        ht = new HashTable<char>(N, loadF, SquareDetection);
    else if(s == 2)
        ht = new HashTable<char>(N, loadF, SeparateChaining);
    else
    {
        cout << "Wrong input." << endl;
        return;
    }
    cout << "Input elements' KEY and VALUE(like \"4 6\"):\n";
    for(int i = 0; i < N; i++)
    {
        cin >> key >> value;
        ht->insert(key, value);
        int index = ht->find(key, &ch);
    }    
    cout << "Input key of element which you want to find: ";
    cin >> key;
    if(ht->find(key, &value) != -1)
        cout << "key = " << key << ", value = " << value << endl;
    else
        cout << "Not Find." << endl;
    cout << "Input key of element which you want to delete: ";
    cin >> key;
    cout << "After delete key " << key << ":\n";
    ht->erase(key);
    if(ht->find(key, &value) != -1)
        cout << "Find key = " << key << ", value = " << value << ",  Delete Failed!" << endl;
    else
        cout << "Not Find key " << key << ", Delete Success!" << endl;
    delete ht;
}

void test_kmp()
{
    string s, p;
    cout << "Input source string: ";
    getline(cin, s);
    cout << "Input pattern string: ";
    getline(cin, p);
    int i = KMP(s, p);
    if(i == NOT_MATCH)
        cout << "Pattern string not match." << endl;
    else
        cout << "Match index of source string is " << i << endl;
}

/*由于分桶原则较为复杂且桶排序实用价值不大，因此桶排序以伪代码形式写在sort.hpp的末尾*/
void test_sort()
{
    int i, j, t, N, *a[7];
    cout << "Input length of array: ";
    cin >> N;
    for(i = 0; i < 7; i++)
        a[i] = new int[N];
    cout << "Input arrar(like: 1 2 3 4): ";
    for(i = 0; i < N; i++)
    {
        cin >> t;
        for(j = 0; j < 7; j++)
            a[j][i] = t;
    }
    bubbleSort(N, a[0]);
    cout << "After bubble sort: ";
    for(i = 0; i < N; i++)
        cout << a[0][i] << " ";
    cout << "\n";
    insertSort(N, a[1]);
    cout << "After insert sort: ";
    for(i = 0; i < N; i++)
        cout << a[1][i] << " ";
    cout << "\n";
    selectionSort(N, a[2]);
    cout << "After selection sort: ";
    for(i = 0; i < N; i++)
        cout << a[2][i] << " ";
    cout << "\n";
    heapSort(N, a[3]);
    cout << "After heap sort: ";
    for(i = 0; i < N; i++)
        cout << a[3][i] << " ";
    cout << "\n";
    quickSort(N, a[4]);
    cout << "After quick sort: ";
    for(i = 0; i < N; i++)
        cout << a[4][i] << " ";
    cout << "\n";
    mergeSort(N, a[5]);
    cout << "After merge sort: ";
    for(i = 0; i < N; i++)
        cout << a[5][i] << " ";
    cout << "\n";
    int *r = tableSort(N, a[6]);
    cout << "After table sort: ";
    for(i = 0; i < N; i++)
        cout << a[6][r[i]] << " ";
    delete []r;
    cout << "\n";
}
