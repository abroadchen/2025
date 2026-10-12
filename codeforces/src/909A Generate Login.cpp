//
// Created by Psy.C on 2026/10/11.
//
/**
str 初始化为一个很长的一串 z（用于初始"无穷大"比较基准）。
读入两个字符串 s1、s2
rep(i, s1.size()) 中 i 从 0 到 s1.size()-1。
s1.substr(0, i+1) 取 s1 的前 i+1 个字符（即长度 ≥ 1 的前缀）。
同理 s2.substr(0, j+1) 取 s2 的前缀。
两者直接拼接 s1前缀 + s2前缀。
str = min(str, 候选串)：string 类型直接用 < 比较字典序，min 取较小者，即不断保留字典序最小的拼接结果。
因为 i、j 从 0 开始且 substr 取 i+1 个字符，所以每个前缀至少长度为 1（不会出现空串）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

string s1, s2, str = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
int main() {
    fast;
    cin >> s1 >> s2;
    rep(i,s1.size()) rep(j,s2.size()) {
        str = min(str, s1.substr(0,i+1)+s2.substr(0,j+1));
    }
    cout << str;
    return 0;
}