//
// Created by Psy.C on 2026/10/14.
//
/**
状态含义：f[i][j] = 处理完前 i 关、共收集 j 个后剩余的最大能量（受上限约束）。
转移：f[i][j] 由上一状态 f[i-1][j-k] 通过"本关收集 k 个"转移而来：
花费 C[i]*k；
过关后回复 x；
新能量 = 上一状态剩余 − C[i]*k + x，取最大值。
前提判断 f[i-1][j-k]-C[i]*k >= 0：扣完花费后不能为负（能量不足则不可行）。
上限截断：转移全部 k 之后，对 f[i][j] 取 min(..., w + b*j)，因为总收集 j 个时能量上限就是 w + b*j
从总数大到小找第一个"第 n 关后可达到"的收集数 i（即 f[n][i] != -1），输出该最大可收集数。若一个都达不到则输出 0
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
#define int long long
using namespace std;

constexpr int N = 1e3+5;

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


int c[N], C[N], sum[N], f[N][N*10];
signed main() {
    int n = rd(), w = rd(), b = rd(), x = rd();
    rep(i,1,n) c[i] = rd();//每关可收集数
    rep(i,1,n) C[i] = rd();//每关单个花费
    rep(i,1,n) sum[i] = sum[i-1] + c[i];//前 i 关可收集总数前缀和
    //f[0][0]=w：处理 0 关、收集 0 个时剩余能量为初始 w。-1 表示该状态不可达
    memset(f, -1, sizeof(f)); f[0][0] = w;
    rep(i,1,n) rep(j,0,sum[i]) {
        int len = min(j, c[i]);//本关最多收集 min(已选总数 j, 本关上限 c[i]) 个
        rep(k,0,len) {//本关收集 k 个
            if (f[i-1][j-k]-C[i]*k >= 0) {//扣完本关花费后不能为负
                if (f[i-1][j-k] != -1)
                    f[i][j] = max(f[i-1][j-k]+x-C[i]*k, f[i][j]);//加上过关回复 x
            }
        }
        if (f[i][j] > w+b*j) f[i][j] = w+b*j;
    }
    per(i,sum[n],1) {
        if (f[n][i] != -1) {
            write(i), putchar('\n');
            return 0;
        }
    }
    write(0), putchar('\n');
    return 0;
}