//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
用 (x, y) 表示平面上的一个点
operator<：让点可以作为 set 的关键字（自动去重、排序）。
operator-：两点相减得到向量。
operator*：计算叉积（cross product），用于判断向量方向/面积
a、b：线段的两个端点。
d：这条线段上"单位步长"的划分，用于数格点。
ln[N]：存放所有 N 条线段
标准辗转相除法
先保证 l <= r，再判断 x 是否落在区间 [l, r] 内（用于验证交点是否真的落在两条线段上，而非延长线上）
u/v 是线段在 x、y 方向的"单位增量"（因为 d 是格点步长）。
通过解两线段参数方程获取交点。
若两线平行（行列式 dw = 0）或交点不是整数坐标（up%dw != 0，即不能整除），则返回 {inf, inf} 标记"无格点交点"。
最终必须验证交点落在两条线段自身范围内，否则只算延长线上的交点，无效
把线段a转为：起点(x0,y0) + 参数k * 单位向量(u0,v0)，k∈[0, d]
线段b同理
解线性方程组：x0+k*u0 = x1+t*u1, y0+k*v0 = y1+t*v1

s[i]：线段i上与其它线段的所有交点；res：全部不同交点集合
读入每条线段的两个端点。
d = gcd(|Δx|, |Δy|)：线段在x、y方向变化量的最大公约数，等于线段上"单位格点步长"的数量。这是著名的 Pick 定理/GCD 格点计数基础：一条端点都是整点的线段，其内部格点数为 gcd(|Δx|, |Δy|) - 1
遍历每条线段 i，与所有其它线段 j 求交点；
有效的交点存入 s[i]（该线段上的交点集合）和 res（全局去重交点集合）；
ln[i].d + 1 = 这条线段上的总格点数（端点+内部格点，Pick定理）；
减去 s[i].size()（落在该线段上、被交到而需扣除重复计数的点）；
全部累加后，再加上全局不同交点数 res.size()
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e6+10, inf = 1e7;

struct node { ll x, y; };
bool operator<(const node& a, const node& b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
node operator-(const node& a, const node& b) { return {a.x-b.x, a.y-b.y}; }
ll operator*(const node& a, const node& b) { return (ll)a.x*b.y - (ll)a.y*b.x; }

struct line { node a, b; ll d; } ln[N];

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

bool in(ll x, ll l, ll r) {
    if (l > r) swap(l, r);
    return l <= x && x <= r;
}
node get(line a, line b) {
    ll x0 = a.a.x, y0 = a.a.y, u0 = (a.b.x-a.a.x)/a.d, v0 = (a.b.y-a.a.y)/a.d;
    ll x1 = b.a.x, y1 = b.a.y, u1 = (b.b.x-b.a.x)/b.d, v1 = (b.b.y-b.a.y)/b.d;
    ll up = (y1-y0)*u0-(x1-x0)*v0, dw = u1*v0-v1*u0;//行列式
    if (!dw || up%dw) return {inf, inf};//平行 或 非整数解 → 无格点交点
    //参数值（格点间可能简化的步数）
    ll k = up/dw, x = x1+k*u1, y = y1+k*v1;//得交点坐标
    //验证交点是否同时落在两条线段上
    if (in(x,a.a.x,a.b.x) && in(y,a.a.y,a.b.y) &&
        in(x,b.a.x,b.b.x) && in(y,b.a.y,b.b.y)) return {x, y};
    return {inf,inf};
}

int n;
set<node> s[N], res;
ll ans;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> ln[i].a.x >> ln[i].a.y >> ln[i].b.x >> ln[i].b.y;
        ln[i].d = gcd(abs(ln[i].a.x-ln[i].b.x), abs(ln[i].a.y-ln[i].b.y));
    }
    rep(i,n) {
        rep(j,n) if (i != j) {
            auto p = get(ln[i], ln[j]);//求线段i与j的交点
            if (p.x != inf) { s[i].insert(p); res.insert(p); }
        }
        ans += ln[i].d + 1 - s[i].size();//每条线段独立贡献
    }
    ans += res.size();//全局交点去重贡献
    cout << ans << '\n';
    return 0;
}