//
// Created by Psy.C on 2025/11/7.
//
/*
*n: 点的数量
a, b, c, d: 分别表示x坐标的最小值、y坐标的最小值、x坐标的最大值、y坐标的最大值
X, Y: 输入坐标临时变量
x[N], y[N]: 存储变换后的坐标数组
f, g, h, s: 计算结果相关变量
 *
*坐标变换：将笛卡尔坐标系转换为切比雪夫距离坐标系
x[i] = X - Y: 新的x坐标
y[i] = X + Y: 新的y坐标
 *
*f: 计算点到边界矩形各边距离的最小值的最大值（第一种情况）
g: 计算点到边界矩形各边距离的最小值的最大值（第二种情况，y轴方向相反）
 *
 *遍历所有点，如果某点到边界矩形四边的最大距离不超过h
 *如果f等于g且内部还有空间
 *h（最小距离）和s（计数结果）
 *
 *时间复杂度为O(n)
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

const int inf = 1e5, N = 10100, mod = 1e9+7;
int n, a, b, c, d, X, Y,
x[N], y[N], f, g, h, s;

int main() {
    scanf("%d",&n);
    a = b = inf, c = d = -inf;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &X, &Y);
        x[i] = X - Y; y[i] = X + Y;
        a = min(a, x[i]); c = max(c, x[i]);
        b = min(b, y[i]); d = max(d, y[i]);
    }
    for (int i = 0; i < n; ++i) {
        f = max(f, min(max(x[i] - a, y[i] - b), max(c - x[i], d - y[i])));
        g = max(g, min(max(x[i] - a, d - y[i]), max(c - x[i], y[i] - b)));
    }
    h = min(f, g); s = 2;
    for (int i = 0; i < n; ++i) {
        if (max(max(x[i] - a, y[i] - b), max(c - x[i], d - y[i])) <= h)
            s = s * 2 % mod;
    }
    if (f == g && a + h < c && b + h < d) s = s * 2 % mod;
    printf("%d\n%d", h, s);
    return 0;
}