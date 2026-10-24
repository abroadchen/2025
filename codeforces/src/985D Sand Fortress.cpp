//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
n：方块总数，h：最高层允许高度
p 是方程 p(p+1)/2 ≤ n 的最大解，即能搭成完整三角形（1+2+...+p）时的最大 p（约等于 √(2n)）。
若 p ≤ h（即完整三角形高度不超限）：
若 n 恰好等于 p(p+1)/2（正好凑成完整三角形），塔高就是 p。
否则（n 比 p(p+1)/2 多了一点），高度为 p+1（多出的往最上层再加，高度+1）
当最高层必须为 h，且总高超过 h 时（p > h）：
n -= h*(h+1)/2;：先减掉最底部"阶梯上升"到 h 所需的方块数 1+2+...+h = h(h+1)/2。
x = -h + sqrt(h*h + n);：求解"从高度 h 继续升起的高度 x"，即第一个完整三角形（再升 x 层）能容纳的方块，结合剩余 n 推出 x（近似解）。
ans = h + 2*x;：塔高 = 底部 h 层 + 上升 x 层 + 对称下降 x 层（近似）。
若 n 还有剩余（n > x*x+2*h*x，即完整的"h→h+x 的菱形"装不满）：
再减掉已装的部分 x*x+2*h*x。
剩余部分 ≤ h+x，则只需再加 1 层（ans++）；
否则剩余更多，需再加 2 层（ans += 2）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, h, ans;
int main() {
    fast;
    cin >> n >> h;
    ll p = (-1+sqrt(1+8*n))/2;
    if (p <= h) {
        if (n == p*(p+1)/2) ans = p;
        else ans = p+1;
    } else {
        n -= h*(h+1)/2;
        ll x = -h+sqrt(h*h+n);
        ans = h+2*x;
        if (n > x*x+2*h*x) {
            n -= x*x+2*h*x;
            if (n <= h+x) ans++; else ans += 2;
        }
    }
    cout << ans;
    return 0;
}