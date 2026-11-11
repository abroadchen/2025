//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
用试除法分解 n，p 是 map，p[i] 是质因子 i 的指数。
num[idx] 存质因子，cnt[idx] 存对应指数
mx = 所有质因子指数中的最大值。完全平方数要求所有指数都是偶数，这里看最大指数需要"拉升"到 2 的幂级别
目标：把所有质因子指数统一处理，使最终 n 成为完全平方数（即所有指数为偶数时可开平方到底）。
o 判断所有指数是否全为偶数；全偶可整体开根（指数减半，op++）；否则需要一次"补偿乘"（f=1 标记）。
每次把指数向上取整 (cnt+1)/2，op++，逐步逼近
ans = 所有出现过（指数≥1）的质因子乘积，即"最小 n 的平方根框架"。
操作次数 = op + f（f 只有 0/1，标记是否额外补过一次
*/
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1001;

int n, num[N], cnt[N];
map<int, int> p;
int main() {
    fast;
    cin >> n;
    int t = n;
    for (int i = 2; i <= n; i++)
        while (t%i == 0) t /= i, p[i]++;
    int idx = 0;
    for (auto [fst, snd] : p) {
        ++idx;
        num[idx] = fst; cnt[idx] = snd;
    }
    int mx = -1;
    rep(i,idx) mx = max(mx, cnt[i]);
    int f = 0, op = 0;
    while (mx > 1) {
        bool o = 1;
        rep(i,idx) if (cnt[i]%2 == 1) o = 0;
        if (o) { rep(i,idx) cnt[i] /= 2; op++; mx /= 2; }
        else {
            if (!f) f = 1;
            rep(i,idx) cnt[i] = (cnt[i]+1)/2;
            mx = (mx+1)/2; op++;
        }
    }
    int ans = 1;
    for (const auto key: p | views::keys) ans *= key;
    cout << ans << ' ' << op+f;
    return 0;
}