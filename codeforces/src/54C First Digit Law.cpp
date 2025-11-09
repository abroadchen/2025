//
// Created by Psy.C on 2025/10/16.
//
/*
 *声明大小为n+1的double类型向量p，用于存储概率值
*定义一个lambda函数get，接受一个长整型x，返回长整型结果
这个函数用于计算从1到x中包含数字"1"的数字个数
*ans: 结果计数器，初始化为0
cur: x的位数
y: x的副本，用于计算
mul: 10的幂次，用于定位最高位
 *
*计算所有位数小于x的数字中包含"1"的个数
例如：1位数中有1个"1"，2位数中有10个包含"1"的数，等等
 *
*根据最高位是否为1进行不同处理：
如果最高位是1：加上从mul到x之间的所有数（因为它们都以1开头）
如果最高位大于1：加上所有以1开头的同位数个数
 *
*循环n次，每次读取区间[l,r]
计算在区间[l,r]中随机选择一个数包含数字"1"的概率
get(r)-get(l-1)表示区间[l,r]中包含"1"的数字个数
除以区间长度(r-l+1)得到概率
 *
 *初始化dp[0][0]为1，表示前0个事件中有0个成功的概率为1
*dp[i][j]表示前i个区间中恰好有j个区间选中的数包含"1"的概率
dp[i][j] = dp[i-1][j] * (1-p[i]) + dp[i-1][j-1] * p[i]
第一项：第i个区间不选中"1"的概率
第二项：第i个区间选中"1"的概率（当j>0时）
 *
*遍历所有可能的成功次数i
当100i >= kn时（即成功比例达到k%），将对应概率加到ans中
 *
 *
 *
 */
#include <iomanip>
#include <vector>
#include <ios>
#include <iostream>
using namespace std;

typedef long long ll;


void solve() {
    int n; cin >> n;
    vector<double> p(n + 1);

    auto get = [&](ll x) -> ll {
        if (!x) return 0;
        ll ans(0), cur(0), y(x), mul(1);
        while (y) cur++, y /= 10, mul *= 10;//计算x的位数cur和最高位权值mul
        mul /= 10;//调整mul为最高位的权值（例如对于123，mul为100）
        for (ll i = 1, res = 1; i < cur; ++i, res *= 10) ans += res;
        if (x / mul == 1) ans += x - mul + 1;
        else ans += mul;
        return ans;
    };
    for (int i = 1; i <= n; ++i) {
        ll l, r; cin >> l >> r;
        p[i] = 1.0 * (get(r) - get(l - 1)) / (r - l + 1);
    }
    vector<vector<double>> dp(n + 1, vector<double>(n + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] += dp[i - 1][j] * (1 - p[i]);
            if (j) dp[i][j] += dp[i - 1][j - 1] * p[i];
        }
    }
    int k; cin >> k; double ans(0);
    for (int i = 0; i <= n; ++i) if (100 * i >= k * n) ans += dp[n][i];
    cout << fixed << setprecision(15) << ans << '\n';
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}