#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

/*先进行分词（这题的分词很恶心），然后采用哈希表的思想存储热门话题并计数*/

// 转换为全小写并去掉所有非英文字母和数字的符号
string handle(string& source)
{
    size_t i;
    string r = "", m = "";
    // 去除前导空格
    for(i = 0; i < source.length(); i++)
    {
        if(source[i] != ' ')
            break;
    }
    while(i < source.length())
    {
        char ch = source[i];
        // 大写转小写
        if((ch >= 'A') && (ch <= 'Z'))
            ch = ch - 'A' + 'a';
        // 保留小写与数字
        if(((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')))
            r += ch;
        // 其余字符转空格
        else
            r += " ";
        i++;
    }
    // 多个空格的情况只保留一个空格
    for(i = 0; i < r.length(); i++)
    {
        if(r[i] == ' ')
        {
            while((i < r.length()) && (r[i] == ' '))
                i++;
            if(i < r.length())
                m += " ";
            i--;
        }
        else
            m += r[i];
    }
    return m;
}

// 分词——只有两个#间的单次才算一个话题，而且#不能重复使用
// 比如#one#two#three#，只算两个话题（one和three）
vector<string> spiltByShap(string& source)
{
    size_t i = 0;
    vector<string> topics;
    while(i < source.length())
    {
        if(source[i] == '#')
        {
            string r = "";
            i++;
            while((i < source.length()) && (source[i] != '#'))
            {
                r += source[i];
                i++;
            }
            if((i < source.length()) && (source[i] == '#'))
            {
                r = handle(r);
                if(r.length())
                {
                    if((topics.size() == 0) || (topics[topics.size() - 1] != r))
                        topics.push_back(r);
                }
            }
        }
        i++;
    }
    return topics;
}

void ex7_46()
{
    int i, item = 0, maxItem = 0, N;
    string s, most_topic;
    cin >> N;
    getchar();
    map<string, int> table;
    map<string, int>::iterator iter;
    // 加入哈希表并统计每条话题的个数
    for(i = 0; i < N; i++)
    {
        getline(cin, s);
        vector<string> m = spiltByShap(s);
        for(string t : m)
        {
            if(!t.empty())
            {
                iter = table.find(t);
                if(iter == table.end())
                    table[t] = 1;
                else
                    ++table[t];
            }
        }
    }
    // 找到最热门话题被提到的个数
    for(iter = table.begin(); iter != table.end(); ++iter)
    {
        if(iter->second > maxItem)
            maxItem = iter->second;
    }
    // 找到字典序最小的最热门话题以及最热门话题的个数
    for(iter = table.begin(); iter != table.end(); ++iter)
    {
        if(iter->second == maxItem)
        {
            ++item;
            if(item == 1)
                most_topic = iter->first;
            else
            {
                if(most_topic > iter->first)
                    most_topic = iter->first;
            }
        }
    }
    // 输出
    most_topic[0] = most_topic[0] - 'a' + 'A';
    cout << most_topic << "\n" << maxItem << "\n";
    if(item > 1)
        cout << "And " << item - 1 << " more ...\n";
}