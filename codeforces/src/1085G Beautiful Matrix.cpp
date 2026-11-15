//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
c[0] 与 c[1] 是两棵大小 n 的 BIT，q=false 用第 0 棵，q=true 用第 1 棵。
add(x,y,q)：在 BIT q 的位置 x 上加 y（用于单点增量）；query(x,q)：求 BIT q 的 [1,x] 前缀和。
此处 BIT 用于维护"某值是否已出现 / 出现的次数"，实现 O(log n) 的序数统计
标准二分快速幂，用于计算 base^exp % mod——后面用于把某部分的乘方贡献加入答案
fac[i] = i! 的模值
dp[i][j] 的转移分三种情况：

j=0：dp[i][0] = dp[i-1][0] * i——即空位数量积。

i==j（全保留）：dp[i][i]，i=1 时无解取 0；i>1 用 (i-1)*(dp[i-1][i-1]+dp[i-2][i-2])。

一般情形 0<j<i：

dp[i][j] = j*dp[i-1][j-1] + (i-j)*dp[i-1][j]
这是一个排列组合的经典递推（类似"将 n 个元素放入 n 个位置使其有恰好 j 个位置固定"的错排加变体，或"装错信封/更列"计数）。后面 dp[n][n] 专门用于乘方底数。

看起来 dp[i][j] 表示某种"长度为 i 的排列中恰好有 j 个固定位"的计数，dp[n][n] 是全固定情况的总方案数。
对第一行每个元素 a[1][i]，统计「比它小且尚未出现」的个数：a[1][i]-1 - query(a[1][i],1)（即小于该值且没被选过的更小值数量）。
乘上 fac[n-i] 作为剩余排列数，累加到 res，再把它标记进 BIT（add(...,1,1) 即第 1 棵用于"首行使用"）。
这其实在做第一行在全排列中的字典序编号(rank)，类似"康托展开"加速版
第一行的贡献 rank 再乘上 dp[n][n]^(n-1)。这说明其余 n-1 行各自独立的方案数为 dp[n][n]，共 n-1 行，所以总体乘 dp[n][n]^(n-1)
每处理新行 i，先重置 c、vis，并把第 0 棵 BIT 全部位置置 1（代表"尚未在本行中被放置的值"）。k 记录"当前仍空闲（未用）的值个数"，初始 n
对上一行(第 i-1 行)的位置 j 的值 a[i-1][j]：如果它在本行还没被用（!vis[1][...]），说明这个值要被强制匹配到本行的这一列（因为题目要求同一列上下行值一致或某种匹配），于是：可用数 k 减 1，并在 BIT0 中扣除该值（该值不再可用于本行其他位置）
用前面查询 a[i][j]-1 的小于值计数，分别乘以 dp[n-j][k]（或 dp[n-j][k-1]），累加入 sum。这里把当前列的可行排列数用 DP 加权——query(...) 数小于值，dp 给“剩余位置怎么安排”的种数。第 1 项用 BIT1（已强制匹配），第 2 项用 BIT0（空闲值）
更新：当前列值 a[i][j] 从对应容器中移除——若它在本行已用过（vis[0]），从 BIT1移除，否则从 BIT0 移除
把上一行当前值 a[i-1][j] 标进 vis[0]（本行已用？语义上标记其"已处理"），把本行当前值 a[i][j] 标进 vis[1]。
若上行的这个值还没标记过（!vis[1]），则把它的位置在 BIT1 里 +1（代表可以复用/作为备选）。
若本行值 a[i][j] 尚未被 vis[0] 标记过，则空闲值数 k 减 1（它也被占用了）。
这段维护了两类状态：已固定要跟上一行对应的值（BIT1 + vis[1]）‍ 与 本行仍可自由分配的值（BIT0 + k）‍，从而逐列计算把本行填充方案数的加权和。最后 sum 即本行所有可行方案对答案的贡献
把本行贡献 sum 乘上 dp[n][n]^(n-i)（剩余 n-i 行的独立方案数）累加进 ans

c[0] 表示"本行仍可自由分配的值"；
c[1] 表示"已由上一行强制匹配到某列的值"；

fac[i]=fac[i-1]*i%mod	阶乘模
dp[0][0]=1	DP 初值
dp[i][j]=j*dp[i-1][j-1]+(i-j)*dp[i-1][j]	长度为 i 恰有 j 个固定位的排列计数
dp[i][i]=(i-1)*(dp[i-1][i-1]+dp[i-2][i-2])	全固定时的错排式递推（i=1 特判 0）
rd()	快读整数
cin>>n 循环 a[i][j]	记录输入矩阵
第一行循环 sum = a[1][i]-1-query(a[1][i],1)	康托式算第一行在排列中的 rank
ans = res*ksm(dp[n][n], n-1)	首行贡献 × 其余 n-1 行独立方案数幂
循环内 k--; add(...,-1,0)	上行的匹配值占用 BIT0
sum += query(...)*dp[n-j][k or k-1]	每一列用上一行信息和 DP 加权可行排列
更新 vis、加减 BIT	双向维护"已匹配"与"仍空闲"两种值的集合
ans += sum*ksm(dp[n][n],n-i)	本行贡献 × 剩余行方案数幂
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i = j; i <= k; ++i)
#define ll long long
using namespace std;

constexpr int N = 2010, mod = 998244353;

int n, c[2][N];
inline void add(int x, int y, bool q) { while (x <= n) { c[q][x] += y; x += x&-x; } }
inline ll query(int x, bool q) {
    ll res = 0;
    while (x) { res += c[q][x]; x -= x&-x; }
    return res;
}
inline ll ksm(ll x, int y) {
    ll res = 1;
    while (y) {
        if (y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

ll fac[N], dp[N][N];
inline void pre() {
    fac[0] = 1;
    rep(i,1,n) fac[i] = fac[i-1]*i%mod;
    dp[0][0] = 1;
    rep(i,1,n) rep(j,0,i) {
        if (!j) dp[i][j] = dp[i-1][j]*i%mod;
        else if (i == j) {
            if (i == 1) dp[i][i] = 0;
            else dp[i][i] = (i-1)*(dp[i-1][j-1]+dp[i-2][j-2])%mod;
        }
        else dp[i][j] = (j*dp[i-1][j-1]%mod+(i-j)*dp[i-1][j]%mod)%mod;
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N][N];
ll res, ans;
bool vis[2][N];
int main() {
    fast;
    n = rd();
    rep(i,1,n) rep(j,1,n) a[i][j] = rd();
    pre();
    rep(i,1,n) {
        ll sum = a[1][i] - 1 - query(a[1][i], 1);
        res = (res + fac[n-i]*sum%mod)%mod;
        add(a[1][i], 1, 1);
    }
    ans = res*ksm(dp[n][n], n-1)%mod;
    int k;
    rep(i,2,n) {
        k = n; ll sum = 0;
        memset(c,0,sizeof(c)); memset(vis,0,sizeof(vis));
        rep(j,1,n) add(j,1,0);
        rep(j,1,n) {
            if (!vis[1][a[i-1][j]]) { k--; add(a[i-1][j],-1,0); }
            sum = (sum+query(a[i][j]-1,1)*dp[n-j][k]%mod)%mod;
            if (k) sum = (sum+query(a[i][j]-1,0)*dp[n-j][k-1]%mod)%mod;
            if (vis[0][a[i][j]]) add(a[i][j],-1,1);
            else add(a[i][j],-1,0);
            vis[0][a[i-1][j]] = vis[1][a[i][j]] = 1;
            if (!vis[1][a[i-1][j]]) add(a[i-1][j],1,1);
            if (!vis[0][a[i][j]]) k--;
        }
        ans = (ans+sum*ksm(dp[n][n],n-i)%mod)%mod;
    }
    cout << ans;
    return 0;
}