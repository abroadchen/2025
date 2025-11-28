//
// Created by Psy.C on 2025/11/27.
//
/*
*对于每个数字a[i]，将其存储在dp[a[i] ^ N]位置
a[i] ^ N表示a[i]的按位取反（因为N是全1的22位数）
 *
*从大到小遍历所有可能的掩码
如果dp[i]为空（0）：
检查所有可以通过将第j位设为1得到的掩码i|(1<<j)
如果dp[i|(1<<j)]非空，则将dp[i|(1<<j)]的值赋给dp[i]
这是SOS DP的核心步骤，用于填充缺失的子集信息
 *
*对于每个输入的数字a[i]，输出dp[a[i]]
如果dp[a[i]]为0，输出"-1"
分别处理前n-1个元素（带空格）和最后一个元素（带换行）
 *
 *i|(1<<j) 的作用是：将数字i的第j位（从右往左数，从0开始）设置为1
*这实现了SOS DP (Sum over Subsets) 中的转移：
如果我们知道了更大的集合的信息，可以用来更新较小集合的信息
i|(1<<j)表示比i更大的掩码（在第j位上多了1个1）
由于大的掩码包含小的掩码作为子集，所以可以用大掩码的信息来填充小掩码
 *
 *
 *
 *时间复杂度：O(N * log N)，其中N=2^22 空间复杂度：O(N)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = (1<<22)-1;
int dp[N], a[N];

int main() {
    fast;
    int n; cin>>n;
    for (auto& x : dp) x = 0;
    for (int i = 0; i < n; ++i) {
        cin>>a[i];
        dp[a[i] ^ N] = a[i];
    }
    for (int i = N; i >= 0; --i) {
        if (!dp[i]) {
            for (int j = 0; j < 22; ++j) if (dp[i|(1<<j)]) {
                dp[i] = dp[i|(1<<j)];
            }
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        if (dp[a[i]]) cout << dp[a[i]] << ' ';
        else cout << "-1 ";
    }
    if (dp[a[n - 1]]) cout << dp[a[n - 1]] << '\n';
    else cout << "-1\n";
    return 0;
}