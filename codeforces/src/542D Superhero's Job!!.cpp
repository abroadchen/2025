//
// Created by Psy.C on 2026/3/6.
//
/**
检查x-1是否恰好有一个质因子（即x-1是否是质数的幂）
cnt：不同质因子的数量
who：记录最后一个发现的质因子
循环找出x-1的所有质因子
如果超过1个不同的质因子，返回false（0）
如果x-1>1说明还有一个大质因子
如果只有1个质因子，返回该质因子；否则返回0

A：输入的数字
fac[N]：存储A的因子
who[N]：存储对应因子的质因数
p[N]：存储唯一的质因数
dp[N]：动态规划数组
n：因子数量
cnt：质因数数量
g[N]：以质因数为索引的因子分组

找出A的所有因子（除了1和2）：

遍历从1到√A的所有数
如果i是A的因子且大于2，添加到fac数组
如果A/i也是因子且大于2，也添加到fac数组
如果没有找到有效因子，输出0
添加因子1
对所有因子排序

对每个因子调用check函数
如果因子满足条件（减1后是质数的幂），将其质因数添加到p数组
对质因数排序
使用unique去重，保留唯一质因数
将每个因子按其质因数分组到g数组中
使用二分查找找到质因数在p数组中的位置

初始化dp[1]=1（基础情况）
动态规划：按质因数分组枚举
对每个现有状态，尝试与当前组中的因子相乘
检查乘积是否超过1e18避免溢出
如果乘积是合法因子，更新对应的dp值
到达最大因子的方案数

p 是数组的起始地址
地址 - 起始地址 = 数组索引

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 7007;

ll check(ll x) {
    int cnt = 0; x--;
    ll who = -1;
    for (ll i = 2; i*i <= x; ++i) {
        if (x%i) continue;
        cnt++; who = i;
        while (x%i == 0) x/=i;
        if (cnt > 1) return false;
    }
    if (x > 1) { cnt++; who = x; }
    return cnt == 1 ? who : 0;
}

ll A, fac[N], who[N], p[N], dp[N];
int n, cnt;
vector<ll> g[N];
int main() {
    fast;
    cin >> A;
    if (A == 1) return cout << "1\n", 0;
    for (ll i = 1; i*i <= A; ++i) {
        if (A%i) continue;
        if (i > 2) fac[++n] = i;
        if (i*i < A && A/i > 2) fac[++n] = A/i;
    }
    if (!n) return cout << "0\n", 0;
    fac[++n] = 1;
    sort(fac + 1, fac + n + 1);
    for (int i = 1; i <= n; ++i) {
        who[i] = check(fac[i]);
        if (who[i]) p[++cnt] = who[i];
    }
    sort(p + 1, p + cnt + 1);
    cnt = unique(p + 1, p + cnt + 1) - p - 1;
    for (int i = 1; i <= n; ++i) {
        if (who[i])
            g[lower_bound(p + 1, p + cnt + 1, who[i])-p].push_back(fac[i]);
    }
    dp[1] = 1;
    for (int i = 1; i <= cnt; ++i)
        for (int j = n; j >= 1; --j) {
            if (!dp[j]) continue;
            for (const auto& t : g[i]) {
                if (1.*t*fac[j] > 1e18) continue;
                int pos = lower_bound(fac + 1, fac + 1 + n, t*fac[j]) - fac;
                if (pos <= n && fac[pos] == t*fac[j])
                    dp[pos] += dp[j];
            }
        }
    cout << dp[n] << '\n';
    return 0;
}