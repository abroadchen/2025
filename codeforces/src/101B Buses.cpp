//
// Created by Psy.C on 2025/11/12.
//
/*
 *起始点s和结束点t
*n：目标区间长度[0,n]
m：区间数量
dp[N]：动态规划数组，dp[i]表示覆盖区间[0,a[i].t]的方案数
s[N]：前缀和数组，s[i] = dp[1]+dp[2]+...+dp[i-1]
ans：最终答案，初始化为0
 *
*t1：第一个结束点≥l的区间索引
t2：第一个结束点≥r的区间索引
 *
*算dp[i]：
s[t2] - s[t1]：结束点在[l,r)范围内的方案数之和
加上mod再取模防止负数
如果当前区间从0开始，方案数加1（可以直接使用该区间）
*更新前缀和数组s
如果当前区间能覆盖到目标终点n，将方案数加到答案中
 *
 *
 *O(m log m)：排序O(m log m) + 每次二分查找O(log m)
 */
#include <algorithm>
#include <ios>
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5+10, mod = 1e9+7;
struct node {
    int s, t;
    bool operator<(const node& b) const { return t < b.t; }
} a[N];
int n, m, dp[N], s[N], ans(0);

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m;
    memset(dp, 0, sizeof(dp)); memset(s, 0, sizeof(s));
    for (int i = 1; i <= m; ++i) cin>>a[i].s>>a[i].t;
    sort(a+1, a+1+m);
    for (int i = 1; i <= m; ++i) {
        int l = a[i].s, r = a[i].t,
        t1 = lower_bound(a + 1, a + 1 + m, (node){0, l}) - a,
        t2 = lower_bound(a + 1, a + 1 + m, (node){0, r}) - a;
        dp[i] = (s[t2] - s[t1] + mod) % mod;
        if (!l) ++dp[i];
        s[i + 1] = (s[i] + dp[i]) % mod;
        if (r == n) (ans += dp[i]) %= mod;
    }
    cout<<ans<<'\n';
    return 0;
}