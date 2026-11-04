//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
读入两堆各 n 张牌，升序排序。
排序后，a[n-1] 和 b[n-1] 分别是两堆的最大牌
ac, bc：指向两堆当前最大牌的下标（从堆顶往小走）。
sa, sb：两家的得分累加
比较 a 堆顶与 b 堆顶：
A 走：若 a 的当前最大 > b 的当前最大，A 取走这张得分；否则 A 不能得分，只能丢一张 b 的（即 bc--）。
B 走：若 b 的当前最大 > a 的当前最大，B 取走得 sb；否则 B 丢一张 a 的（ac--）。
A、B 交替决策，每次比较两堆当前最大牌，大的一方得分并取走，小的一方被迫弃掉，n 轮后输出两家分值差 sa - sb
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

int n, a[N], b[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    sort(a, a+n); sort(b, b+n);
    int ac = n-1, bc = n-1; ll sa = 0, sb = 0;
    rep(i,n) {
        if (a[ac] > b[bc]) { sa += a[ac]; ac--; } else bc--;
        if (b[bc] > a[ac]) { sb += b[bc]; bc--; } else ac--;
    }
    cout << sa - sb << '\n';
    return 0;
}