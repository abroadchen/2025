//
// Created by Psy.C on 2026/9/17.
//
/**
每个元素有 a、b 两个属性以及原编号 id。
cmp：按 a 值从大到小排序
读入 n 个元素的两组数 a 和 b，记录原始编号 id。
按 a 降序排序
输出选取的元素个数：(n>>1)+1，即 ⌈n/2⌉（向上取整的一半）‍。
t[1].id 必选：按 a 降序排好后的第一个元素（a 值最大者）强制选取。
然后从 i = 2 开始，每两步取一对 (t[i], t[i+1])：
若 t[i].b >= t[i+1].b（或 i 是最后一个元素），选 t[i]；
否则选 t[i+1]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
struct node { int a, b, id; } t[N];
inline bool cmp(const node& a, const node& b) {
    return a.a > b.a;
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> t[i].a;
    for (int i = 1; i <= n; ++i) { cin >> t[i].b; t[i].id = i; }
    sort(t+1, t+1+n, cmp);
    cout << (n>>1)+1 << '\n' << t[1].id << ' ';
    for (int i = 2; i <= n; i += 2) {
        if (t[i].b >= t[i+1].b || i == n)
            cout << t[i].id << ' ';
        else cout << t[i+1].id << ' ';
    }
    return 0;
}