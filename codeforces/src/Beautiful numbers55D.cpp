//
// Created by Psy.C on 2025/10/19.
//
/*
*N: 模数相关，2520是1-9的最小公倍数加5
M: 最大位数，用于存储数字的每一位
K: 离散化后因子个数
MOD: 2520，1-9所有数字的最小公倍数
*dp[M][N][K]: 数位DP的状态数组，dp[位置][余数][最小公倍数索引]
idx[MOD+3]: 用于离散化存储MOD的因子索引
dig[M]: 存储数字的每一位
 *
*discretize函数：对2520的所有因子进行离散化编号
遍历1到2520，如果i是2520的因子，则给它分配一个递增的索引号
 *
*dfs函数：数位DP的核心递归函数
参数说明：
pos: 当前处理的位置
mod: 当前构成的数字对2520的余数
Lcm: 当前已选数字的最小公倍数
limit: 是否受到上界的限制
 *递归终止条件：如果处理完所有位数，判断数字是否能被其各位数字的最小公倍数整除
 *记忆化搜索：如果没有限制且该状态已计算过，直接返回结果
*确定当前位能填入的数字上界
遍历0到up的所有可能数字：
如果是0，最小公倍数不变(因为0不参与LCM计算)
如果非0，更新最小公倍数为LCM和当前数字的最小公倍数
递归处理下一位，更新余数和限制条件
*如果不受限制，保存计算结果
返回当前状态的答案
 *
*solve函数：计算0到x范围内满足条件的数字个数
将x的每一位存储到dig数组中
调用dfs函数进行数位DP计算
 */
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
const int N = 2525, M = 20, K = 50, MOD = 2520;
ll dp[M][N][K];
int idx[MOD+3], dig[M];

ll gcd(ll m, ll n) { return n ? gcd(n, m%n) : m; }
ll lcm(ll m, ll n) { return m / gcd(m, n) * n; }

void discretize() {
    int cnt(0);
    for (int i = 1; i <= MOD; ++i) {
        if (MOD % i == 0) idx[i] = ++cnt;
    }
}

ll dfs(int pos, int mod, int Lcm, int limit) {
    if (pos == 0) return mod % Lcm == 0;
    if (!limit && dp[pos][mod][idx[Lcm]] != -1) return dp[pos][mod][idx[Lcm]];
    int up = limit ? dig[pos] : 9;
    ll ans(0);
    for (int i = 0; i <= up; ++i) {
        if (i == 0) ans += dfs(pos - 1, (mod*10+i)%MOD, Lcm, limit && i == up);
        else ans += dfs(pos - 1, (mod*10+i)%MOD, lcm(Lcm, i), limit && i == up);
    }
    if (!limit) dp[pos][mod][idx[Lcm]] = ans;
    return ans;
}

ll solve(ll x) {

    int len(0);
    while (x) {
        dig[++len] = x % 10;
        x /= 10;
    }
    return dfs(len, 0, 1, 1);
}




int main() {
    discretize();
    int t; scanf("%d", &t);
    memset(dp, -1, sizeof(dp));
    while (t--) {
        ll l, r; scanf("%lld%lld", &l, &r);
        printf("%lld\n", solve(r) - solve(l - 1));
    }
    return 0;
}