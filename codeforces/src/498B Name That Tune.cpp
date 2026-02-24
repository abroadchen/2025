//
// Created by Psy.C on 2026/2/23.
//
/**
p[i]: 第i个项目的成功概率（转换为小数）
pw[i]: (1-p[i])^(t[i]-1)，连续失败t[i]-1次的概率
pw1[i]: pw[i] * p[i]，恰好在第t[i]次成功的概率
pw2[i]: pw[i] * (1-p[i])，前t[i]-1次失败且第t[i]次也失败的概率

f[now][j]: 考虑前i个项目，恰好使用j个单位时间的概率
考虑第i个项目：
不做第i个项目：f[now][j-1]*(1.-p[i])
做第i个项目：f[lst][j-1]*p[i]

f[lst][j-t[i]]*pw[i]: 在j-t[i]时间内完成其他项目，然后第i个项目连续失败t[i]-1次再成功
f[lst][(j-1)-(t[i]-1)]*pw1[i]: 修正项1
f[lst][j-1-t[i]]*pw2[i]: 修正项2

O(n*q)，其中n是项目数，q是时间限制

 */
#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar()) if (ch == '-') f = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    return x * f;
}

constexpr int N = 5001;
int n, q, t[N];
double p[N], pw[N], pw1[N], pw2[N], f[2][N], ans;
int main() {
    n = read(); q = read();
    for (int i = 1; i <= n; ++i) {
        p[i] = 1.*read()/100.; t[i] = read();
        pw[i] = pow(1. - p[i], t[i] - 1);
        pw1[i] = pw[i] * p[i];
        pw2[i] = pw[i] * (1. - p[i]);
    }
    f[0][0] = 1;
    for (int i = 1, now=1, lst = 0; i <= n; ++i) {
        for (int j = 1; j <= q; ++j) {
            f[now][j] = f[now][j-1]*(1.-p[i]) + f[lst][j-1]*p[i];
            if (j >= t[i] + 1)
                f[now][j] += f[lst][j-t[i]]*pw[i] - f[lst][(j-1)-(t[i]-1)]*pw1[i] -
                    f[lst][j-1-t[i]]*pw2[i];
            else if (j == t[i])
                f[now][j] += f[lst][j-t[i]]*pw[i] - f[lst][(j-1)-(t[i]-1)]*pw1[i];
            ans += f[now][j];
        }
        now ^= 1;
        lst ^= 1;
        f[now][0] = 0;
    }
    printf("%.9lf\n", ans);
    return 0;
}