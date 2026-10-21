//
// Created by Psy.C on 2026/10/21.
//
/**
每个节点有三个属性：h（高度）、v（某种值，如体积/速度）、d（数量/重量/需求）
n：节点数；m：分组数（按 h 分组后）。
V[m]：第 m 组里存 (v, d) 对。
rt[m]：第 m 组里所有 d 的和（组内总 d）
前提：tr 已按 h 排序（见 in()）。
遍历每个节点：若当前节点的 h 与上一个分组基准 tr[now].h 相同，则加入同一组（V[m]）；否则开启新组（now=i, m++，加入 V[新m]）。
每次加入都累加该组总 d：rt[m] += d。
结果：相邻相同 h 的节点归为一组，m 为组数
读入 n 及每个节点的 h,v,d；tot 累加所有 d。
排序：先按 h 升序，h 相同按 v 升序。
排序后调用 init() 分组
len 取第一组大小。
检查每一组大小是否都等于 len，若某组大小不同直接返回 1（不可行）
对每一列 i：第 1 组的 (v, d) 作为基准。
对组 j=2..m：
检查第 j 组该列的 v 是否等于第 1 组该列的 v，不同则返回 1。
检查比例 d/rt 是否相等：k/rt[1] == x/rt[j]（用 long double 比较，避免浮点精度/整数误差）。若不等返回 1
对每个组 i 的每个元素 j：
g = rt[i] / gcd(rt[i], d)：把 d 约分后的分母（约去与组总 d 的公因数）。
z = lcm(z, g)（z/p*g 是求最小公倍数，p=gcd(z,g)）。
若 z 超过上限 mx 则返回 1。
z 最终是所有分数分母的最小公倍数（约束候选倍数须被 z 整除）。
返回 0 表示分组与比例约束总体可行
solve(ht, kd)：若候选高度 ht 能被 z 整除则计数+1（kd 参数实际未被使用）
输入后：mx = gcd(rt[1], rt[2], ..., rt[m])（各组总 d 的最大公约数）。
调用 func()，若不可行输出 0 并结束。
枚举 mx 的所有因子 i（成对枚举：i 和 mx/i）：
对每个因子调用 solve(i, tot/i) 与 solve(mx/i, tot/(mx/i))。
i*i==mx 时防重复（break 前只求一次 i）。
ans 统计满足 因子 % z == 0 的个数并输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
#define ld long double
using namespace std;

constexpr int N = 2e5+5e3;

struct node { ll h, v, d; } tr[N];

int n, m;
vector<pll> V[N];
ll rt[N];
void init() {
    for (int i = 1, now = 0; i <= n; i++) {
        if (tr[i].h == tr[now].h) {
            V[m].emplace_back(tr[i].v, tr[i].d);
            rt[m] += tr[i].d;
        } else {
            now = i; m++;
            V[m].emplace_back(tr[i].v, tr[i].d);
            rt[m] += tr[i].d;
        }
    }
}

ll tot;
void in() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> tr[i].h >> tr[i].v >> tr[i].d;
        tot += tr[i].d;
    }
    sort(tr+1, tr+n+1, [](const node &a, const node &b) {
        return a.h  == b.h ? a.v < b.v : a.h < b.h;
    });
    init();
}

ll z(1), mx;
int func() {
    int len = V[1].size();
    for (int i = 2; i <= m; i++) if (V[i].size() != len) return 1;
    for (int i = 0; i < len; i++) {
        ll k = V[1][i].second;
        for (int j = 2; j <= m; j++) {
            ll x = V[j][i].second;
            if (V[j][i].first != V[1][i].first) return 1;
            if ((ld)k/(ld)rt[1] != (ld)x/(ld)rt[j]) return 1;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < V[i].size(); j++) {
            ll g = __gcd(rt[i], V[i][j].second); g = rt[i]/g;
            ll p = __gcd(z, g); z = z/p*g;
            if (z > mx) return 1;
        }
    }
    return 0;
}

ll ans;
void solve(ll ht, ll kd) { if (ht%z == 0) ans++; }


int main() {
    fast; in();
    mx = rt[1];
    for (int i = 2; i <= m; i++) mx = __gcd(mx, rt[i]);
    if (func()) { cout << "0\n"; return 0; }
    for (ll i = 1; i*i <= mx; i++) {
        if (mx%i != 0) continue;
        solve(i, tot/i);
        if (i*i == mx) break;
        solve(mx/i, tot/(mx/i));
    }
    cout << ans;
    return 0;
}