//
// Created by Psy.C on 2026/3/20.
//
/**
dp[i][j]表示在树状数组j维中位置i的值
读取数组长度n和子序列长度k
k++：将k调整为1-indexed
外层循环：处理数组中的每个元素x
内层循环：对于每个长度j，计算以x结尾的长度为j的上升子序列数量
f = j; f--;：设置当前操作的维度为j-1
if (f == 0) ans = 1;：长度为1的子序列数量恒为1
else ans = sum(x - 1);：计算[1, x-1]范围内所有长度为j-1的子序列数量之和
f++;：恢复f的值
add(x, ans);：将计算结果添加到树状数组中
f = k;：设置维度为k
sum(n)：计算所有长度为k的上升子序列的总数
时间复杂度：O(nk log n) 空间复杂度：O(nk)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int low_bit(int x) { return x & -x; }

int f;///当前操作的维度
ll dp[N][15];
ll sum(int x) {
    ll ans = 0;
    while (x > 0) {
        ans += dp[x][f];
        x -= low_bit(x);
    }
    return ans;
}

int n;
void add(int x, ll dt) {
    while (x <= n) {
        dp[x][f] += dt;
        x += low_bit(x);
    }
}

int k;
int main() {
    fast;
    cin >> n >> k; k++;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        for (int j = 1; j <= k; ++j) {
            ll ans; f = j; f--;
            if (f == 0) ans = 1;
            else ans = sum(x - 1);
            f++;
            add(x, ans);
        }
    }
    f = k;
    cout << sum(n) << '\n';
    return 0;
}