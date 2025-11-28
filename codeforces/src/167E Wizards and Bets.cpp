//
// Created by Psy.C on 2025/11/28.
//
/*
*n: 节点数，m: 边数，mod: 模数
in[N], out[N]: 入度和出度数组
S[N], T[N]: 源点和汇点数组，cs, ct: 计数器
q[N]: 队列，t, s: 队列指针
id[N], top[N]: 节点映射数组，cur: 计数器
f[N][N], a[N][N]: 矩阵数组
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

typedef long long ll;
constexpr int N = 605, M = 1e5+5;
int n, m, mod,
in[N], out[N], S[N], T[N], cs, ct,
q[N], t, s, id[N], top[N], cur,
f[N][N], a[N][N];

int to[M], nxt[M], head[N], d[N], cnt;
void add(const int u, const int v) {//添加从u到v的有向边，并更新入度
    to[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
    ++d[v];
}
//矩阵求逆和行列式计算中的线性变换
void func(int u, int v, int& ii, int& ik, int &ki, int& kk, int& sgn) {
    ii = 1, ik = 0, ki = 0, kk = 1, sgn = 1;
    while (v) {
        (ii -= u / v * ki) %= mod;
        (ik -= u / v * kk) %= mod;
        u -= u / v * v;
        swap(u, v); swap(ii, ki); swap(ik, kk);
        sgn = -sgn;
    }
}
//通过行变换将矩阵化为上三角矩阵，然后计算对角线元素的乘积
int gauss(const int x) {
    int ans = 1, ii, ik, ki, kk, sgn;
    rep(i,x) {
        for (int k = i + 1; k <= x; ++k) if (a[k][i]) {
            func(a[i][i], a[k][i], ii, ik, ki, kk, sgn);
            ans *= sgn;
            for (int j = i; j <= x; ++j) {
                const int u = static_cast<int>((1ll * a[i][j] * ii + 1ll * a[k][j] * ik) % mod),
                v = static_cast<int>((1ll * a[i][j] * ki + 1ll * a[k][j] * kk) % mod);
                a[i][j] = u, a[k][j] = v;
            }
        }
        ans = static_cast<int>(1ll * ans * a[i][i] % mod);
    }
    return ans;
}

int main() {
    fast;
    cin >> n >> m >> mod;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        add(x, y);
        ++in[y], ++out[x];
    }
    rep(i,n) {//找出所有源点（入度为0）和汇点（出度为0）
        if (!in[i]) S[++cs] = i;
        if (!out[i]) T[++ct] = i;
    }
    //按拓扑序重新编号节点
    rep(i,n) if (!d[i]) q[t++] = i;
    while (s < t) {
        const int u = q[s++]; id[(top[u] = ++cur)] = u;
        for (int i = head[u]; i; i = nxt[i]) if (--d[to[i]] == 0) {
            q[t++] = to[i];
        }
    }
    //动态规划计算从每个源点到每个节点的路径数
    for (int i = 1, u; i <= n; ++i) {
        u = id[i]; f[u][u] = 1;
        for (int j = i, v; j <= n; ++j) {
            v = id[j];
            for (int k = head[v]; k; k = nxt[k])
                (f[u][to[k]] += f[u][v]) %= mod;//从节点u到节点to[k]的路径数
        }
    }
    const int ans = cs;
    rep(i,ans) rep(j,ans) a[i][j] = f[S[i]][T[j]];//构建源点到汇点的路径数矩阵
    cout << (gauss(ans) + mod) % mod << '\n';//计算矩阵行列式
    return 0;
}