//
// Created by Psy.C on 2026/1/19.
//
/**
* n,m,r：矩阵大小和半径
h[N]：圆弧高度数组
d[N]：距离数组
s[N][N]：前缀和数组
p[N][N]：圆形区域和数组
mxl/mxr：左右最大值数组
pol/por：左右最大值计数数组
ans：答案
cnt：计数
 *
*mxl[i][j]：从左到j的最大圆形和
pol[i][j]：最大值的出现次数
*mxr[i][j]：从右到j的最大圆形和
por[i][j]：最大值的出现次数
 *
*遍历所有可能的圆形区域中心
计算两个不重叠圆形区域的最大和
(r<<1|1) 等价于 2*r+1，判断是否足够远以避免重叠
如果距离足够远，使用整行最大值
否则考虑距离限制下的最大值
 *
*输出最大和
输出方案数
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 510
#define rep(i,n) for (int i = 1; i <= (n); ++i)
using namespace std;


int main() {
    fast;
    int n, m, r, x, h[N], d[N]; cin >> n >> m >> r;
    ll s[N][N], p[N][N], mxl[N][N], pol[N][N], mxr[N][N], por[N][N], ans = 0, cnt = 0;
    rep(i,n) rep(j,m) {
        cin >> x;
        s[i][j] = s[i][j-1] + x;//每行的前缀和数组
    }
    h[0] = r;//圆心处的高度
    rep(i,r) h[i] = static_cast<int>(sqrt(r * r - i * i));//h[i] = sqrt(r² - i²)：计算圆弧上各点的高度
    for (int i = 0; i <= r<<1; ++i) for (int j = 0; j <= r; ++j) {//两个圆心距离为i时的最大影响范围
        if (j >= i - r) d[i] = max(d[i], h[j] + h[abs(i - j)] + 1);
    }
    //遍历矩阵中心区域（避开边界）
    for (int i = r + 1; i <= n - r; ++i) for (int j = r + 1; j <= m - r; ++j) {
        for (int k = -r; k <= r; ++k)//(i,j)为中心、半径为r的圆形区域内的元素和
            p[i][j] += s[i+k][j+h[abs(k)]] - s[i+k][j-h[abs(k)]-1];//使用前缀和快速计算圆形区域和
    }
    for (int i = r + 1; i <= n - r; ++i) for (int j = r + 1; j <= m - r; ++j) {
        mxl[i][j] = mxl[i][j-1], pol[i][j] = pol[i][j-1];//每行左侧的最大值和计数
        if (p[i][j] > mxl[i][j]) mxl[i][j] = p[i][j], pol[i][j] = 1;
        else if (p[i][j] == mxl[i][j]) pol[i][j]++;
    }
    for (int i = r + 1; i <= n - r; ++i) for (int j = m - r; j >= r + 1; --j) {
        mxr[i][j] = mxr[i][j+1], por[i][j] = por[i][j+1];//每行右侧的最大值和计数
        if (p[i][j] > mxr[i][j]) mxr[i][j] = p[i][j], por[i][j] = 1;
        else if (p[i][j] == mxr[i][j]) por[i][j]++;
    }
    for (int i = r + 1; i <= n - r; ++i) for (int j = r + 1; j <= m - r; ++j) {
        const ll res = p[i][j];
        for (int k = r + 1; k <= n - r; ++k) {
            if (abs(k - i) >= (r<<1|1)) {
                if (res + mxl[k][m-r] > ans)
                    ans = res + mxl[k][m-r], cnt = pol[k][m-r];
                else if (res + mxl[k][m-r] == ans) cnt += pol[k][m-r];
                continue;
            }
            if (j - d[abs(k - i)] >= r + 1) {
                if (res + mxl[k][j-d[abs(k-i)]] > ans)
                    ans = res + mxl[k][j-d[abs(k-i)]], cnt = pol[k][j-d[abs(k-i)]];
                else if (res + mxl[k][j-d[abs(k-i)]] == ans)
                    cnt += pol[k][j-d[abs(k-i)]];
            }
            if (j + d[abs(k-i)] <= m - r) {
                if (res + mxr[k][j+d[abs(k-i)]] > ans)
                    ans = res + mxr[k][j+d[abs(k-i)]], cnt = por[k][j+d[abs(k-i)]];
                else if (res + mxr[k][j+d[abs(k-i)]] == ans)
                    cnt += por[k][j+d[abs(k-i)]];
            }
        }
    }
    cout << ans << ' ' << (cnt>>1);
    return 0;
}