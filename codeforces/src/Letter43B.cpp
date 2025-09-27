//
// Created by Psy.C on 2025/9/26.
//
/*
*l用于统计小写字母出现次数
r用于统计大写字母出现次数
 *从标准输入读取第一行字符串存储到s中
 *遍历字符串s中的每个字符
*如果当前字符是小写字母(a-z)，则在l数组对应位置计数加1
s[i] - 'a'将字符转换为0-25的索引(a->0, b->1, ..., z->25)
*如果当前字符是大写字母(A-Z)，则在r数组对应位置计数加1
s[i] - 'A'将字符转换为0-25的索引(A->0, B->1, ..., Z->25)
 *
 *从标准输入读取第二行字符串存储到mes中
 *遍历第二行字符串mes中的每个字符
 *如果当前字符是小写字母，则在l数组对应位置计数减1
 *如果当前字符是大写字母，则在r数组对应位置计数减1
 *
 *遍历所有26个字母的计数数组
 *如果任何一个字母在l或r数组中的计数变为负数，说明第二行中该字母出现次数超过了第一行
 *
 *
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int N = 26;//英文字母的个数

int main() {
    vector<int> l(N, 0), r(N, 0);
    string s; getline(cin, s);

    for (int i = 0; i < s.size(); ++i) {
        if ('a' <= s[i] && s[i] <= 'z') ++l[s[i] - 'a'];
        if ('A' <= s[i] && s[i] <= 'Z') ++r[s[i] - 'A'];
    }

    string mes; getline(cin, mes);
    for (int i = 0; i < mes.size(); ++i) {
        if ('a' <= mes[i] && mes[i] <= 'z') --l[mes[i] - 'a'];
        if ('A' <= mes[i] && mes[i] <= 'Z') --r[mes[i] - 'A'];
    }

    string o("YES");
    for (int i = 0; i < N; ++i)
        if (l[i] < 0 || r[i] < 0) {
            o = "NO";
            break;
        }
    cout << o << endl;
    return 0;
}