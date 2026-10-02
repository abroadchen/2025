//
// Created by Psy.C on 2026/10/2.
//
/**
有 2n 个节点（1..2n）。
读入 n 对 (x, y)，每条边连接节点 x 和 y。
若是自环 x==y，给该点所在块打 c=1 标记。
并查集合并 x,y。
若 x,y 本来在不同块 → 合并，传递 c 标记和 sz 大小。
若 x,y 已在同一块（fx==fy）→ 说明这条边形成了"额外边"（环），给该块打 cc=1。
统计阶段：对每个根节点（find(i)==i）且不含自环标记 !c[i] 的块：

若块内有"环/额外边" cc[i] → 乘 2；
否则（普通树状块）→ 乘 sz[i]（块内节点数）。
答案 ans 对 mod=1e9+7 取模
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+10, mod = 1e9+7;

int f[N];
inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int sz[N];
bool c[N], cc[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= 2*n; ++i) { f[i] = i; sz[i] = 1; }
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        if (x == y) c[x] = 1;
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            f[fx] = fy; c[fy] |= c[fx];
            sz[fy] += sz[fx]; sz[fx] = 0;
        } else cc[fx] = 1;
    }
    ll ans = 1;
    for (int i = 1; i <= 2*n; ++i) {
        if (find(i) == i && !c[i]) {
            if (cc[i]) ans = ans*2%mod;
            else ans = ans*sz[i]%mod;
        }
    }
    cout << ans << '\n';
    return 0;
}