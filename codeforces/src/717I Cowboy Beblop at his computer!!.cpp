//
// Created by Psy.C on 2026/4/22.
//
/**
node：三维点/向量结构
a[2][N]：两个多边形的顶点坐标（a[0]和a[1]分别存储两个多边形）
p[2]：两个多边形的法向量
x：临时变量
实现向量减法：a - b
实现向量叉积：a × b
叉积结果垂直于原两个向量
实现向量点积：a · b
返回标量值
read()：读取整数
sgn(x)：符号函数，返回-1、0或1
读取两个多边形的数据
a[t][n[t]] = a[t][0]：将最后一个点设为第一个点（形成闭环）
p[t]：计算多边形的法向量（通过前三个点）
x = p[0]*p[1]：计算两个法向量的叉积
!(x^x)：如果叉积的模长为0（两平面平行）
平行且不重合则无交集，输出"NO"

步骤1：确定顶点相对于另一平面的位置
计算每个顶点相对于另一个多边形所在平面的位置
o[i]：顶点i在平面的哪一侧（+1、0、-1）
步骤2：找到与另一平面相交的边
当相邻两点在平面两侧时，边与平面相交
步骤3：计算交点参数
计算多边形边与另一多边形所在平面的交点
使用参数方程计算交点在线段上的位置

按交点参数排序
扫描线算法统计交集情况
s和t：统计两个多边形的交集情况
如果存在交集，输出"YES"，否则输出"NO"

2. a[t^1][0]
另一个多边形的第一个顶点坐标
3. p[t^1]
另一个多边形的法向量
4. a[t][i]-a[t^1][0]
向量：从另一个多边形的第一个顶点指向当前多边形第i个顶点
5. (a[t][i]-a[t^1][0])^p[t^1]
向量点积运算
根据点积公式：u·v = |u||v|cos(θ)
这里是计算从另一多边形起点到当前顶点的向量与另一多边形法向量的点积

第一个元素：交点在交线上的参数值
第二个元素：{t, o[i]-o[i+1]}，表示多边形索引和方向信息
1. x = p[0]*p[1]
x 是两个多边形法向量的叉积
这给出了两个平面的交线方向向量
2. (a[t][i]^x) 和 ((a[t][i+1]-a[t][i])^x)
这些是点积运算，得到在交线方向上的投影值
(a[t][i]^x)：顶点i在交线方向上的投影
(a[t][i+1]-a[t][i])^x：边向量在交线方向上的投影
3. (p[t^1]^(a[t][i]-a[t^1][0]))
这是多边形t的顶点i到多边形t^1上某点的向量与多边形t^1法向量的点积
表示顶点i到多边形t^1所在平面的距离（带符号）
4. (p[t^1]^(a[t][i]-a[t][i+1]))
这是边向量 (a[t][i]-a[t][i+1]) 与多边形t^1法向量的点积
表示边的方向在法向量方向上的投影
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ld long double
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+7;
struct node { ll x, y, z; } a[2][N], p[2], x;
node operator-(const node &a, const node &b) {
    return {a.x-b.x, a.y-b.y, a.z-b.z};
}
node operator*(const node &a, const node &b) {
    return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
}
ll operator^(const node &a, const node &b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
int read() { int x; cin >> x; return x; }
int sgn(ll x) { return x < 0 ? -1 : x ? 1 : 0; }

int n[2], o[N], s, t;
vector<pair<ld, ii>> v;
int main() {
    fast;
    for (int t = 0; t < 2; ++t) {
        n[t] = read();
        for (int i = 0; i < n[t]; ++i) a[t][i] = {read(), read(), read()};
        a[t][n[t]] = a[t][0], p[t] = (a[t][1]-a[t][0])*(a[t][2]-a[t][0]);
    }
    if (x = p[0]*p[1], !(x^x)) return !puts("NO");//同时完成两件事：输出 "NO" 并返回 0
    for (int t = 0; t < 2; ++t) {
        for (int i = 0; i <= n[t]; ++i) o[i] = sgn((a[t][i]-a[t^1][0])^p[t^1]);
        for (int i = 0; i < n[t]; ++i)
            if (o[i]^o[i+1])
                v.push_back({(a[t][i]^x)+((a[t][i+1]-a[t][i])^x)*
                    (ld)(p[t^1]^(a[t][i]-a[t^1][0]))/(p[t^1]^(a[t][i]-a[t][i+1])),
                {t, o[i]-o[i+1]}});
    }
    ranges::sort(v);
    for (auto x : v)
        x.second.first ? s += t*x.second.second : t += x.second.second;
    puts(s ? "YES" : "NO");
    return 0;
}