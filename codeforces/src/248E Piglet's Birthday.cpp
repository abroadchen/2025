//
// Created by Psy.C on 2025/12/16.
//
/*
*a[N]：存储每个位置的值
mx[N]：存储每个位置的最大值
f[N][M]：概率DP数组，f[i][j]表示第i个位置值为j的概率
b[MAX][6]：组合数表，b[i][j] = C(i,j) = C(i-1,j) + C(i-1,j-1)
 *
 *
*从中取出x个的概率是：C(j,x) * C(a[u]-j,k-x) / C(a[u],k)
取出x个后，位置u剩下j-x个
累加到f[u][j-x]上
 *
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define M 105
#define MAX 500050
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    int a[N], mx[N];
    double f[N][M], b[MAX][6];
    for (int i = 1; i <= n; ++i) {
        cin>>a[i];
        mx[i] = a[i];
        f[i][a[i]] = 1;
    }
    for (int i = 0; i <= MAX - 5; ++i) {
        b[i][0] = 1;
        for (int j = 1; j <= min(i, 5); ++j)
            b[i][j] = b[i-1][j] + b[i-1][j-1];
    }
    double ans = 0, g[M];
    for (int i = 1; i <= n; ++i) ans += f[i][0];//所有位置值为0的概率之和
    int q; cin>>q;
    while (q--) {
        int u, v, k; cin>>u>>v>>k;
        ans -= f[u][0];
        for (int i = 0; i <= mx[u]; ++i) {
            g[i] = f[u][i];//位置u的概率分布备份到g数组
            f[u][i] = 0;//清空位置u的概率分布
        }
        for (int j = 0; j <= mx[u]; ++j) for (int x = 0; x <= k; ++x) {
            f[u][j-x] += b[j][x] * b[a[u]-j][k-x] / b[a[u]][k] * g[j];
        }
        a[u] -= k; a[v] += k;
        ans += f[u][0];
        cout << fixed << setprecision(12) << ans << '\n';
    }
    return 0;
}