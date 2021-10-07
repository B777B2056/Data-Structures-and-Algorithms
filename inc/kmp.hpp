#ifndef __KMP_H
#define __KMP_H

#include <string>
#include <vector>
#include <iostream>

#define NOT_MATCH -1

/* 关于next数组
 * 1、next数组下标从0开始，kmp算法依然可以运行，但会导致其每个元素与真正的next数组少1；（源串索引由0开始则next也由0开始）
 * 2、next数组下标从1开始，得到的是真正的next数组。（源串索引由1开始则next也由1开始）
 * 3、无论next从0还是从1开始，i与j的初始化都必须有i = j + 1；next首元素的值与j初值必须一致。
 * 4、若需将next数组由0开始改为由1开始，在kmp函数内，两指针i与j的初始值均变为1，next数组长度也变为模式串长度+1。
 */

/*next数组下标从0开始*/
void getNext(const std::string& pattern, std::vector<int>& next)
{
    next[0] = -1;
    int i = 0, j = -1;
    /*相当于模式串自己与自己做匹配*/
    while(i < pattern.length())
    {
        if((j == -1) || (pattern[i] == pattern[j]))
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

/*next数组下标从1开始，得到的是真正的next数组*/
// void getNext(const std::string& pattern, std::vector<int>& next)
// {
//     next[1] = 0;
//     int i = 1, j = 0;
//     /*相当于模式串自己与自己做匹配*/
//     while(i <= pattern.length())
//     {
//         if((j == 0) || (pattern[i] == pattern[j]))
//         {
//             ++i;
//             ++j;
//             next[i] = j;
//         }
//         else
//         {
//             j = next[j];
//         }
//     }
// }

int KMP(const std::string& source, const std::string& pattern)
{
    if(source.length() < pattern.length())
        throw "Pattern string must be shorter than source string.";
    std::vector<int> next(pattern.length());
    getNext(pattern, next);
    std::cout << "NEXT array: ";
    for(std::size_t t = 0; t < next.size(); t++)
        std::cout << next[t] << " ";
    std::cout << "\n";
    unsigned int i = 0, j = 0;
    while((i < source.length()) && (j < pattern.length()))
    {
        /*源串与模式串中元素相等时，两串指针均向前一步*/
        if((j == 0) || (source[i] == pattern[j]))
        {
            ++i;
            ++j;
        }
        /*源串与模式串中元素不相等时，源串指针不动，模式串指针回退一次*/
        else
        {
            j = next[j];
        }
    }
    /*如果匹配成功，即：模式串指针移动到了模式串末尾，则返回第一次匹配成功时源串的索引（当前源串索引减去模式串长度即可）*/
    if(j == pattern.length())
        return i - pattern.length();
    /*匹配失败，返回失败宏*/
    else
        return NOT_MATCH;
}

#endif
