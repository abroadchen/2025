//
// Created by Psy.C on 2026/2/26.
//
/**
N = 201：字符串长度上限
M = 301：矩阵大小上限
mod = 10007：模数

m：字符串长度
vis[N][N][N]：记忆化标记数组
f[N][N][N]：DP状态数组
i：操作次数
l,r：当前处理的区间[left,right]
三种转移方式：
向左扩展（字符不相等）
向右扩展（字符不相等）
同时向两侧扩展（字符相等）
返回当前状态的方案数

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 201, M = 301, mod = 10007;

inline void add(int& x, const int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int len;///矩阵维度变量
struct node {
    int a[M][M]{};
    friend void operator*(node& x, const node& y) {//下三角矩阵
        node z;
        for (int i = 1; i <= len; ++i)
            for (int j = i; j <= len; ++j)
                for (int k = j; k <= len; ++k)
                    add(z.a[i][k], x.a[i][j]*y.a[j][k]%mod);
        x = z;
    }
    friend void operator^(node& x, const node& y) {//行向量乘法
        node z;
        for (int i = 1; i <= len; ++i)
            for (int j = 1; j <= len; ++j)
                add(z.a[1][i], x.a[1][j]*y.a[j][i]%mod);
        x = z;
    }
} A, B, _A, _B;

inline void ksm(int k) {//矩阵的k次幂
    while (k) {
        if (k&1) A*B;
        B*B;
        k >>= 1;
    }
}

int m, vis[N][N][N], f[N][N][N];
char s[N];
int dp(const int i, const int l, const int r) {
    if (i < 0 || l <= 0 || r > m || l > r) return 0;
    if (vis[i][l][r]) return f[i][l][r];
    vis[i][l][r] = 1;
    if (l == 1 && r == m) return f[i][l][r] = i == 0;//处理完整个字符串且操作次数为0
    if (l != 1 && s[l-1] != s[r]) add(f[i][l][r], dp(i-1,l-1,r));
    if (r != m && s[l] != s[r+1]) add(f[i][l][r], dp(i-1,l,r+1));
    if (l != 1 && s[l-1] == s[r+1]) add(f[i][l][r], dp(i,l-1,r+1));
    return f[i][l][r];
}

int n;///操作次数
int main() {
    scanf("%s%d", s+1, &n);
    m = strlen(s+1); len = m+(m+1)/2;
    for (int i = 0; i < m; ++i) {//每种操作次数下的基础转移值
        int t = 0;
        for (int j = 1; j <= m; ++j) {
            add(t, dp(i,j,j));
            if (j != m && s[j] == s[j+1])
                add(t, dp(i,j,j+1));
        }
        if (i) {
            B.a[i][i] = 24, B.a[i][len-(m-i+1)/2] = t;
            if (i == 1) A.a[1][1] = 1; else B.a[i-1][i] = 1;
        } else {//当 i = 0 时（初始情况）
            A.a[1][m] = t, B.a[len][len] = 26;//最后一个状态有26种字符选择
            for (int j = m; j < len; ++j)
                B.a[j][j] = 25, B.a[j][j+1] = 1;//到下一状态的转移系数
        }
    }
    _A = A, _B = B;//保存矩阵的初始状态
    ksm((n+m+1)/2);
    int ans = A.a[1][len];
    if (!((n+m)&1)) {//总长度为偶数
        printf("%d\n", ans);
        return 0;
    }
    ///
    A = _A, B = _B;//重置矩阵到备份时的状态
    for (int i = 0; i < m; ++i) {
        int t = 0;
        for (int j = 1; j <= m; ++j)
            if (j != m && s[j] == s[j+1])
                add(t, dp(i,j,j+1));
        if (i) B.a[i][len-(m-i+1)/2] = t;
        else A.a[1][m] = t, B.a[len][len] = 0;
    }
    ksm((n+m+1)/2);
    add(ans, mod-A.a[1][len]);
    printf("%d\n", ans);
    return 0;
}