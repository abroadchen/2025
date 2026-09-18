//
// Created by Psy.C on 2026/9/18.
//
/**
v[0]：两种技能都不满足的书（普通书）。
v[1]：只满足 A 技能的书（vis = 1）。
v[2]：只满足 B 技能的书（vis = 2）。
v[3]：A、B 两种技能都满足的书（vis = 3）。
l[0..3] 记录每组数量，k 表示最终要求 A、B 各至少达到 k 个。

A / B：当前已选了多少本"只A"书 / "只B"书。
la / lb：当前已满足的 A 技能总数 / B 技能总数。
nr：当前已选了多少本"普通书"（v[0]）。
s：当前已选书的总价格。
fk：失败标志。
再买 x 本"额外填充"书，每次贪心地选当前最便宜且合法的一本。
每次选择一个候选：
选"只A书"（v[1]）的条件：还有剩余、价格更小、且当前 B 技能已满足（lb >= k）。
选"只B书"（v[2]）的条件：还有剩余、价格更小、且当前 A 技能已满足（la >= k）。
选"普通书"（v[0]）的条件：还有剩余、价格更小、且 A、B 都已满足（la >= k && lb >= k）。
即：在 A、B 都已经满足 k 的前提下，再买最多的书来填充到 m 本，总是挑最便宜的，且尽量先别破坏已满足的状态。若没有可选的（id == -1），置失败标志 fk
读 n 本书价格 a[i]。某几本拥有 A 技能（vis += 1），某几本拥有 B 技能（vis += 2）。
于是 vis[i] 可能是 0（无技能）、1（仅A）、2（仅B）、3（AB都有）。
按 vis[i] 把每本归入对应组 v[vis[i]]，组内按价格升序排序
可行性判断：若 m < k（书不够 k 本）直接 -1。否则若 AB 双技能书 l[3] < k，还要检查：用 A 书、B 书、AB 书能否凑满 k 个 A 和 k 个 B，且总数不超过 m；不满足则 -1。
初始选法：先尽量选 AB 双技能书（v[3]，最划算，一本同时满足两个技能），取前 mn = min(l[3], m) 本。
la = lb = mn：AB 书同时+1 A 和 +1 B。
再补足：若 A 还差 k - l[3] 个，用"只A书"补；同理用"只B书"补 B。
最后用 get(m - mn - A - B) 把总数补到 m 本，此时得到初始可行解 ans = s
逐一减少 AB 书的使用数量（从 mn 递减到 1），尝试"少用 AB 书、改用其他组合"是否更便宜。
每次去掉一本 AB 书（la--, lb--, s -= v[3][i]），A、B 各少一个满足。
若 A、B 都跌破了 k（la<k && lb<k），则尝试：若还有"只A书""只B书""普通书"可用，就把一本普通书换成"只A书+只B书"（s -= v[0][nr--]，s += v[1][++A]，s += v[2][++B]，la++, lb++）来重新满足 A、B 各 k；否则 break。
否则（只有一边跌破），调用 get(1) 补一本。
每轮更新 ans = min(ans, s)（当前总价更小就更新）。
最终输出最小总价 ans
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


constexpr int N = 2e5+5, inf = 2e9;
int A, B, la, lb, v[4][N], l[4], k, nr, fk;
ll s;
void get(int x) {
    while (x--) {
        int mn = inf, id = -1;
        if (A < l[1] && v[1][A+1] < mn && lb >= k) mn = v[1][A+1], id = 1;
        if (B < l[2] && v[2][B+1] < mn && la >= k) mn = v[2][B+1], id = 2;
        if (nr < l[0] && v[0][nr+1] < mn && la >= k && lb >= k) mn = v[0][nr+1], id = 3;
        if (id == -1) { fk = 1; return; }
        if (id == 1) A++, la++;
        if (id == 2) B++, lb++;
        if (id == 3) nr++;
        s += mn;
    }
}

int n, m, a[N], t, vis[N], mn;
ll ans;
int main() {
    n = rd(), m = rd(), k = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    t = rd();
    for (int i = 1; i <= t; ++i) vis[rd()]++;
    t = rd();
    for (int i = 1; i <= t; ++i) vis[rd()] += 2;
    for (int i = 1; i <= n; ++i)
        v[vis[i]][++l[vis[i]]] = a[i];
    for (int i = 0; i < 4; ++i) sort(v[i]+1, v[i]+l[i]+1);
    if (m < k || (l[3] < k && ((k-l[3])*2+l[3] > m || k - l[3] > l[1] ||
        k - l[3] > l[2]))) { puts("-1"); return 0; }
    mn = min(l[3], m);
    for (int i = 1; i <= mn; ++i) s += v[3][i];
    la = lb = mn;
    while (A < k - l[3]) s += v[1][++A], la++;
    while (B < k - l[3]) s += v[2][++B], lb++;
    get(m-mn-A-B); ans = s;
    for (int i = mn; i >= 1; --i) {
        la--; lb--; s -= v[3][i];
        if (la < k && lb < k) {
            if (A < l[1] && B < l[2] && nr > 0)
                s -= v[0][nr--], s += v[1][++A], s += v[2][++B], la++, lb++;
            else break;
        } else get(1);
        if (fk || la < k || lb < k) break;
        ans = min(ans, s);
    }
    cout << ans << '\n';
    return 0;
}