#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<string> spilt(string str)
{
    size_t i;
    string temp = "";
    vector<string> vec;
    for(i = 0; i < str.length(); i++)
    {
        if((str[i] >= 'A') && (str[i] <= 'Z'))
            str[i] = str[i] - 'A' + 'a';
    }
    for(i = 0; i < str.length(); i++)
    {
        if((str[i] < 'a') || (str[i] >'z'))
        {
            if(temp.length() >= 3)
            {
                if(temp.length() > 10)
                    temp.erase(10);
                vec.push_back(temp);
            }
            temp = "";
            while((i < str.length()) && ((str[i] < 'a') || (str[i] >'z')))
               i++;
            i--;
        }
        else
            temp += str[i];
    }
    if(temp.length() >= 3)
    {
        if(temp.length() > 10)
            temp.erase(10);
        vec.push_back(temp);
    }
    set<string> s(vec.begin(), vec.end());
    return vector<string>(s.begin(), s.end());
}

void ex7_44()
{
    int i, a, b, N, M;
    float result;
    string base, str;
    scanf("%d", &N);
    getchar();
    vector<string> temp, files[N + 1];
    for(i = 1; i <= N; i++)
    {
        getline(cin, str);
        base = str;
        while(str != "#")
        {
            base += "@";
            getline(cin, str);
            if(str != "#")
                base += str;
        }
        files[i] = spilt(base);
    }
    scanf("%d", &M);
    for(i = 0; i < M; i++)
    {
        cin >> a >> b;
        set<string> s;
        s.insert(files[a].begin(), files[a].end());
        s.insert(files[b].begin(), files[b].end());
        result = (files[a].size() + files[b].size() - s.size()) / (float)s.size();
        printf("%.1f%%\n", 100 * result);
    }
}