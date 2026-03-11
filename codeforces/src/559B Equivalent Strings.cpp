//
// Created by Psy.C on 2026/3/11.
//
/**
基本情况1: 如果两个字符串相等，返回1（可以变换）
基本情况2: 如果字符串长度为奇数，返回0（无法分割）
将字符串a和b都分成两半
a1, a2: 字符串a的前半部分和后半部分
b1, b2: 字符串b的前半部分和后半部分
情况1: a的前半部分可以变换为b的后半部分，且a的后半部分可以变换为b的前半部分
情况2: a的前半部分可以变换为b的前半部分，且a的后半部分可以变换为b的后半部分
任一情况成立即可

设字符串长度为n，时间复杂度为 O(n^log₂3) ≈ O(n^1.585)
每层递归分支数为2，深度为log n，每层需要O(n)时间处理字符串
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int dfs(string a, string b) {
    if (a == b) return 1;
    if (a.length()%2) return 0;
    int n = a.length();
    string a1 = a.substr(0, n/2), a2 = a.substr(n/2, n/2),
    b1 = b.substr(0, n/2), b2 = b.substr(n/2, n/2);
    return (dfs(a1, b2) && dfs(a2, b1)) ||
        (dfs(a1, b1) && dfs(a2, b2));
}

string a, b;
int main() {
    fast;
    cin >> a >> b;
    cout << (dfs(a, b) ? "YES" : "NO") << '\n';
    return 0;
}