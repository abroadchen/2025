//
// Created by Psy.C on 2026/4/21.
//
/**
线段的两个端点坐标 (x1,y1) 和 (x2,y2)
n: 输入的目标数字
m: 数组a的实际长度
a[30]: 存储n转换为6进制后的各位数字
将n转换为6进制表示，每一位存储在数组a中
a[1]到a[m]存储6进制的低位到高位
设置初始的两个线段

循环处理6进制的每一位（从高位到低位）
根据当前位的数值添加相应线段：
如果 a[i] <= 2：添加垂直线段 {len-1, len+1, len, len+1}
如果 a[i] % 3 == 0：添加垂直线段 {len-1, len+2, len, len+2}
总是添加水平线段 {len+1, len-1, len+1, len}
如果 a[i] % 3 != 2：添加垂直线段 {len+2, len-1, len+2, len}
扩展网格大小：len += 2
当不是最后一位时，添加连接当前轮和下一轮的线段
这些线段形成一个连接结构，确保不同位之间正确连接
当网格大小大于4时，添加额外的辅助线段
这些线段用于维持构造的连通性
输出网格大小：len × len
输出线段总数：k
输出每条线段的坐标
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

struct node {
    int x1, y1, x2, y2;
    void out() const {
        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
    }
} ans[400];

ll n;
int main() {
    fast;
    cin >> n;
    int m = 0, a[30];
    for (; n; n/=6) a[++m] = n%6;
    ans[1] = {1, 2, 2, 2};
    ans[2] = {2, 1, 2, 2};
    int k = 2, len = 2;
    for (int i = m; i >= 1; --i) {
        if (a[i] <= 2) ans[++k] = {len-1, len+1, len, len+1};
        if (a[i]%3 == 0) ans[++k] = {len-1, len+2, len, len+2};
        ans[++k] = {len+1, len-1, len+1, len};
        if (a[i]%3 != 2) ans[++k] = {len+2, len-1, len+2, len};
        len += 2;
        if (i == 1) break;
        ans[++k] = {len-2, len, len-2, len+1};
        ans[++k] = {len-1, len, len-1, len+1};
        ans[++k] = {len-2, len+2, len-1, len+2};
        ans[++k] = {len, len-2, len+1, len-2};
        ans[++k] = {len, len-1, len+1, len-1};
        ans[++k] = {len+2, len-2, len+2, len-1};
        if (len <= 4) continue;
        ans[++k] = {len-4, len+1, len-3, len+1};
        ans[++k] = {len+1, len-4, len+1, len-3};
    }
    cout << len << ' ' << len << '\n' << k << '\n';
    for (int i = 1; i <= k; ++i) ans[i].out();
    return 0;
}