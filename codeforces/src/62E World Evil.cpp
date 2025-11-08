//
// Created by Psy.C on 2025/10/29.
//
/*
*N = 5：最大元素数量（可能是状态或位置）
M = 100005：最大步数/时间单位
C = 32：动态规划数组大小（2^N = 2^5 = 32）
*n, m：输入参数
r[N][M]：二维数组存储转移成本
c[N][M]：二维数组存储配置成本
dp[C]：动态规划数组存储最小成本
 *
*读取转移成本矩阵r：
对于每一步i从1到m-1
对于每个元素j从1到n
将成本存储在r[j-1][i]中（转换为0索引）
*读取配置成本矩阵c：
对于每一步i从1到m
对于每个元素j从1到n
将成本存储在c[j-1][i]中（转换为0索引）
 *
*使用位操作的状态转移：
对于每个可能的状态j（从0到2^n - 1）
对于每个元素k（从0到n-1）
j^(1<<k)：切换状态j中的第k位
通过添加转移成本r[k][i]更新到达新状态的最小成本
 *
*配置成本计算：
对于每个状态j和每个元素k
检查相邻元素（k和(k+1)%n）在位表示中是否有不同状态
如果它们不同（异或为1），则将配置成本c[k][i+1]加到当前状态成本中
 *
 *输出到达最终状态（所有位都设为1）的最小成本
 */
#include <cstring>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define repe(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;

typedef long long ll;
const int N = 5, M = 100005, C = 32;
int n, m;
ll r[N][M], c[N][M], dp[C];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    rep(i,1,m) repe(j,1,n) cin >> r[j - 1][i];
    repe(i,1,m) repe(j,1,n) cin >> c[j - 1][i];
    memset(dp, 0x3f, sizeof(dp));//（0x3f代表无穷大）
    dp[0] = 0;//（未选择任何元素）的成本为0
    repe(i,1,m-1) {
        rep(j,0,1<<n) repe(k,0,n-1) {
            dp[j^(1<<k)] = min(dp[j^(1<<k)], dp[j] + r[k][i]);
        }
        rep(j,0,1<<n) repe(k,0,n-1) {
            if (((j>>k)&1)^((j>>((k+1)%n))&1)) dp[j] += c[k][i+1];
        }
    }
    cout << dp[(1<<n)-1];
    return 0;
}