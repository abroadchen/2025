//
// Created by Psy.C on 2025/11/9.
//
/*
*定义三维向量结构体：
包含x, y, z三个坐标分量
提供带参数的构造函数和默认构造函数
同时定义了两个全局变量：a（初始位置）和v（速度向量）

*求解二次方程 at² + bt + c = 0：
计算判别式 d = b² - 4ac
如果d < 0（无实数解），将t1和t2设为无穷大
否则计算两个解：t1（较小解）和t2（较大解）
 *
*计算碰撞时间的函数：
a：移动球体的初始位置
b：静止球体的位置
v：移动球体的速度
r：两球半径之和
基于物理公式建立方程：|(a + v*t) - b|² = r²
展开后得到二次方程，调用eq求解
只考虑未来的碰撞（t ≥ 0），更新最小碰撞时间
 *
*处理n个障碍物：
读取第i个障碍物的位置t和半径r2
调用solve计算与主球体的碰撞时间（半径相加）
读取该障碍物的m个卫星球
对每个卫星球，计算与主球体的碰撞时间
 *
*如果没有碰撞（ans仍为无穷大），输出-1
否则输出最早碰撞时间，保留20位小数
 */
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

typedef long long ll;
typedef unsigned int ul;
const double inf = 1e9;

struct  vec {
    ll x, y, z;
    vec(ll x, ll y, ll z) : x(x), y(y), z(z) {}
    vec() = default;
}a, v;

vec operator+(const vec& a, const vec& b) { return vec(a.x+b.x, a.y+b.y, a.z+b.z); }
vec operator-(const vec& a, const vec& b) { return vec(a.x-b.x, a.y-b.y, a.z-b.z); }
ll operator*(const vec& a, const vec& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

void eq(ll a, ll b, ll c, double& t1, double& t2) {
    ll d = b * b - 4 * a * c;
    if (d < 0) { t1 = inf; t2 = inf; }
    double t = sqrt(double(d));
    t1 = (-b - t) / (2 * a);
    t2 = (-b + t) / (2 * a);
}

double ans = inf;
void solve(const vec& a, const vec& b, const vec& v, ll r) {
    double t1, t2;
    eq(v * v, (a - b) * v * 2, (a - b) * (a - b) - r * r, t1, t2);
    if (t2 < 0) return;
    if (t2 >= 0) ans = min(ans, max(t1, double(0)));
}

int main() {
    scanf("%lld%lld%lld", &a.x, &a.y, &a.z);
    scanf("%lld%lld%lld", &v.x, &v.y, &v.z);
    ll r; scanf("%lld", &r);
    ul n; scanf("%u", &n);
    for (ul i = 1; i <= n; ++i) {
        vec t; scanf("%lld%lld%lld", &t.x, &t.y, &t.z);
        ll r2; scanf("%lld", &r2);
        solve(a, t, v, r + r2);
        ul m; scanf("%u", &m);
        for (ul j = 1; j <= m; ++j) {
            vec p; scanf("%lld%lld%lld", &p.x, &p.y, &p.z);
            solve(a, t + p, v, r);
        }
    }
    if (ans >= inf - 1) printf("-1\n");
    else printf("%.20lf\n", ans);
    return 0;
}