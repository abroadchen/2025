//
// Created by Psy.C on 2026/9/18.
//
/**
N 取谐音 114514（OIIP 文化梗），用于存缩放倍数 x。
f[41][M]：DP 表。第一维是"用了几个缩放倍数"，第二维是照片的宽（以某个目标横轴为轴）。
f[i][j] 表示：用了前 i 个倍数后，宽恰好为 j 时，高能达到的最大值（在 w/b 轴上的值）。
inf = 1e9 表示不可行
用最少的倍数，把照片（h 宽 × w 高）放大成至少 a×b 的目标尺寸（在指定摆放方向）。
f[i][j]：用前 i 个倍数，横向（宽）恰好放大到 j时，纵向（高）能放大到的最大值。
初始化：用 0 个倍数时，宽 = min(a, h)（若原宽 h 已超目标 a，直接截成 a），高 = min(b, w)（同理）。
转移分两种：
横着乘 j * x[i]：把当前宽 j 乘上第 i 个倍数，新宽截到 a；高不变（因为横向放大），取 max(f[i-1][j]) 然后 min 到 b。
纵着乘：宽不变 j，高乘 x[i]，即 f[i-1][j]*x[i]，min 到 b。
两者都取 max（取更大的高）、并 cap 到 b（高不能超过目标 b，因为超过即可截断视为已达标）。
最终若某层 f[i][a] == b（宽达到 a 且高达到 b），说明用 i 个倍数就满足，返回 i（最少的倍数个数）‍。
这个 DP 是 01 背包式的：每个倍数最多用一次，用来在宽或高上放大。
读入：目标 a×b，原图 h×w，以及 n 个可用倍数 t。
sort 排序，然后从大到小收集所有 > 1 的倍数到 x[]（倍数 1 无意义，跳过）。从大到小排是因为大的倍数放大效率高，贪心地先用大的。
cnt = min(cnt, 40)：只取最大的前 40 个倍数——因为倍数递增时，放大到目标通常不需要很多个，40 足够（指数增长，2^40 巨大）。
分两种情况：
get(a,b,h,w)：照片不旋转（宽 h→a，高 w→b）。
get(a,b,w,h)：照片旋转 90°（宽 w→a，高 h→b）。
取两者的最小值。
若返回 inf（不可行），输出 -1；否则输出最少用几个倍数。
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 114514, M = 1e5+5, inf = 1e9;

int f[41][M], cnt, x[N];
int get(int a, int b, int h, int w) {
    memset(f, 0, sizeof f);
    f[0][min(a, h)] = min(b, w);
    for (int i = 1; i <= cnt; ++i)
        for (int j = 1; j <= a; ++j) {
            f[i][min(a, j*x[i])] = min(max(f[i][min(a, j*x[i])],
                f[i-1][j]), b);
            f[i][j] = min(max(f[i][j], f[i-1][j]*x[i]), b);
        }
    for (int i = 0; i <= cnt; ++i)
        if (f[i][a] == b) return i;
    return inf;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, t[N];
signed main() {
    int a, b, h, w; a = rd(), b = rd(), h = rd(), w = rd(), n = rd();
    for (int i = 1; i <= n; ++i) t[i] = rd();
    sort(t+1, t+n+1);
    for (int i = n; i >= 1; --i)
        if (t[i] > 1) x[++cnt] = t[i];
    cnt = min(cnt, 40ll);
    int ans = min(get(a, b, h, w), get(a, b, w, h));
    if (ans == inf) write(-1); else write(ans);
    return 0;
}