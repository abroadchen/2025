//
// Created by Psy.C on 2026/10/5.
//
/**
把每个出现的 x 和 y 分别映射成点编号 1..tot，tot 是总节点数
每个节点自成一块，sz 记录块大小
把点 (x_i,y_i) 的两个端点在并查集里合并
find 带路径压缩
若两端点本来就在同一连通块，说明这条边让块形成环，置 h=1
否则合并，并传播“该块是否含环”的标记 h，同时累加块大小
对每个 根节点（i==fa[i]，即每个连通块）
含环：贡献
2
s
z
2
sz
不成环（树）‍：贡献
2
s
z
−
1
2
sz
各块方案数相乘即答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+10, mod = 1e9+7;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int h[N], sz[N];
void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) h[x] = 1;
    else {
        if (h[x] == 0 && h[y] == 1) h[x] = h[y];
        fa[y] = fa[x];
        sz[x] += sz[y];
    }
}

ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b&1) { res*=a; res%=mod; }
        a*=a; a%=mod;
        b>>=1;
    }
    return res;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int x[N], y[N], tot;
unordered_map<int, int> mp1, mp2;
int main() {
    fast;
    int n = rd();
    for (int i = 1; i <= n; ++i) {
        x[i] = rd(), y[i] = rd();
        if (!mp1[x[i]]) mp1[x[i]] = ++tot;
        if (!mp2[y[i]]) mp2[y[i]] = ++tot;
    }
    for (int i = 1; i <= tot; ++i) fa[i] = i, sz[i] = 1;
    for (int i = 1; i <= n; ++i) merge(mp1[x[i]], mp2[y[i]]);
    ll ans = 1;
    for (int i = 1; i <= tot; ++i)
        if (i == fa[i]) {
            if (h[i]) {
                ans *= ksm(2, sz[i])%mod; ans %= mod;
            } else {
                ans *= ((ksm(2, sz[i])-1)%mod+mod)%mod; ans %= mod;
            }
        }
    cout << ans;
    return 0;
}