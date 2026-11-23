//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
试除到 x^(1/2)分解质因数，p[i].num 存质因子、p[i].tot 存其指数。
最后残留的 x>1 是大于 b^(1/2)的质因子，单独加入
mul 依次等于
p^1, p^2, p^3,…，now += n/mul 累加各项。
循环条件 n/mul >= p[i].num 保证下一项（再乘一次 p）仍非零。
把
b 分解质因数，用勒让德公式算每个质因子在
n! 里的指数，再各自扣除
b 里需要的指数取整、整体取最小
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e4+10;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct node { ll num, tot; } p[N];

ll cnt;
void get(ll x) {
    for (ll i = 2; i*i <= x; i++) {
        while (x%i == 0) {
            x /= i;
            if (p[cnt].num == i) p[cnt].tot++;
            else p[++cnt].num = i, p[cnt].tot = 1;
        }
    }
    if (x > 1) {
        if (p[cnt].num == x) p[cnt].tot++;
        else p[++cnt].num = x, p[cnt].tot = 1;
    }
}

ll n, b;
int main() {
    fast;
    cin >> n >> b; get(b);
    ll ans = inf;
    for (int i = 1; i <= cnt; i++) {
        ll mul = 1, now = 0;
        while (n/mul >= p[i].num) {
            mul *= p[i].num;
            now += n/mul;
        }
        ans = min(ans, now/p[i].tot);
    }
    cout << ans << '\n';
    return 0;
}