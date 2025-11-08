//
// Created by Psy.C on 2025/9/24.
//
/*
*ind：当前在字符串s中的索引位置，初始化为0
pos：可能的插入位置，初始化为s的最后一个位置
inc：标记是否已经跳过一个字符（允许一次不匹配）
possible：标记匹配是否可能成功
 *
*遍历目标字符串t的每个字符：
如果t[i]等于s[ind]，正常匹配，ind前进一位
否则如果还没有跳过字符(!inc)且t[i]等于s[ind+1]，允许跳过s[ind]，记录跳过位置pos，ind前进两位，标记已跳过
否则匹配失败，设置possible为false并跳出循环
 *
*如果匹配可能成功：
创建向量v存储可能的插入位置
从pos位置向前搜索，找到所有与s[pos]相同的字符位置
这些位置都可以作为插入点
 *
*使用贪心策略匹配t中的每个字符
允许最多跳过s中的一个字符（相当于在该位置插入了所需字符）
找到跳过位置后，寻找该位置前后相同字符的所有位置作为可能的插入点
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#define IO ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)
using namespace std;

int main() {

    IO;
    string s, t; cin >> s >> t;

    long ind(0), pos(s.size() - 1);
    bool inc(false), possible(true);
    for (long i = 0; i < t.size(); ++i) {
        if (t[i] == s[ind]) ++ind;
        else if (!inc && t[i] == s[ind + 1]) {
            pos = ind;
            ind += 2;
            inc = true;
        } else {
            possible = false;
            break;
        }
    }

    if (possible) {
        vector<long> v;
        for (long i = pos; i >= 0; --i) {
            if (s[i] == s[pos]) v.push_back(i + 1);
            else break;
        }
        printf("%ld\n", v.size());
        for (long i = v.size() - 1; i >= 0; --i)
            printf("%ld ", v[i]);
        puts("");
    } else {
        puts("0");
    }
    return 0;
}