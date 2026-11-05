//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
标准并查集，merge 时若两个不同集合合并，则连通块数 sum--
标准快速幂，用于 2^sum 等幂运算（取模 mod）。
读入 n 个点、m 条边、分组数 k。
初始 fa[i]=i，每个点自成一个连通块。
边权 = 两端点 c 的异或。
按边权 c 升序排序。
外层：分段处理，每段内所有边边权 XOR 值相同（a[i].c 相等）。
cnt++：统计出现的不同 XOR 值的种类数。
对内层这段边建立并查集，统计连通块数 sum，然后累加 2^sum 到 ans。
关键：处理后立即回滚并查集（fa 重置为自身），因为下一段要用全新的并查集，互不干扰。这说明每一段是独立计入个数的
ksm(2,k)：所有可能的 XOR 权值数（2^k 种）。
cnt：实际在边中出现过的 XOR 种类数。
ksm(2,k) - cnt：没出现在任何一条边上的 XOR 值的种类数。
这些未出现的 XOR 值对应的图是"完全无连边"的，故每个贡献 2^n（n 个点各自独立）。
累加到 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define int long long
using namespace std;

constexpr int N = 5e5+5, mod = 1e9+7;

struct node {
    int u, v, c;
    bool operator<(const node& o) const { return c < o.c; }
} a[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int sum;
void merge(int u, int v) {
    int x = find(u), y = find(v);
    if (x != y) fa[x] = y, sum--;
}
int ksm(int a, int b) {
    int r = 1;
    while (b) {
        if (b&1) r=r*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return r;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, k, c[N], cnt, ans;
signed main() {
    fast;
    n = rd(), m = rd(), k = rd();
    rep(i,n) c[i] = rd(), fa[i] = i;
    rep(i,m) {
        int u = rd(), v = rd();
        a[i] = {u, v, c[u]^c[v]};
    }
    sort(a+1, a+1+m);
    for (int i = 1, j = 1; i <= m; ) {
        cnt++; sum = n;
        for (; j <= m; j++) {
            if (a[i].c != a[j].c) break;
            merge(a[j].u, a[j].v);
        }
        ans = (ans + ksm(2,sum))%mod;
        for (; i < j; i++) {
            fa[a[i].u] = a[i].u;
            fa[a[i].v] = a[i].v;
        }
    }
    ans += (ksm(2,k)-cnt)*ksm(2,n);
    cout << (ans%mod+mod)%mod << '\n';
    return 0;
}