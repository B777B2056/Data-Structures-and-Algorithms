#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum status{EMPTY, FILLED};

struct User
{
    long id;
    string password;
    status st; 
    User() : st(EMPTY) {}
    User(long i, string pw, status s) : id(i), password(pw), st(s) {}
};

// 将账号对表长取余后作为key
inline
int hashMethod(int P, long id)
{
    return id % P;
}

// 分离连接法解决哈希冲突
void ex7_15()
{
    ios::sync_with_stdio(false);
    int i, postion, N;
    char command;
    long id;
    string password;
    bool isExist, isFind;
    cin >> N;
    vector<User> hashTable[N];
    for(i = 0; i < N; i++)
    {
        cin >> command >> id >> password;
        // 哈希表插入
        if(command == 'N')
        {
            isExist = false;
            postion = hashMethod(N, id);
            for(User u : hashTable[postion])
            {
                if(u.id == id)
                {
                    isExist = true;
                    break;
                }
            }
            if(isExist)
                cout << "ERROR: Exist\n";
            else
            {
                hashTable[postion].push_back(User(id, password, FILLED)); 
                cout << "New: OK\n";
            }
        }
        // 哈希表查找
        if(command == 'L')
        {
            isFind = false;
            postion = hashMethod(N, id);
            for(User u : hashTable[postion])
            {
                if(u.id == id)
                {
                    isFind = true;
                    if(u.password == password)
                        cout << "Login: OK\n";
                    else
                        cout << "ERROR: Wrong PW\n";
                    break;
                }
            }
            if(!isFind)
                cout << "ERROR: Not Exist\n";
        }
    }
}