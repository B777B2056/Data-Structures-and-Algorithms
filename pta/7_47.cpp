#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

void ex7_47()
{
    int i, a, N, K;
    size_t j, C;
    string name;
    cin >> N >> K;
    vector<string> vec[K + 1];
    for(i = 0; i < N; i++)
    {
        cin >> name >> C;
        string str = "";
        for(j = 0; j < name.length(); j++)
        {
            if((name[j] >= '0') && (name[j] <= '9'))
                str += name[j];
        }
        for(j = 0; j < C; j++)
        {
            cin >> a;
            vec[a].push_back(name);
        }
    }
    for(i = 1; i <= K; i++)
        sort(vec[i].begin(),vec[i].end());
    for(i = 1; i <= K; i++)
    {
        cout << i << " " << vec[i].size() << "\n";
        for(string s : vec[i])
            cout << s << "\n";
    }
}
