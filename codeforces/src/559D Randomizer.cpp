//
// Created by Psy.C on 2026/3/11.
//
/**
叉积的值等于平行四边形面积
calc(s, t): 使用皮克定理计算内部点数（S = I + B/2 - 1，所以 I = S - B/2 + 1）
A = I + B/2 - 1
A: 多边形面积
I: 内部格点数
B: 边界格点数

f: 预计算的2的幂次
get(n, k): 计算某种比例或权重
计算总面积S: 使用鞋带公式（以顶点0为基准）
计算边界点数T: 每条边上格点数 = gcd(dx, dy)
遍历所有顶点，计算子区域贡献
pre: 当前边向量
s: 子三角形面积
t: 子区域边界点数
k: 当前考虑的边数
计算多个子区域的贡献并累加
最终结果 = 总面积计算值 - 子区域重复计算值

now：从顶点 i 到顶点 j 的向量（对角线）
tmp：now - pre，表示从 pre 向量到 now 向量的差向量
num：向量 now 上的格点数（从原点到点 a[j]-a[i]）
更新边界点总数 t
pre * now：计算向量 pre 和 now 的叉积
叉积值 = 平行四边形面积，除以2得到三角形面积
累加到子区域面积 s
calc(s, t)：使用皮克定理计算当前子区域的内部格点数
((j+1)%n == i ? 0 : num-1)：条件修正项
如果 j+1 == i（即将绕回起点），加0
否则加 num-1（边界点修正）
get(n, k)：权重系数，根据总顶点数和当前边数计算
t -= num;      // 从t中减去num（可能是为了下次循环做准备）
pre = now;     // 将当前向量作为下一轮的pre

O(n × min(n, 35)) ≈ O(n²)（由于k限制为35）
对于大n值进行了优化
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 100;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
struct node {
    int x, y;
    node operator-(const node& o) const { return node{x - o.x, y - o.y}; }
    double operator*(const node& o) const { return 1.* x * o.y - 1.* y * o.x; }
} a[N];
double calc(double s, double t) { return s + 1. - 0.5 * t; }
double f[M+5];
double get(int n, int k) {
    if (n > M) return 1./f[k+1];
    return (f[n-k-1]-1)/(f[n]-1-n-0.5*n*(n-1));
}

int n;
int main() {
    fast;
    f[0] = 1;
    for (int i = 1; i <= M; ++i) f[i] = 2.*f[i-1];
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y;
    double S = 0, T = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        S += (a[i] - a[0]) * (a[j] - a[0]) * 0.5;
        T += gcd(abs(a[j].x - a[i].x), abs(a[j].y - a[i].y));
    }
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        node pre = a[(i+1)%n] - a[i];
        double s = 0, t = gcd(abs(pre.x), abs(pre.y));
        for (int j = (i+2)%n, k = 2; k <= 35 && (j+1)%n != i; j = (j+1)%n, ++k) {
            node now = a[j] - a[i], tmp = now - pre;
            double num = gcd(abs(now.x), abs(now.y));
            t += num + gcd(abs(tmp.x), abs(tmp.y));
            s += pre * now * 0.5;
            ans += (calc(s, t) + ((j+1)%n == i ? 0 : num-1)) * get(n, k);
            t -= num;
            pre = now;
        }
    }
    printf("%.10f\n", calc(S, T) - ans);
    return 0;
}