//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
传入字符串 a，判断它是否是回文串。
循环 i 从 0 到 a.size()/2（只比较前半段）。
a[i] 与对称位置 a[size-1-i] 比较；只要有一处不等就返回 false（非回文）。
全部相等则返回 true（是回文）
读入字符串 s。
双重循环枚举所有子串：起点 i，终点 j（j>i，注意是 i+1 起，长度为 j-i+1）。
用 s.substr(i, j-i+1) 取出子串，ok() 判断是否回文。
若不是回文（ok()==false），记录其长度 x=j-i+1，用 max 更新 mx。
最后输出 mx，即最长的非回文子串长度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<i##_end_; i++)
using namespace std;

bool ok(const string &a) {
    rep(i,0,a.size()/2)
        if (a[i] != a[a.size()-1-i])
            return false;
    return true;
}


string s;
int mx;
int main() {
    fast;
    cin >> s;
    rep(i,0,s.size()) rep(j,i+1,s.size())
        if (ok(s.substr(i,j-i+1)) == false) {
            int x = j-i+1;
            mx = max(mx, x);
        }
    cout << mx;
    return 0;
}