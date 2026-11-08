//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
一个 2D 点/向量。
+、-、*标量：向量加减与数乘。
len()：向量长度（欧氏距离）
把 a1→a2 和 b1→b2 视作两段线段（或两段时刻轨迹）。
在参数 t ∈ [0,1] 处插值：
k1 = a1 + (a2-a1)*t：a 线上 t 时刻的位置；
k2 = b1 + (b2-b1)*t：b 线上 t 时刻的位置；
返回 k1 与 k2 的距离。即：这两条线段上参数同为 t 时的距离（同参数点间距离）
n：轨迹分段数；
d1：触发"计入"的距离阈值（更严格/更近的阈值）；
d2：重置状态用的距离阈值（更宽松/更远的阈值）；
a[i]、b[i]：第 i 时刻两条线的位置
ans：计数结果；
f：状态标志（1="可计数/空闲"，0="已计数/触发热寻期中"）
从第 2 段开始遍历每段区间 [i-1, i]。
当进入新的第 i 段时，若前一个节点两线距离 >(a[i-1]-b[i-1]).len() > d2（即两线在 i-1 点已经离得很远，超过较宽松的 d2），将 f 复位为 1（允许重新计数）。
作用：防止重复计数——只有当两线分开足够远（超过 d2）后，才允许下一次再计入"接近"。
换句话说：d1 是"多远就算接近一次"，d2 是"要分开多远才能再算第二次"
在 t ∈ [0,1] 上做三分查找，逼近 get(a[i], a[i-1], b[i], b[i-1], t) 的最小值点。
lm、rm：三等分点。
若 lm 处距离更小 → 最小值在 [l, rm]，把右边界 r 移到 rm；否则在 [lm, r]，l = lm。
因两线段间距函数关于 t 是凸的（二次函数极小），三分能收敛到最小点。
结束时 l 是能使间距最小的 t（近似）。
注意：get 传入的是 (a[i], a[i-1], b[i], b[i-1], ...)，即当前段的两个端点
若当前是可计数状态 f==1，且该段最小距离 ≤ d1（+eps 容忍浮点误差），则：
ans++：计一次"接近";
f = 0：锁定，防止同一段/连续段内重复计数。
之后要等两线分开超过 d2 才可能再计数
输出总共"接近/相遇"的次数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-9
#define db double
using namespace std;

struct node {
    db x, y;
    node(db u=0, db v=0) : x(u), y(v) {}
    node operator+(const node& o) const { return {x+o.x, y+o.y}; }
    node operator-(const node& o) const { return {x-o.x, y-o.y}; }
    node operator*(db o) const { return {x*o, y*o}; }
    db len() const { return sqrt(x*x + y*y); }
};

db get(node a1, node a2, node b1, node b2, db t) {
    node k1 = a1 + (a2 - a1)*t, k2 = b1 + (b2 - b1)*t;
    return (k1 - k2).len();
}

int n;
db d1, d2;
int main() {
    fast;
    cin >> n >> d1 >> d2;
    node a[n+1], b[n+1];
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y;
    int ans = 0, f = 1;
    for (int i = 2; i <= n; i++) {
        if (i > 2) if ((a[i-1]-b[i-1]).len() > d2) f = 1;
        db l = 0, r = 1;
        while (r - l > eps) {
            db lm = l + (r - l)/3, rm = r - (r - l)/3;
            if (get(a[i], a[i-1], b[i], b[i-1], lm) <
                get(a[i], a[i-1], b[i], b[i-1], rm)) r = rm;
            else l = lm;
        }
        if (f && get(a[i], a[i-1], b[i], b[i-1], l) <= d1 + eps) {
            ans++; f = 0;
        }
    }
    cout << ans << '\n';
    return 0;
}