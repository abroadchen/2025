//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
dx = 1：x 方向（行）的当前步长。
dy = 1：y 方向（列）的当前步长。
a = 1, b = 1：当前区间的下界（x 的最小可能值、y 的最小可能值）。
语义：当前认为答案格子的 x 坐标在 [a, a+dx-1] 区间内，y 坐标在 [b, b+dy-1] 区间内。每次询问该区间的右上角
当前 x 的候选区间下界为 a，步长 dx，所以 x 候选区间理论上到 a+dx-1。
用 min(n, a+dx-1) 把它裁剪到不超过 n（边界保护，因为网格只有 n×n）。
同理 y。
于是每次询问当前候选区间的右上角 (x, y)
输出询问点，等待系统返回 ret
ret == 1：答案在 x 更大的那一侧（行方向继续向右/向上）。
把 x 下界提升：a = x+1，即答案 x 坐标比 x 大，所以新的下界从 x+1 开始。
步长翻倍 dx *= 2：倍增跳，加快逼近
ret == 2：答案在 y 更大的那一侧（列方向继续向上）。
y 下界提升：b = y+1。
步长翻倍 dy *= 2
ret == 3：答案不是在这个方向，即当前跳过头了，需要后退。
dx = max(1, dx/2)、dy = max(1, dy/2)：两个方向步长都减半（但最小为 1），因为跳过头了，回退一半步长相当于"精细搜索"
ret == 0：找到了答案格子，退出循环
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n;
int main() {
    fast;
    cin >> n;
    ll dx = 1, dy = 1, a = 1, b = 1;
    while (true) {
        ll x = min(n,a+dx-1), y = min(n, b+dy-1);
        cout << x << ' ' << y << endl;
        int ret; cin >> ret;
        if (ret == 0) break;
        if (ret == 1) a = x+1, dx *= 2;
        if (ret == 2) b = y+1, dy *= 2;
        if (ret == 3) dx = max(1ll, dx/2), dy = max(1ll, dy/2);
    }
    return 0;
}