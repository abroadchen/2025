//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
封装二维点/向量，x,y 为整数（坐标）。
重载了 + - 一元负号，方便向量运算。
arc()：返回该向量的极角（atan2(y,x)），范围 (-π, π]，用于排序与判断方向
返回 x*(x-1)/2，即 C(x,2)，表示从 x 个东西里选 2 个的组合数
对每个非锚点 i，计算它相对锚点 x 的向量 a[i]-a[x]，并求极角 d[i]。

极角 <=0（下半平面，含 x 轴负方向）的点塞进 dn。
极角 >0（上半平面，含正 x 轴方向）的点塞进 up。
这样把所有点按极角大致分成上下两组
dn 和 up 分别按极角从小到大排序，然后对每个下半平面的点 dn[i]，用双指针 j 统计在这 pi + d[dn[i]]（即从 dn[i] 逆时针转到恰好超过半圆）范围内的"上半平面点"数量 ct。

这里计数的是：以锚点 x 为一个顶点的四边形的两对相对边的计数——通过极角半平面分裂，用「平凡的组合计数」把四边形结构拆解为 C(ct,2) × C(其余,2)，从而高效统计。

具体来说，f(ct)*f(n-2-ct) 表示：把其余 n-2 个点分成"某一侧半圆内 ct 个"和"外侧 n-2-ct 个"，各取 2 个，构成一个以 x 为顶点的四边形。
读入 n 个点。
对每个点 i，累加 calc(i)，即以每个点为锚点各统计一次。
输出总和。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define db double
#define ll long long
#define pi acos(-1)
using namespace std;

constexpr int N = 20200;

struct vec {
    int x, y;
    vec() = default;
    vec(int _x, int _y) : x(_x), y(_y) {}
    vec operator+(const vec &o) const { return {x + o.x, y + o.y}; }
    vec operator-(const vec &o) const { return {x - o.x, y - o.y}; }
    vec operator-() const { return {-x, -y}; }
    db arc() { return atan2(y, x); }
} a[N], b[N];

int f(int x) { return x*(x-1)/2; }

int n;
db d[N];
ll calc(int x) {
    vector<int> dn, up;
    rep(i,n) {
        if (i == x) continue;
        //从锚点 x 指向点 i
        b[i] = a[i] - a[x], d[i] = b[i].arc();//该向量的极角
        if (d[i] <= 0) dn.push_back(i);
        else up.push_back(i);
    }
    ll res = 0;
    ranges::sort(dn, [](int &u, int &v) { return d[u] < d[v]; });
    ranges::sort(up, [](int &u, int &v) { return d[u] < d[v]; });
    for (int i = 0, j = 0, ct = up.size(); i < dn.size(); i++) {
        while (j < up.size() && d[up[j]] <= pi+d[dn[i]]) j++, ct--;
        if (i) ct++;
        res += 1ll*f(ct)*f(n-2-ct);
    }
    return res;
}
void solve() {
    cin >> n; int x, y;
    rep(i,n) cin >> x >> y, a[i] = {x,y};
    ll res = 0;
    rep(i,n) res += calc(i);
    cout << res << '\n';
}


int main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}