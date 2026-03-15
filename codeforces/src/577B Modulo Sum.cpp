//
// Created by Psy.C on 2026/3/15.
//
/**
n：数组长度
m：模数
a[N]：输入数组
dp[i][j]：前i个数能否构成和模m余j
flag：标记是否能构成和模m为0

当n > m时，根据鸽笼原理，必定存在一个非空子集和能被m整除
因为前缀和只有m个可能的余数(0~m-1)，而有n个前缀和(n>m)，必有重复

前0个数能构成和模m余0（空集的和为0）
计算使得前i-1个数的和 + a[i] ≡ j (mod m)成立的前缀和余数
dp[i-1][t]：检查前i-1个数是否能构成余数t
如果能，则dp[i][j] = 1（选中第i个数）
如果j==0，说明找到了和模m为0的子集，设置flag=1
如果前i-1个数就能构成余数j，则前i个数也能构成余数j（不选第i个数）

dp[i][j] = dp[i-1][j] || dp[i-1][(j-a[i])%m]
即：前i个数能构成余数j = 不选第i个数能构成j || 选第i个数能构成j

时间复杂度
O(n × m)：双重循环
空间优化
可以用滚动数组优化空间至O(m)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5, M = 1005;
int n, m, a[N], dp[2][M], flag;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (n > m) {
        cout << "YES\n";
        return 0;
    }
    dp[0][0] = 1;//初始化第一行为1
    for (int i = 1; i <= n; ++i) {
        //当前行 上一行
        int cur = i&1, pre = cur^1;
        for (int j = 0; j < m; ++j) dp[cur][j] = 0;//清空当前行
        for (int j = 0; j < m; ++j) {
            //选择第i个数：从前一行的((j-a[i])%m+m)%m转移过来
            if (int t = ((j-a[i])%m+m)%m; dp[pre][t]) {
                dp[cur][j] = 1;
                if (j == 0) flag = 1;
            }
            //不选择第i个数：继承上一行的状态
            if (dp[pre][j]) dp[cur][j] = 1;
        }
    }
    cout << (flag ? "YES\n" : "NO\n");
    return 0;
}