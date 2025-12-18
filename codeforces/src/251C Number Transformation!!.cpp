//
// Created by Psy.C on 2025/12/17.
//
/*
*定义函数get，接受参数x作为起始点
使用memset将dp数组全部初始化为-1（表示未访问）
设置起始点x的距离为0
*创建队列q用于BFS搜索
将起始点x加入队列
*BFS主循环，当队列不为空时继续
取出队首元素u并弹出
*如果u-1位置未被访问过：
设置u-1的距离为u的距离+1
将u-1加入队列
*对于i从2到k：
计算v = u - (u % i)，即u对i取模后向下取整到i的倍数
如果v已经被访问过则跳过
设置v的距离为u的距离+1
将v加入队列
 *
*计算2到k的所有数字的最小公倍数(LCM)
使用公式：lcm(a,b) = a*b/gcd(a,b)
 *
*l：大于等于a的最小lcm倍数
r：小于等于b的最大lcm倍数
 *如果存在完整的lcm倍数区间
*计算完整lcm倍数区间的个数cnt
调用get函数计算从lcm-1到0的最短距离
*累加所有完整区间的操作次数
dp[0]*cnt：到0点的操作次数乘以区间数
+cnt：每个区间需要额外的一次操作
 *
*如果a不是lcm的倍数：
加上从a%lcm到0的操作次数
再加1次额外操作
*调用get函数计算从b%lcm到0的最短距离
加上这部分的操作次数
*如果不存在完整区间：
调用get函数计算从b%lcm到a%lcm的最短距离
 *
 *复杂度从 O(b-a) 降低到 O(LCM)，其中 LCM 在 k≤50 时最多约为 3000 万
 */
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 500007
using namespace std;

int dp[N], k;
void get(const int x) {
    memset(dp,-1,sizeof(dp)); dp[x] = 0;
    queue<int> q; q.push(x);
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        if (dp[u-1] == -1) {
            dp[u-1] = dp[u] + 1;
            q.push(u-1);
        }
        for (int i = 2; i <= k; ++i) {
            int v = u - (u % i);
            if (~dp[v]) continue;
            dp[v] = dp[u] + 1;
            q.push(v);
        }
    }
}


int main() {
    fast;
    ll a, b; int lcm = 1; cin>>a>>b>>k; swap(a, b);//确保 a >= b
    for (int i = 2; i <= k; ++i) lcm = lcm / __gcd(lcm, i) * i;
    ll ans = 0;
    const ll l = a + (lcm - a % lcm) % lcm, r = b - (b % lcm);
    if (l <= r) {
        const ll cnt = (r - l) / lcm; get(lcm - 1);
        ans = dp[0] * cnt + cnt;
        if (a % lcm) ans += dp[a % lcm] + 1;
        get(static_cast<int>(b % lcm));
        ans += dp[0];
    } else {
        get(static_cast<int>(b % lcm));
        ans = dp[a % lcm];
    }
    cout << ans << '\n';
    return 0;
}