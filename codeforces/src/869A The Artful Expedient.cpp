//
// Created by Psy.C on 2026/10/5.
//
/**
先把 x 全部读入，再读入 y，并把每个数都加入 mp 中计数，从而 mp 记录了全部 2n 个数的出现情况
枚举所有 n×n 个有序对 (i,j)，对每个对计算 x[i]^y[j]；
用 mp.contains(x)（C++20 的 map 成员函数，等价于 mp.find(x)!=mp.end()）判断该异或结果是否属于给出的 2n 个数【码translate】；
属于则 cnt++
计数为偶数输出 Karen，否则输出 Koyomi
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e3+5;

int n1[N], n2[N];
map<int, int> mp;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) { cin >> n1[i]; mp[n1[i]]++; }
    for (int i = 0; i < n; ++i) { cin >> n2[i]; mp[n2[i]]++; }
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int x = n1[i]^n2[j];
            if (mp.contains(x)) cnt++;
        }
    if (cnt%2 == 0) cout << "Karen\n"; else cout << "Koyomi\n";
    return 0;
}