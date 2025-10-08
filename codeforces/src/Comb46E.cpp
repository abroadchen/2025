//
// Created by Psy.C on 2025/10/7.
//
/*
*N = 1510：数组大小上限
inf = 1e18：表示无穷大的值
n, m：矩阵的行数和列数
a[N][N]：存储输入矩阵
dp[N][N]：动态规划数组，dp[i][j]表示到达第i行第j列时的最大权值和
 *
*初始化第一行：只能从左到右移动
dp[1][i]表示从(1,1)到(1,i)的权值和，等于前缀和
*从第二行开始进行动态规划
best：上一行最优解
sum：当前行的累积和
如果是奇数行(i%2为真)，则从左到右移动
 *
*奇数行(从左到右)：
sum初始化为当前行第一个元素
best初始化为上一行第一列的值
对于每一列j，dp[i][j] = best + sum，即上一行最优解加上当前行前缀和
更新best为max(best, dp[i-1][j])
 *
*偶数行(从右到左)：
sum初始化为当前行前m-1个元素的和
best初始化为上一行最后一列的值
从右到左遍历，dp[i][j] = best + sum
每次减去当前元素并更新best
 *
 *
 *时间复杂度O(n×m)，空间复杂度O(n×m)
 *
 *
 *
 */
#include <ios>
#include <iostream>
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define repd(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef long long ll;
//更新a为a和b中的较大值
template<class T, class V>inline void maxx(T& a, V b) { if (a < b) a = b; }

const int N = 1510;
const ll inf = 1e18;
int n, m;//矩阵的行数和列数
ll dp[N][N], a[N][N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;

    rep(i, 1, n + 1) rep(j, 1, m + 1) cin >> a[i][j];
    rep(i, 1, m + 1) dp[1][i] = dp[1][i - 1] + a[1][i];
    rep(i, 2, n + 1) {
        ll best(0), sum(0);
        if (i % 2) {
            sum = a[i][1];
            best = dp[i - 1][1];
            rep(j, 2, m + 1) {
                sum += a[i][j];
                dp[i][j] = best + sum;
                maxx(best, dp[i - 1][j]);
            }
        } else {
            sum = 0;
            best = dp[i - 1][m];
            rep(j, 1, m) sum += a[i][j];
            repd(j, m - 1, 1) {
                dp[i][j] = best + sum;
                sum -= a[i][j];
                maxx(best, dp[i - 1][j]);
            }
        }
    }

    ll ans(-inf);
    if (n % 2) rep(i, 2, m + 1) maxx(ans, dp[n][i]);
    else rep(i, 1, m) maxx(ans, dp[n][i]);
    cout << ans << '\n';
    return 0;
}