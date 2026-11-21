//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
constexpr int N = 1e5+5;   // 商品数上限 + 余量
ll n, m, a[N];             // a[i] = 商品 i 当前剩余库存
ll c[N];                   // c[i] = 商品 i 单价
ll t;                      // 临时变量：本次实际买到的数量
ll q1, q2;                 // 当前订单: q1=商品编号, q2=想要的数量
ll d[N];                   // d[i] = 第 i 个订单最终花费
priority_queue<pair<ll, ll>> q;   // (单价, 商品编号)，默认大顶堆
先读全部库存 a[]。
再读单价 c[]，把 (-单价, 编号) 压入堆。因为是大顶堆 + 负号 = 低价优先，堆顶就是最便宜的商品 i。
① t = min(q2, a[q1])：尽可能从顾客点名的 q1 商品里买，能买多少买多少（受库存 a[q1] 限制）。d[i] += t*c[q1] 计费，q2 -= t、a[q1] -= t 都扣掉。

② if (q2 > 0)：指定商品不够，走替代逻辑。循环从堆顶（最便宜）开始：

若该商品库存已空（a[...]==0），q.pop() 弹出，continue 找下一个更便宜的。
否则 t = min(q2, a[顶])，从它还够买的数量里 t 个，d[i] += t*c[顶]，库存和待买都扣。重复直到 q2 清零或堆空。
注意：堆里的商品即使用户点名的 q1 已经买过，也仍在堆里（先被 q1 分支买，之后替代循环也能再碰到它，再次购买）。这是题目策略允许的——替代阶段照旧按最便宜原则买。
③ if (q2 > 0) d[i] = 0：替代循环都结束，还欠 q2 > 0，说明全店库存都卖光了，买不到这个订单 → 把之前累计的 d[i] 清零（这单作废，不收费）
按 m 个订单顺序，每个占据一行，输出各订单花费 d[i]（若作废则为 0）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;
ll n, m, a[N], c[N], t, q1, q2, d[N];
priority_queue<pair<ll, ll>> q;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,n) { cin >> c[i]; q.emplace(-c[i],(ll)i); }
    rep(i,m) {
        cin >> q1 >> q2; t = min(q2,a[q1]);
        d[i] += t*c[q1]; q2 -= t; a[q1] -= t;
        if (q2 > 0) {
            while (!q.empty() && q2 > 0) {
                if (a[q.top().second] == 0) { q.pop(); continue; }
                t = min(q2,a[q.top().second]);
                d[i] += t*c[q.top().second];
                a[q.top().second] -= t; q2 -= t;
            }
        }
        if (q2 > 0) d[i] = 0;
    }
    rep(i,m) {
        cout << d[i];
        if (i != m) cout << '\n';
    }
    return 0;
}