//
// Created by Psy.C on 2026/3/7.
//
/**
d[0][u]：以u为根的子树中，包含u的独立集数量
遍历u的所有儿子v
res *= d[0][v] + 1：对于每个子树，可以选择包含v的独立集（d[0][v]种）或不选择v（1种）
d[0][u] = res：保存结果

tot：记录有多少个(d[0][v]+1) ≡ 0 (mod mod)
res：除零因子外的所有(d[0][v]+1)的乘积
d[1][v]：表示不包括v的子树部分的独立集数量
如果存在多个零因子：d[1][v] = 0
如果只有一个零因子且v就是那个因子：d[1][v] = 其他因子的乘积
否则：d[1][v] = d[0][u] / (d[0][v]+1)（使用模逆元）
d[1][v] *= (d[1][u] + 1)：乘上父亲方向的贡献
递归处理子树

第一次DFS：计算子树内部的独立集数量
第二次DFS：计算外部（兄弟子树+祖先）的独立集数量
d[0][i]：包含i的子树内部独立集数量
(d[1][i]+1)：外部独立集数量（+1表示外部部分可以为空）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, mod = 1e9+7;
struct node { int v, nxt; } e[N<<1];
int cnt, head[N];
void add(int u, int v) {
    e[cnt] = {v, head[u]}, head[u] = cnt++;
}

ll ksm(ll a) {//求模逆元
    ll res = 1;
    int n = mod - 2;
    while (n) {
        if (n&1) { res *= a; res %= mod; }
        a *= a; a %= mod;
        n >>= 1;
    }
    return res;
}

ll d[2][N];
void dfs(int u, int fa) {
    ll res = 1;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        dfs(v, u);
        res *= d[0][v] + 1; res %= mod;
    }
    d[0][u] = res;
}

void dfs2(int u, int fa) {
    int tot = 0; ll res = 1;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        if ((d[0][v]+1)%mod == 0) ++tot;
        else { res *= d[0][v] + 1; res %= mod; }
    }
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        if (tot) {
            if ((d[0][v]+1)%mod == 0 && tot == 1) d[1][v] = res;
            else d[1][v] = 0;
        } else {
            d[1][v] = d[0][u]*ksm((d[0][v]+1)%mod);
            d[1][v] %= mod;
        }
        d[1][v] *= d[1][u] + 1; d[1][v] %= mod;
        dfs2(v, u);
    }
}

int n;
int main() {
    fast;
    memset(head, -1, sizeof(head));
    cin >> n;
    for (int i = 2, a; i <= n; ++i) {
        cin >> a; add(a, i); add(i, a);
    }
    dfs(1, 1); dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
        cout << d[0][i]*(d[1][i]+1)%mod << ' ';
    return 0;
}