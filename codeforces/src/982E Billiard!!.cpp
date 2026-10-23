//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
gcd：递归求最大公约数。
exgcd(a,b,x,y)：求 a*x + b*y = gcd(a,b) 的一组整数解 x,y。用于后续解同余/线性丢番图方程
n, m：矩形边长。
x, y：初始位置坐标。
u, v：初始运动方向（-1 / 0 / 1，三个可能值，表示 x/y 方向的速度分量）
当 u==0：x 方向不动。若 x 不在边界（0 或 n），永远无法到达边界 → -1；否则 x 方向一直保持在边界 x，y 方向一直延伸到对面边界 (v>0)*m（若 v>0 输出 m，否则 0）。
对称地，v==0 时同样处理 y 方向静止的情况
将方向统一为"正方向"，负方向通过镜像坐标 x=n-x（或 y=m-y）来对称处理。
这样后续只需考虑"沿正方向、可反弹"的周期运动。
u,v 之后表示初始是否在边界偏向（0/1）
判断 (x-y) 是否能被 gcd(n,m) 整除——若不能，则无解（这是线性丢番图方程 n*a - m*b = x-y 有解的充要条件）。
用 exgcd(n, -m, a, b) 求 n*a + (-m)*b = gcd(n,m) 的一组解，再乘上 (x-y)/g 得到 n*a - m*b = x-y 的特解
校验符号，若等式不符则取相反解（确保 n*a - m*b = x-y 成立）
ra 取模到 [1, aa]（aa = m/g），得到满足条件的第一个正经解（a 的周期解），+1 保证为正
由 ra 反推 rb（满足 ra*n - rb*m = x-y）。
u ^= ra&1：若 ra 为奇数，x 坐标方向取反（命中某侧边界）。
v ^= rb&1：类似的 y 方向翻转。
最终输出落点边界坐标 (u ? n : 0) 与 (v ? m : 0)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

inline int gcd(int x, int y) { return y ? gcd(y, x%y) : x; }
inline void exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) x = 1, y = 0;
    else exgcd(b, a%b, y, x), y -= a/b*x;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}

int n, m, x, y, u, v;
int main() {
    fast;
    read(n, m, x, y, u, v);
    if (u == 0) return x==0||x==n?cout<<x<<' '<<(v>0)*m<<'\n':cout<<"-1\n", 0;
    if (v == 0) return y==0||y==m?cout<<(u>0)*n<<' '<<y<<'\n':cout<<"-1\n", 0;
    if (u < 0) u = 1, x = n-x; else u = 0;
    if (v < 0) v = 1, y = m-y; else v = 0;
    if ((x-y)%gcd(n,m)) return cout << "-1\n", 0;
    ll a, b, g = gcd(n, m), aa = m/g;
    exgcd(n,-m,a,b), a*=(x-y)/g, b*=(x-y)/g;
    if (x-y != a*n-b*m) a = -a, b = -b;
    ll ra = ((a+aa-1)%aa+aa)%aa+1, rb = (ra*n-x+y)/m;
    u ^= ra&1, v ^= rb&1;
    cout << (u?n:0) << ' ' << (v?m:0) << '\n';
    return 0;
}