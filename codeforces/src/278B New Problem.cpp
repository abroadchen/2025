//
// Created by Psy.C on 2025/12/26.
//
/*
* ch[30]：临时存储输入的字符串（最大长度30）
e1[26] = {}：布尔数组，记录每个字母是否出现过（a-z对应0-25）
e2[26][26] = {}：二维布尔数组，记录相邻字母对是否出现过
 *
*循环读入n个字符串
第一个内循环：遍历字符串中每个字符，标记对应字母在e1中为true
ch[j] - 'a'：将字符转换为0-25的索引
第二个内循环：遍历相邻字符对，标记在e2中为true
ch[j-1] - 'a'：前一个字符的索引
ch[j] - 'a'：后一个字符的索引
 *
*首先查找缺失的单个字母
遍历'a'到'z'，如果某个字母没有出现过（!e1[c-'a']）
输出该字母，设置found标记，跳出循环

如果没有找到缺失的单个字母，查找缺失的两个字母组合
双重循环遍历所有可能的字母对(c1, c2)
如果字母对(c1,c2)没有出现过，输出该组合，设置found标记，跳出循环*
 *
*预处理：O(总字符数)
查找：O(26) + O(26²) = O(702) = O(1)
总体：O(总字符数)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    char ch[30];
    bool e1[26] = {}, e2[26][26] = {};
    for (int i = 0; i < n; ++i) {
        cin >> ch;
        for (int j = 0; j < strlen(ch); ++j) e1[ch[j] - 'a'] = true;
        for (int j = 1; j < strlen(ch); ++j) e2[ch[j-1] - 'a'][ch[j] - 'a'] = true;
    }
    bool found = false;
    for (char c = 'a'; c <= 'z'; ++c) if (!e1[c - 'a']) {
        cout << c << '\n';
        found = true;
        break;
    }
    if (!found) {
        for (char c1 = 'a'; !found && c1 <= 'z'; ++c1) {
            for (char c2 = 'a'; c2 <= 'z'; ++c2) if (!e2[c1 - 'a'][c2 - 'a']) {
                cout << c1 << c2 << '\n';
                found = true;
                break;
            }
        }
    }
    return 0;
}