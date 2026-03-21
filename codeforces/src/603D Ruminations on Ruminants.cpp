//
// Created by Psy.C on 2026/3/21.
//
/**
n: 直线数量
x[N], y[N]: 每条直线在变换后的位置坐标
k[N]: 斜率数组
输入直线方程 ax + by + c = 0 的系数
将直线转换为垂足坐标：
(a*c/(a²+b²), b*c/(a²+b²)) 是原点到直线的垂足坐标
这种变换将直线表示为点坐标，便于后续计算
对于每个基准直线i，统计与它相关的交点数
sum: 与直线i完全重合的直线数
tot: 与直线i不同但相交的直线数
k[]: 存储相对于直线i的斜率

时间复杂度
外层循环：O(n)
内层处理：O(n log n)（排序）
总体：O(n² log n)
空间复杂度
O(n)：存储坐标和斜率数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define eps 1e-12
using namespace std;
constexpr int N = 2005, inf = 1e9;
int n;
double x[N], y[N], k[N];
int main() {
    fast;
    cin >> n;
    double a, b, c;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b >> c;
        x[i] = a*c/(a*a+b*b), y[i] = b*c/(a*a+b*b);
    }
    ll ans = 0;
    for (int i = 1; i <= n-2; ++i) {
        int tot = 0, sum = 0, pos = 1;
        for (int j = i+1; j <= n; ++j) {
            if (x[i] == x[j] && y[i] == y[j]) ++sum;//重合的直线
            else if (x[i] != x[j]) k[++tot] = (y[j]-y[i])/(x[j]-x[i]);//计算斜率
            else k[++tot] = inf;//垂直线（斜率为无穷）
        }
        sort(k+1,k+tot+1);
        for (int j = 1; j <= sum; ++j) ans += n - i - j;//重合直线的贡献
        for (int j = 1; j <= tot; ++j) {
            while (abs(k[pos] - k[j]) > eps) ++pos;//找到相同斜率的位置
            ans += j - pos;//计算相交对数
        }
    }
    cout << ans << '\n';
    return 0;
}