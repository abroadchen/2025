//
// Created by Psy.C on 2026/2/12.
//
/**
n：每行的元素数量
q：行数
a[10][N]：存储q行，每行n个元素的二维数组
pos[10][N]：记录每个数值在每行中的位置
dp[N]：动态规划数组，记录最长递增子序列的长度

时间复杂度为O(q × n²)，空间复杂度为O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2005
using namespace std;

int n, q, a[10][N], pos[10][N], dp[N];

int main() {
    fast;
    cin >> n >> q;
    for (int i = 1; i <= q; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
            pos[i][a[i][j]] = j;//第i行中值为a[i][j]的元素位于第j列
        }
    for (int i = 1; i <= n; ++i) {
        dp[a[1][i]] = 1;//当前元素的LIS长度为1
        for (int j = 1; j < i; ++j) {
            const int t1 = a[1][i], t2 = a[1][j];//当前元素和之前的元素
            bool flag = true;//所有行的单调性条件
            for (int k = 2; k <= q; ++k) {
                if (pos[k][t1] <= pos[k][t2]) {//第k行中t1的位置不严格大于t2的位置
                    flag = false;
                    break;
                }
            }
            if (flag) dp[t1] = max(dp[t1], dp[t2] + 1);
        }
    }
    int ans = 1;
    for (int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
    cout << ans << '\n';
    return 0;
}