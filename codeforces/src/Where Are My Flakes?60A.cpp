//
// Created by Psy.C on 2025/10/26.
//
/*
 *cin.ignore(): 忽略输入缓冲区中的剩余字符(通常是换行符)
 *
 *循环m次，每次处理一个约束条件
*创建字符串流ss，将输入行s放入其中
逐个提取单词，如果单词首字符是数字，则将其转换为整数存入k
这一步的目的是从输入行中提取数字参数
*如果字符串中包含"left"，说明是向左的约束，更新右边界r为min(r, k-1)
否则说明是向右的约束，更新左边界l为max(l, k+1)
这是在根据约束条件不断缩小可能的范围
 *
*如果左边界不大于右边界，说明存在有效范围，输出范围大小(r-l+1)
否则说明约束条件矛盾，输出-1
 *
 */
#include <sstream>
#include <iostream>
#include <ios>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin>>n>>m; cin.ignore();
    int l(1), r(n);
    while (m--) {
        string s; getline(cin, s);
        int k(0);
        stringstream ss(s);
        string w;
        while (ss >> w) { if (isdigit(w[0])) k = stoi(w); }
        if (s.find("left") != string::npos) r = min(r, k - 1);
        else l = max(l, k + 1);
    }

    if (l <= r) cout << r - l + 1 << endl;
    else cout << -1 << endl;
    return 0;
}