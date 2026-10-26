//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
x, y 分别代表复数的实部和虚部。
复乘 (x+iy)(u+iv) = (xu - yv) + i(xv + yu)，对应最后一个运算符。
其余为实数的加减乘除，其中 operator* 和 operator/ 是与实数的运算（缩放）。
用自定结构而非 std::complex，通常是为了常数/移植性
type = 1：正变换；type = -1：逆变换。
第 1 步：按 rev[] 位逆序重排。
第 2 步：标准蝶形运算（迭代式 FFT），w0 是旋转因子 e^{± 2πi/(2mid)}。
逆变换最后除以 lim
v < x 记作"小"元素（设为 1），否则为 0。
m 遍历过程中累加成为当前前缀中 1 的个数。
f[k].x 统计：累加到前缀和为 k 的端点数。
循环结束后 m = 整个数组 1 的总数。补 f[0].x++ 是补上"空前缀和 0"这个起点。
关键思想：子区间 [l, r] 中 1 的个数 = 前缀和 s[r] - s[l-1]。所以"恰好 k 个 1 的区间数" = 前缀和相差 k 的（起点, 终点）对个数
卷积结果长度约 2m，升级到 2 的幂 lim。
位逆序表
f[i].x 为前缀和为 i 的端点数（实部）。
f[m-i].y 放前缀和为 m-i 的数量（虚部）。
ret += C(f[i].x, 2)：同一前缀和 i 的两个端点构成长度为 0（区间为空/1 个数为 0）的区间，贡献是组合数。这是 ans[0]（1 个数为 0 的区间数）
把复数
Z
=
A
+
i
B
Z=A+iB 平方：
Z
2
=
(
A
2
−
B
2
)
+
i
(
2
A
B
)
Z
2
 =(A
2
 −B
2
 )+i(2AB)
实部：
A
2
−
B
2
A
2
 −B
2
 （含自卷积差为 0）
虚部：
2
A
B
2AB（恰好是两组卷积 A 和 B 的交叉卷积，即前缀和差的分布）
利用这个复数技巧，一次 FFT 就同时算出了"差为 0"和"差非零"的两类结果，省一次 FFT
因为复数技巧使交叉卷积在虚部出现两次（
2
A
B
2AB），所以差非零的部分要除以 2 才是真实个数。
+0.5 后取整 = 四舍五入，抵消 FFT 浮点误差。
f[m-i].y：虚部在 y 分量上。为何下标是 m-i？因为上述镜像放置使得"差为 i（i 个 1）的端点数"落在虚部的第 m-i 个位置（卷积后交错）
m 是 1 的总个数。一个区间最多包含 m 个 1，所以恰好 k>m 个 1 的区间数恒为 0，直接输出 0
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pi acos(-1.)
#define db double
#define ll long long
using namespace std;

constexpr int N = 6e5+5;

struct vec {
    db x, y;
    vec(db _x=0, db _y=0) : x(_x), y(_y) {}
    vec operator-(const vec& o) const { return {x - o.x, y - o.y}; }
    vec operator+(const vec& o) const { return {x + o.x, y + o.y}; }
    vec operator*(const db &o) const { return {x * o, y * o}; }
    vec operator/(const db &o) const { return {x / o, y / o}; }
    vec operator*(const vec& o) const { return {x * o.x - y * o.y, x * o.y + y * o.x}; }
};
typedef vec clx;

int rev[N];
inline void fft(int lim, clx *arr, int type) {
    for (int i = 0; i < lim; i++)
        if (i < rev[i]) swap(arr[i], arr[rev[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        clx w0(cos(pi/mid), type*sin(pi/mid));
        for (int i = 0; i < lim; i += mid<<1) {
            clx w(1,0);
            for (int j = 0; j < mid; j++, w = w*w0) {
                clx x = arr[i+j], y = w*arr[i+j+mid];
                arr[i+j] = x + y, arr[i+j+mid] = x - y;
            }
        }
    }
    if (type == -1) {
        for (int i = 0; i < lim; i++)
            arr[i] = arr[i]/lim;
    }
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}


int n, x, m, lim(1);
clx f[N];
int main() {
    fast;
    read(n); read(x);
    for (int i = 1, v; i <= n; i++) {
        read(v);
        m += v < x ? 1 : 0;
        f[m].x++;
    }
    f[0].x++;
    while (lim <= m<<1) lim <<= 1;
    for (int i = 0; i < lim; i++) rev[i] = (rev[i>>1]>>1)|(i&1?lim>>1:0);
    ll ret = 0;//虚部放"镜像" C(cnt,2)：差为 0 的区间对数
    for (int i = 0; i <= m; i++) f[m-i].y = f[i].x, ret += 1ll*f[i].x*(f[i].x-1)/2;
    fft(lim, f, 1);
    for (int i = 0; i < lim; i++) f[i] = f[i]*f[i];
    fft(lim, f, -1);
    cout << ret << ' ';
    for (int i = 1; i <= m; i++) cout << (ll)(f[m-i].y/2.0+0.5) << ' ';
    for (int i = m+1; i <= n; i++) cout << 0 << " \n"[i==n];
    return 0;
}