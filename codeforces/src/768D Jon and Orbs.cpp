//
// Created by Psy.C on 2026/9/7.
//
/**
dp[i][j]：抽了正好 i 次，恰好集齐了 j 种不同奖品的概率。
初始化：dp[0][0] = 1，即抽 0 次、收集 0 种，概率为 1（唯一确定状态
抽到新品种：上一次是 (i-1) 次收集了 j-1 种，这次抽到还没拥有的那 k-(j-1)=k-j+1 种中的一种。概率为 (k-j+1)/k，贡献 dp[i-1][j-1] × (k-j+1)/k。
抽到已有的：上一次是 (i-1) 次收集了 j 种，这次又抽到已拥有的 j 种中的一种。概率为 j/k，贡献 dp[i-1][j] × j/k
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4+5, M = 1e3+5;

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

int k, q;
double dp[N][M];
int main() {
    fast;
    k = rd(); q = rd(); dp[0][0] = 1;
    for (int i = 1; i <= N-5; ++i)
        for (int j = 1; j <= k; ++j) {
            dp[i][j] += dp[i-1][j-1]*double(k-j+1)/double(k);
            dp[i][j] += dp[i-1][j]*double(j)/double(k);
        }
    while (q-->0) {
        double p = rd(), now = p/2000.;
        for (int i = 1; i <= N-5; ++i)
            if (dp[i][k] >= now) {
                write(i), puts("");
                break;
            }
    }
    return 0;
}