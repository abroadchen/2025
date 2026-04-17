//
// Created by Psy.C on 2026/4/16.
//
/**
T, n, m, k：测试用例数、行数、列数、分割段数
i, j, h, x：循环变量
a[N][N]：输入的二维数组
pre[1<<16][17]：前驱数组，用于回溯路径
mn, ans[17]：最小值和答案数组
sum, now：临时变量
val[17][17]：存储状态转移的代价
f[1<<16][17]：DP数组，f[mask][last]表示使用mask集合的段，最后一个是last的最小代价

两层循环计算任意两个段i和j之间的转移代价
if (i == j) continue;：跳过相同段的情况
x = n/k*i;：计算第i段的结束位置
now += a[x][h] + a[x-1][h] + ...：计算第i段边界附近6个位置的值
x = n/k*(j-1)+1;：计算第j段的开始位置
now -= a[x][h] + a[x+1][h] + ...：减去第j段边界附近6个位置的值
sum += 1ll*now*now;：累加差值的平方
val[i][j] = sum;：保存i到j的转移代价

memset(f, 120, sizeof(f));：将f数组初始化为一个大数
for (i = 1; i <= k; ++i) f[1<<(i-1)][i] = 0;：初始化单个元素的状态
三层循环进行状压DP
if (!(i&(1<<(j-1)))) continue;：如果当前状态i不包含j，跳过
if (i&(1<<(h-1))) continue;：如果当前状态i已经包含h，跳过
int nxt = i + (1<<(h-1));：添加元素h后的新状态
状态转移：f[nxt][h] = f[i][j] + val[j][h]
pre[nxt][h] = j;：记录前驱状态
在所有可能的终点中找到代价最小的一个
从最终状态回溯到初始状态
ans[mn] = i;：记录第mn段的编号为i
j -= 1<<(mn-1);：从状态j中移除元素mn
mn = pre[j+(1<<(mn-1))][mn];：获取前一个状态的最后一个元素
输出每一段的顺序
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 605;

int T, n, m, k, i, j, a[N][N], h, x, pre[1<<16][17], mn, ans[17];
ll sum, now, val[17][17], f[1<<16][17];
int main() {
    fast;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= m; ++j) cin >> a[i][j];
        for (i = 1; i <= k; ++i)
            for (j = 1; j <= k; ++j) {
                if (i == j) continue;
                sum = 0;
                for (h = 1; h <= m; ++h) {
                    x = n/k*i; now = 0;
                    now += a[x][h] + a[x-1][h] + a[x-1][h-1] +
                        a[x-1][h+1] + a[x][h-1] + a[x][h+1];
                    x = n/k*(j-1)+1;
                    now -= a[x][h] + a[x+1][h] + a[x+1][h-1] +
                        a[x+1][h+1] + a[x][h-1] + a[x][h+1];
                    sum += 1ll*now*now;
                }
                val[i][j] = sum;
            }
        memset(f, 120, sizeof(f));
        for (i = 1; i <= k; ++i) f[1<<(i-1)][i] = 0;
        for (i = 1; i < 1<<k; ++i)
            for (j = 1; j <= k; ++j) {
                if (!(i&(1<<(j-1)))) continue;
                for (h = 1; h <= k; ++h) {
                    if (i&(1<<(h-1))) continue;
                    int nxt = i + (1<<(h-1));
                    if (f[i][j] + val[j][h] < f[nxt][h])
                        f[nxt][h] = f[i][j] + val[j][h], pre[nxt][h] = j;
                }
            }
        mn = 1;
        for (i = 2; i <= k; ++i)
            if (f[(1<<k)-1][i] < f[(1<<k)-1][mn]) mn = i;
        for (i = k, j = (1<<k)-1; i; i--) {
            ans[mn] = i;
            j -= 1<<(mn-1);
            mn = pre[j+(1<<(mn-1))][mn];
        }
        for (i = 1; i <= k; ++i)
            cout << ans[i] << ' ';
        cout << '\n';
    }
    return 0;
}