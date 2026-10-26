//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
vt1：第一个人的 n 组数对；vt2：第二个人的 m 组数对。每对数先 min/max 归一化（保证 first ≤ second）。
遍历第一个人每组 (a,b)：与第二个人所有组 (c,d) 比较：
相同数对跳过。
数对间任一相等数字（a==c / b==c / a==d / b==d）视为"共享数字"出现一次，f1[该数]++，并标记 f[0] 或 f[1]。
若该组两个数 (a,b) 各自都与第二个人有交集（f[0]&&f[1]）→ 无法确定唯一数字，置 tag=1。
再从第二个人角度对称跑一遍（逻辑同前，f2 数组实际未用）。
统计 f1[] 中非零（出现过的共享数字）个数：
若 tag==1 → 说明存在一组两个数都是共享数字，无法唯一确定 → 输出 -1。
否则共享数字 恰有 1 个 → 输出该数字 ans。
否则（多个共享数字）→ 输出 0。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i, n) for(i=1;i<=n;i++)
#define ii pair<int,int>
using namespace std;

vector<ii> v1, v2;
int n, m, i, x, y;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) {
        cin >> x >> y;
        v1.emplace_back(min(x,y), max(x,y));
    }
    rep(i,m) {
        cin >> x >> y;
        v2.emplace_back(min(x,y), max(x,y));
    }
    int f1[10]{}, tag = 0;
    for (auto &it : v1) {
        int a = it.first, b = it.second, f[2]{0,0};
        for (auto &it2 : v2) {
            int c = it2.first, d = it2.second;
            if (a == c && b == d) continue;
            if (a == c && b != d) { f1[a]++; f[0] = 1; }
            else if (b == c) { f1[b]++; f[1] = 1; }
            else if (a == d) { f1[a]++; f[0] = 1; }
            else if (b == d) { f1[b]++; f[1] = 1; }
        }
        if (f[0] && f[1]) tag = 1;
    }
    int f2[10]{};
    for (auto &it : v2) {
        int a = it.first, b = it.second, f[2]{0,0};
        for (auto &it2 : v1) {
            int c = it2.first, d = it2.second;
            if (a == c && b == d) continue;
            if (a == c && b != d) { f2[a]++; f[0] = 1; }
            else if (b == c) { f2[b]++; f[1] = 1; }
            else if (a == d) { f2[a]++; f[0] = 1; }
            else if (b == d) { f2[b]++; f[1] = 1; }
        }
        if (f[0] && f[1]) tag = 1;
    }
    int num = 0, ans = 0;
    rep(i,9) if (f1[i]) { num++; ans = i; }
    if (tag) cout << "-1\n";
    else {
        if (num == 1) cout << ans << '\n';
        else cout << "0\n";
    }
    return 0;
}