//
// Created by Psy.C on 2026/10/19.
//
/**
用 complex<double> 复数做蝶形运算。n 是补零后长度（2 的幂），R[i] 是位逆序置换表，A/B 是工作数组
先按位逆序重排（R[i] 位反转）→ if (i<R[i]) swap 避免重复交换。
三层循环：最外层 i 是当前合并的块宽（1,2,4,...），中层 j 遍历每个块，内层 k 做蝶形合并。wn 是单位根，f=+1 正变换、f=-1 逆变换。
蝶形核心：t = a[j+i+k]*w; a[j+i+k]=a[j+k]-t; a[j+k]=a[j+k]+t;——把块分成左右两半交叉相加/相减
确定 n：卷积结果长度为 len = l1+l2-1，向上取到 2 的幂 n。++L 后 --L，得到 L = log2(n)-1，用于位逆序表。
构造位逆序表：R[i] = (R[i>>1]>>1)|((i&1)<<L)（递推位反转）。
把 a、b 填进复数数组 A、B。
正变换两个、逐点相乘、逆变换一个。
结果取实部除以 n 四舍五入（因为是整数卷积，FFT 复数结果的实部/复数点数是精确值）。
这里卷积 c[i] = sum_k a[k]*b[i-k]，用于字符串匹配：某个字符在 s 的位置和 t 的位置对齐时的匹配计数。
带路径压缩的并查集查找。注意这里 f 是传入的 f[i] 数组（每个位置 i 有自己的 6 元素字符并查集数组），f[i][x] 是位置 i 上字符 x 的祖先
这里字符集是 'a'..'f'（6 个字符，c1,c2∈[0,5]）‍，所以 'a'+c1 表示第 c1 个字符。

对给定的字符对 (c1,c2)：

v1[i]=1 当 s[i]=='a'+c1，否则 0。v2[j]=1 当 t[j]=='a'+c2，否则 0。
reverse(v2, v2+m)：反转模式串，这样卷积后 v1[i] = 文本位置 i 处与模式末位对齐时 s 中字符 c1 同时模式中字符 c2 的对齐匹配数。
卷积后 v1[i] 非零 ⇒ 在文本位置 i 对齐模式时，存在位置使得 s 中字符是 c1 且模式 t 中字符是 c2 对上。
位置 i 需要把字符 c1 和 c2 定为相同（可互相替换）‍。用该位置的并查集 f[i] 合并 c1、c2；若它们本来不属于同组，则合并并 ++ans[i]（ans[i] 表示该对齐需要的最少替换/合并次数，即不同字符类数量）
初始化每个位置 i 的 6 字符并查集 f[i][j]=j（自环）。
枚举 6×6 个字符对（跳过 i==j），对每对做一遍 solve —— 即对每个字符对单独做一次 FFT 卷积，找出哪些对齐位置需要把这个字符对合并。
最后输出 ans[i]，对每个可能完整对齐的位置 i（模式长度为 m，所以有效对齐起点从 m-1 到 n-1），输出该处需要的最少替换次数
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define db double
#define pi acos(-1)
#define cpx complex<double>
using namespace std;

constexpr int N = 125005*5;

namespace fft {
    int n, L, R[N], len;
    cpx A[N], B[N];
    void fft(cpx *a, int f) {
        rep(i,0,n-1) if (i < R[i]) swap(a[i],a[R[i]]);
        for (int i = 1; i < n; i <<= 1) {
            cpx wn(cos(pi/i), sin(f*pi/i)), t;
            for (int j = 0; j < n; j += i<<1) {
                cpx w(1, 0);
                for (int k = 0; k < i; ++k, w = w*wn) {
                    t = a[j+i+k]*w;
                    a[j+i+k] = a[j+k] - t;
                    a[j+k] = a[j+k] + t;
                }
            }
        }
    }
    void mul(int *a, int *b, int l1, int l2, int *c) {
        L = 0;
        for (n=1, len = l1+l2-1; n < len; n <<= 1) ++L;
        --L;
        rep(i,0,n-1) R[i] = (R[i>>1]>>1)|((i&1)<<L);
        fill_n(A, n, 0); fill_n(B, n, 0);
        rep(i,0,l1-1) A[i] = a[i];
        rep(i,0,l2-1) B[i] = b[i];
        fft(A, 1); fft(B, 1);
        rep(i,0,n-1) A[i] *= B[i];
        fft(A, -1);
        rep(i,0,l1-1) c[i] = (int)(A[i].real()/n+0.5);
    }
}

inline int find(int *f, int x) {
    if (x == f[x]) return x;
    return f[x] = find(f, f[x]);
}

int n, m, v1[N], v2[N], f[N][6], ans[N];
char s[N], t[N];
void solve(int c1, int c2) {
    rep(i,0,n-1) v1[i] = s[i] == 'a'+c1;//文本s中字符=='a'+c1的位置标记为1
    rep(i,0,m-1) v2[i] = t[i] == 'a'+c2;//模式t中字符=='a'+c2的位置标记为1
    reverse(v2, v2+m);//反转b以形成卷积
    fft::mul(v1, v2, n, m, v1);//卷积
    rep(i,0,n-1) {
        if (!v1[i]) continue;//该对齐位置没有c1-c2匹配
        if (find(f[i], c1) != find(f[i], c2))//在位置i，字符c1(c2对应的)需要合并
            f[i][f[i][c1]] = f[i][c2], ++ans[i];
    }
}

int main() {
    scanf("%s\n", s); n = strlen(s);
    scanf("%s\n", t); m = strlen(t);
    rep(i,0,n-1) rep(j,0,5) f[i][j] = j;
    rep(i,0,5) rep(j,0,5) {
        if (i == j) continue;
        solve(i, j);//枚举所有不同字符对 (c1,c2)
    }
    rep(i,m-1,n-1) cout << ans[i] << ' ';//输出每个有效对齐位置的答案
    cout << '\n';
    return 0;
}