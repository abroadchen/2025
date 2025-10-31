//
// Created by Psy.C on 2025/10/30.
//
/*
*p：存储最大目录层级数
q：存储单个根目录出现的最大次数
*s：存储完整的输入路径
s1：存储根目录部分
s2：存储子目录路径
 *
 *循环读取输入，每次读取一个由空格分隔的字符串，直到没有更多输入
 *将读取的字符数组转换为字符串存储在s中
 *从索引3开始查找第一个反斜杠\的位置，确定根目录结束位置
 *提取从开始到第一个反斜杠的子字符串作为根目录名
 *在映射m中增加该根目录的计数
 *清空子目录字符串
 *从第一个反斜杠后的位置开始遍历剩余字符
 *将当前字符添加到子目录字符串中
 *如果当前字符是反斜杠，则将当前累积的子目录路径插入到对应根目录的集合中
 *
 */
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#define sz(a) ((int)(a).size())
using namespace std;
const int N = 105;
int i, p, q;
char c[N];//读取输入字符串
string s, s1, s2;
map<string,int> m;//键为字符串（根目录名），值为整数（出现次数）
map<string,int>::iterator itm;
map<string,set<string>> d;//键为根目录名，值为该根目录下的子目录集合
map<string,set<string>>::iterator itd;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (scanf("%s", &c) == 1) {
        s = c;
        for (i = 3; s[i] != '\\'; ++i);
        s1 = s.substr(0, i);
        m[s1]++;
        s2 = "";
        for (++i; i < (int)s.length(); ++i) {
            s2.push_back(s[i]);
            if (s[i] == '\\') d[s1].insert(s2);
        }
    }
    p = 0;
    for (itd = d.begin(); itd != d.end(); ++itd) {
        p = max(p, sz(itd->second));
    }
    q = 0;
    for (itm = m.begin(); itm != m.end(); ++itm) {
        q = max(q, itm->second);
    }
    cout << p << " " << q;
    return 0;
}