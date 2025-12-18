//
// Created by Psy.C on 2025/12/17.
//
/*
*p: 分割后的段数计数器
pre: 记录连续冒号(::)的位置
arr[10]: 存储分割后的各段字符串
 *
*如果字符串末尾不是冒号，则添加一个冒号（统一处理）
添加空格作为结束标记
初始化变量：x为段起始位置，p为段计数，pre为连续冒号位置
*遍历字符串查找冒号
遇到冒号时：
段数加1
提取当前段内容（从x到i-1）
更新下一段起始位置
特殊处理连续冒号(::)情况：记录位置并跳过
 *
*调用split函数解析地址
cur存储展开后的地址（不含冒号）
*遍历每一段：
如果段长度不足4位，在前面补0
添加当前段内容
如果当前位置是连续冒号位置，补充缺失的0000段
*构造最终结果：
每4个字符后添加冒号
总共32个十六进制字符，分成8组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int p, pre;
string arr[10];
void split(string s) {
    if (s[s.size() - 1] != ':') s += ':';
    s += ' ';
    int x = 0; p = 0, pre = -1;
    for (int i = 0; i < s.size() - 1; ++i) {
        if (s[i] == ':') {
            ++p; arr[p] = "";
            for (int j = x; j < i; ++j) arr[p] += s[j];
            x = i + 1;
            if (s[i+1] == ':') { x = i = i + 2; pre = p; }
        }
    }
}

string get(string s) {
    split(std::move(s)); string cur;
    for (int i = 1; i <= p; ++i) {
        for (int j = 1; j <= (4 - arr[i].size()); ++j) cur += '0';
        for (const auto c : arr[i]) cur += c;
        if (pre == i) for (int j = 1; j <= 8 - p; ++j) cur += "0000";
    }
    string res;
    for (int i = 1; i <= cur.length(); ++i) {
        res += cur[i-1];
        if (i < 32 && i % 4 == 0) res += ':';
    }
    return res;
}

int main() {
    fast;
    int n; cin >> n; string s;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        cout << get(s) << '\n';
    }
    return 0;
}