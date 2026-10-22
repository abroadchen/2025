//
// Created by Psy.C on 2026/10/22.
//
/**
operator+ / operator-：向量加、减。
operator*(pt, ld)：数乘，向量乘以标量。
operator*(pt, pt)：叉积 a.x*b.y - a.y*b.x（2D 叉积 = 有向面积的两倍）。
pang(pt)：返回向量的极角 atan2(y,x)（弧度）。
dist(pt)：向量模长（到原点的距离）。
pt a[N]：顶点数组；pt mas：质心（重心）；pt pos：当前"基准位置"点。
int p：当前旋转基准顶点下标（配合全局 q 使用）
a[x]-a[p]：顶点 x 相对于基准顶点 p 的向量。
mas-a[p]：质心相对于 p 的向量。
pang(...)：求这两个向量的极角。
ang = 1.5*pi + pang(a[x]-a[p]) - pang(mas-a[p])：
1.5*pi（即 270°）。
这是在构造一个旋转角：使多边形绕 p 旋转，使得旋转后质心 mas 的位置被转到 pos 方向。
pt{cos(ang), sin(ang)}：旋转单位向量（角度 ang 的方向）。
* dist(a[x]-a[p])：把 x 相对 p 的向量长度乘上该单位向量，得到旋转加缩放后的相对向量。
+ pos：平移到 pos 处。
也就是说：query(x) 输出顶点 x 经过"以 p 为中心、旋转某个角度使质心对齐到 pos"的变换后的坐标。这里同时包含了旋转（角度）和平移（+pos），长度不变（dist 只取模长）
read(n), read(m)：读入顶点数 n 和操作数 m（注意这里 main 里又声明了 int n, m, q——遮蔽了全局变量名，后面用到的是局部 q，全局 p 仍用全局的）。
读入 n 个顶点坐标 a[i]。
a[0] = a[n]：把下标 0 指向最后一个顶点，便于环形遍历（计算面积时需要 a[i-1]）
第一句 area += a[i-1]*a[i]：a[i-1] 与 a[i] 的叉积累加，得到2 倍有向面积（多边形面积公式，area = Σ a[i-1]×a[i]，最终除以 2 才是面积，这里直接当 2S 用）。
从 i>=3 开始，累加质心项：
(a[i]+a[i-1]+a[1])：三角形三个顶点之和（第 1、i-1、i 顶点组成的三角形）。
*(1.0/3.0)：除以 3（三角形质心平均）。
*(a[1]*a[i-1]+a[i-1]*a[i]+a[i]*a[1])：这个值是三角形有向面积的 2 倍（三个叉积之和），作为权重。
这是多边形质心的加权求和公式：质心 = Σ (三角形质心 × 三角形面积) / 总面积。
循环结束后 mas = mas * (1.0/area)：除以面积（这里 area 是 2S，对应上面权重也是 2 倍有向面积，两者抵消，得到正确质心坐标）。这个公式在几何上是对的（分子分母的 2 相互抵消
初始化 p=1, q=2（初始旋转基准为顶点 1、当前"被移动的顶点"为 2）。flg 记录是否已发生过翻转（还没翻转时顶点就是原始坐标）。
循环处理 m 次操作：
① op==1（旋转/翻转操作）：

读入 x, y（题意：把顶点 x 翻转到顶点 y 的位置之类）。
首次翻转初始化（flg==false）：
若 x==1：pos = a[2], swap(p,q)（交换基准），否则 pos = a[1]。
置 flg=true。这一步是把初始 pos（基准位置）设置为当前要翻转的锚点对应位置。
之后（已是翻转状态）‍：
若 x == q：直接 q = y（要移动的顶点正好是当前 q，只需更新 q）。
否则：pos = query(q)（把当前 q 顶点用变换后的坐标作为新的基准 pos），swap(p,q)，然后 q = y。
这套操作在维护"翻转中心/基准"随操作移动后的新状态。
② op==2（查询顶点 x 的坐标）：

若还没翻转过（flg==false）：直接输出原坐标 a[x]。
否则：pt t = query(x)，输出经当前变换后的坐标（10 位小数）
 */
#include <bits/stdc++.h>
#define ld long double
#define pi acos(-1)
using namespace std;

constexpr int N = 2e5+5;

struct pt { ld x, y; };
pt operator+(pt a, pt b) { return {a.x+b.x, a.y+b.y}; }
pt operator-(pt a, pt b) { return {a.x-b.x, a.y-b.y}; }
pt operator*(pt a, ld b) { return {a.x*b, a.y*b}; }
ld operator*(pt a, pt b) { return a.x*b.y - a.y*b.x; }
ld pang(pt a) { return atan2(a.y, a.x); }
ld dist(pt a) { return sqrt(a.x*a.x + a.y*a.y); }
pt a[N], mas, pos;
int p;
pt query(int x) {
    ld ang = 1.5*pi+pang(a[x]-a[p])-pang(mas-a[p]);
    return pos + pt{cos(ang), sin(ang)}*dist(a[x]-a[p]);
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) (x*=10) += ch&15;
    if (f) x = -x;
}

int n, m, q;
ld area;
int main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++) read(a[i].x), read(a[i].y);
    a[0] = a[n];
    for (int i = 1; i <= n; i++) {
        area += a[i-1]*a[i];
        if (i >= 3)
            mas = mas + (a[i]+a[i-1]+a[1])*(1.0/3.0)*(a[1]*a[i-1]+a[i-1]*a[i]+a[i]*a[1]);
    }
    mas = mas*(1.0/area); p = 1, q = 2;
    bool flg = false;
    for (int i = 1, op, x, y; i <= m; i++) {
        read(op);
        if (op == 1) {
            read(x), read(y);
            if (flg == false) {
                if (x == 1) pos = a[2], swap(p, q); else pos = a[1];
                flg = true;
            }
            if (x == q) q = y;
            else {
                pos = query(q);
                swap(p, q);
                q = y;
            }
        } else {
            read(x);
            if (flg == false) printf("%.10Lf %.10Lf\n", a[x].x, a[x].y);
            else {
                pt t = query(x);
                printf("%.10Lf %.10Lf\n", t.x, t.y);
            }
        }
    }
    return 0;
}