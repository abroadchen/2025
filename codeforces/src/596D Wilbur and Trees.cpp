//
// Created by Psy.C on 2026/3/20.
//
/**
[l][r]：区间[l,r]
[x][y]：两个布尔状态
p：概率值
a[N]：位置数组
h：步长参数
s1[N], s2[N]：辅助数组，用于快速查找

计算区间[l,r]的期望值
x, y：布尔状态，表示左边和右边是否已达到高度h
第一项：以概率p选择左边
0.5*p*：考虑对称性和概率p
min(a[l]-a[l-1]-x*h, h)：左边移动的距离
dfs(l+1, r, 0, y)：递归处理剩余区间
第二项：以概率(1-p)选择右边
0.5*(1-p)*：考虑对称性和概率(1-p)
min(a[r+1]-a[r]-y*h, h)：右边移动的距离
dfs(l, r-1, x, 0)：递归处理剩余区间

s1[r]：从r往左第一个与r距离≥h的位置
s2[l]：从l往右第一个与l距离≥h的位置
根据这些位置决定是直接计算还是递归处理
时间复杂度约为O(n²)，空间复杂度约为O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e3+5, inf = 0x3f3f3f3f;

double dp[N][N][2][2], p;
int a[N], h, s1[N], s2[N];
double dfs(int l, int r, int x, int y) {
    double sum = 0;
    if (l > r) return 0;
    if (dp[l][r][x][y]) return dp[l][r][x][y];
    sum += 0.5*p*(min(a[l]-a[l-1]-x*h, h) + dfs(l+1, r, 0, y));
    sum += 0.5*(1-p)*(min(a[r+1]-a[r]-y*h, h) + dfs(l, r-1, x, 0));
    if (s1[r] <= l) sum += 0.5*p*(min(a[l]-a[l-1]-x*h, h)+a[r]-a[l]);
    else sum += 0.5*p*(dfs(l,s1[r]-1,x,1)+a[r]-a[s1[r]]+h);
    if (s2[l] >= r) sum += 0.5*(1-p)*(min(a[r+1]-a[r]-y*h, h)+a[r]-a[l]);
    else sum += 0.5*(1-p)*(dfs(s2[l]+1,r,1,y)+a[s2[l]]-a[l]+h);
    dp[l][r][x][y] = sum;
    return dp[l][r][x][y];
}

int n;
int main() {
    fast;
    cin >> n >> h >> p;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1); s1[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i] - a[i-1] < h) s1[i] = s1[i-1];
        else s1[i] = i;
    }
    s2[n] = n;
    for (int i = n-1; i >= 1; --i) {
        if (a[i+1] - a[i] < h) s2[i] = s2[i+1];
        else s2[i] = i;
    }
    a[0] = -inf; a[n+1] = -a[0];
    printf("%.9lf\n", dfs(1, n, 0, 0));
    return 0;
}