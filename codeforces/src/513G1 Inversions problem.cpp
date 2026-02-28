//
// Created by Psy.C on 2026/2/28.
//
/**
n：数组长度
m：操作次数
a[N]：输入的原始数组
dp[N][N]：DP数组，dp[i][j]表示i和j位置元素逆序对的概率
t[N][N]：临时数组，保存上一轮的DP状态

初始化所有逆序对概率为1（初始状态下如果a[i]>a[j]则构成逆序对）
p：选择区间[x,y]的概率，共有n*(n+1)/2个可能的区间

对每个操作：
复制当前DP状态到临时数组t
清零dp数组
外层循环遍历所有可能的翻转区间[x,y]
内层循环遍历所有可能的逆序对(i,j)
计算翻转后的新位置u,v：
如果i在[x,y]区间内，翻转后位置变为x+y-i
如果j在[x,y]区间内，翻转后位置变为x+y-j
如果原区间[i,j]完全在[x,y]内：
翻转后原来不是逆序对的变成逆序对，概率为(1-t[i][j])*p
否则：
保持原来的逆序对状态，概率为t[i][j]*p

遍历所有可能的逆序对
如果原数组中a[i] > a[j]（原本是逆序对），加上dp[i][j]
否则（原本不是逆序对），加上1-dp[i][j]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


constexpr int N = 101;
int n, m, a[N];
double dp[N][N], t[N][N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) dp[i][j] = 1;
    const double p = 1./(n*(n+1)/2.);
    while (m--) {
        memcpy(t, dp, sizeof(dp));
        memset(dp, 0, sizeof(dp));
        for (int x = 1; x <= n; ++x)
            for (int y = x; y <= n; ++y) {
                for (int i = 1; i <= n; ++i)
                    for (int j = i + 1; j <= n; ++j) {
                        int u = i, v = j;
                        if (x <= u && u <= y) u = x + y - u;
                        if (x <= v && v <= y) v = x + y - v;
                        if (u > v) swap(u, v);
                        if (x <= i && j <= y) dp[u][v] += (1-t[i][j])*p;
                        else dp[u][v] += t[i][j]*p;
                    }
            }
    }
    double ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] > a[j]) ans += dp[i][j];
            else ans += 1 - dp[i][j];
        }
    printf("%.10f\n", ans);
    return 0;
}