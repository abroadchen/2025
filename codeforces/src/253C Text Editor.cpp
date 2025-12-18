//
// Created by Psy.C on 2025/12/17.
//
/*
 *a[105]存储每行的列数（索引从1到n）
*r1, c1：起点行和列
r2, c2：终点行和列
ans=1<<30：初始化答案为2^30（约10亿），作为无穷大的初始值
*l：当前行i、起点行r1、终点行r2中的最小值
r：当前行i、起点行r1、终点行r2中的最大值
 *
*初始化t为起点列c1
遍历从行l到行r的所有行
找到这些行中列数的最小值（即最窄的行宽度）
 *
*abs(i - r1)：从起点到第i行的垂直距离
abs(i - r2)：从第i行到终点的垂直距离
abs(t - c2)：水平移动距离（受到行宽限制）
总路径长度 = 垂直距离 + 水平距离
更新最小路径长度
 *时间复杂度：O(n²) 空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n; cin >> n;
    int a[105];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i]++;
    }
    int r1, c1, r2, c2, ans=1<<30; cin >> r1 >> c1 >> r2 >> c2;
    for (int i = 1, l, r, t; i <= n; ++i) {
        l = min(i, min(r1, r2));
        r = max(i, max(r1, r2));
        t = c1;
        for (int j = l; j <= r; ++j) t = min(t, a[j]);
        int sum = abs(i - r1) + abs(i - r2) + abs(t - c2);
        ans = min(ans, sum);
    }
    cout << ans << '\n';
    return 0;
}