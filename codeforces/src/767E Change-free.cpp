//
// Created by Psy.C on 2026/9/7.
//
/**
ci：原价格。
wi：权重/手续费单价。
cmp：(100 - ci%100) * wi，即"把这件的零头补齐到 100 所需的代价"。
pos：下标。
重载 < 让 cm 大的排在优先队列堆顶（a.cmp > b.cmp → 小顶堆按 cmp 反过来，实际是"代价最大者优先"）。
全局节点数组 a[N] 和临时 now

u[i]：标记第 i 件是否被"强制凑整"（即动用了一次性补齐）。
ans[i][0] / ans[i][1]：分别记录最终输出的"整百部分 / 零钱部分"。
每轮读入 n、m 后重置 res、u，并清空优先队列 q
读入 n 个 ci（价格）和 n 个 wi（权重）

a[i].cmp = (100 - a[i].ci%100) * a[i].wi;
计算把第 i 件的零钱部分（ci%100）补齐成 100 的成本，即"若强制这单凑整需要付出的代价"。

ans[i][0] = a[i].ci/100; ans[i][1] = a[i].ci%100;
先用"不凑整"的方式初始化输出：整百数 + 零钱。

if (ans[i][1] != 0) q.push(a[i]); else u[i] = 1;

若这单有零钱（ci%100 != 0），把它放进优先队列候选；
若这单已经是整百（余数 0），直接标记 u[i]=1（无需凑整）。
if (m >= a[i].ci%100)
若手头零钱 m 够付这单的零钱 → 直接付，m -= a[i].ci%100。

else（零钱不够）
取出队列中费用代价（cmp）最大的那个候选（堆顶），把它的成本累加进 res；
m -= ans[i][1]：先扣掉当前这单需要的零钱；
m += 100：因为强制凑整产生了一张 100，让零钱池 +100；
弹出已被"强制凑整"的元素。
这等价于：当 m 不够时，翻出之前某张"最贵/最划算被凑整"的账单，换取 +100 的解围。
处理完后，优先队列里剩余的元素再不入答案，直接统一标记为 u=1（表示这些最终也视为已处理/凑整状态）。这一句把所有没被实际选中但仍在队列中的候选清空并标记，统一成"整百"输出形态
第一行输出最小总代价 res。
对每个 i：
若 u[i]==0（没被强制凑整、也没被标记成整百），则把它输出为 (ci/100 + 1, 0)——即进一位整百：ans[i][0]++（整百 +1）且零钱清零。
否则按原样输出 (ci/100, ci%100)（保留零钱形式
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+8e3;
struct node {
    ll ci, wi, cmp, pos;
    friend bool operator<(node a, node b) {
        return a.cmp > b.cmp;
    }
} a[N], now;

ll n, m, u[N], ans[N][2];
int main() {
    fast;
    while (cin >> n >> m) {
        ll res = 0;
        memset(u, 0, sizeof(u));
        priority_queue<node> q;
        for (ll i = 0; i < n; ++i) cin >> a[i].ci;
        for (ll i = 0; i < n; ++i) cin >> a[i].wi;
        for (ll i = 0; i < n; ++i) {
            a[i].cmp = (100 - (a[i].ci%100))*a[i].wi; a[i].pos = i;
            ans[i][0] = a[i].ci/100; ans[i][1] = a[i].ci%100;
            if (ans[i][1] != 0) q.push(a[i]); else u[i] = 1;
            if (m >= a[i].ci%100) m -= a[i].ci%100;
            else {
                now = q.top(); res += now.cmp; m -= ans[i][1];
                m += 100; q.pop();
            }
        }
        while (!q.empty()) { u[q.top().pos] = 1; q.pop(); }
        cout << res << '\n';
        for (ll i = 0; i < n; ++i) {
            if (u[i] == 0) ans[i][0]++, ans[i][1] = 0;
            cout << ans[i][0] << ' ' << ans[i][1] << '\n';
        }
    }
    return 0;
}