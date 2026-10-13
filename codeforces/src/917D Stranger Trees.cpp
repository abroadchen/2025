//
// Created by Psy.C on 2026/10/13.
//
/**
dp[x][j][t]：以 x 为根的子树中，选恰好 j 个点且 x 是否被选(t=0/1) 的方案数；
sz[x]：子树大小；
f：合并儿子时的临时数组
j+k-1 的项表示合并时“合并掉了一个点”的情形（典型的基环/去重技巧，具体含义取决于题意，常见场景是"选出的集合在合并儿子时要扣掉公共计数"）
pw 是在 init 里传入的 n（总节点数）为底
g[i] 由根节点 dp 值乘幂得到；dp[1][n-i][1] 表示整棵树选 n-i 个点且根被
这种 Σ (-1)^(j-i) * C[j][i] * g[j] 的形式正是二项式反演的标准结构，用来从"至少/至多…"的 g 反推出"恰好…"的 F选
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 105, mod = 1e9+7;

int to[N<<1], head[N], nxt[N<<1], cnt;
inline void adde(int x, int y) {
    to[++cnt] = y, nxt[cnt] = head[x], head[x] = cnt;
    to[++cnt] = x, nxt[cnt] = head[y], head[y] = cnt;
}
inline int add(int a, int b) { return a+b-(a+b>=mod ? mod : 0); }

int dp[N][N][2], sz[N], f[N][2];
void dfs(int x, int fa) {
    //初始化：只含 x 自己，选的 1 个点可以是 x 也可以不是 x
    dp[x][1][0] = dp[x][1][1] = 1, sz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y != fa) {
            dfs(y, x);//先递归算好儿子子树
            //卷积式合并：把儿子子树依次合并进来，枚举 x 中已选 j 个、儿子中已选 k 个
            rep(j,1,sz[x]) rep(k,1,sz[y]) {
                f[j+k][0]=(f[j+k][0]+1ll*dp[x][j][0]*dp[y][k][1])%mod;
                f[j+k][1]=(f[j+k][1]+1ll*dp[x][j][1]*dp[y][k][1])%mod;
                f[j+k-1][0]=(f[j+k-1][0]+1ll*dp[x][j][0]*dp[y][k][0])%mod;
                f[j+k-1][1]=(f[j+k-1][1]+1ll*dp[x][j][1]*dp[y][k][0]+
                    1ll*dp[x][j][0]*dp[y][k][1])%mod;
            }
            sz[x] += sz[y];
            //把临时结果写回 dp[x]，清空 f
            rep(j,1,sz[x]) rep(k,0,1) { dp[x][j][k] = f[j][k]; f[j][k] = 0; }
        }
    }
}

int C[N][N], pw[N];
inline void init(int n) {
    rep(i,0,n) {
        C[i][0] = 1;
        rep(j,1,i) C[i][j] = add(C[i-1][j-1], C[i-1][j]);
    }
    pw[0] = 1;
    rep(i,1,n) pw[i]=1ll*pw[i-1]*n%mod;//pw[i] = n^i
}

int g[N], F[N];
int main() {
    fast;
    int n, u, v; cin >> n;
    rep(i,1,n-1) { cin >> u >> v; adde(u, v); }
    dfs(1, 0); init(n);
    rep(i,0,n-2) g[i] = 1ll*dp[1][n-i][1]*pw[n-i-2]%mod;
    g[n-1] = 1;
    rep(i,0,n-1) {
        rep(j,i,n-1) {
            if ((j^i)&1) F[i]=(F[i]-1ll*C[j][i]*g[j])%mod;
            else F[i]=(F[i]+1ll*C[j][i]*g[j])%mod;
        }
        F[i] += F[i]<0 ? mod : 0;
        cout << F[i] << (i<n-1?' ':'\n');
    }
    return 0;
}