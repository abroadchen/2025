//
// Created by Psy.C on 2026/2/23.
//
/**
a[][]: 预处理的转移矩阵
s[][]: 后缀矩阵乘积 第i位从j开始的后缀矩阵乘积
p[][]: 前缀矩阵乘积 第i位前j个矩阵的乘积

将数字n转换为m进制表示
b[i] 存储第i位的数字

从高位到低位处理每一位
对于每一位的数字，依次乘以对应的转移矩阵
j 控制转移状态的循环
O(log_m(n) × m³)，其中矩阵乘法为O(m³)
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 31, mod = 1e9+7;
int m;
struct Matrix {
    int mat[N][N];

    Matrix operator*(const Matrix& a) const {
        Matrix res{};
        memset(res.mat, 0, sizeof res.mat);
        for (int i = 0; i <= m; ++i)
            for (int j = 0; j <= m; ++j)
                for (int k = 0; k <= m; ++k)
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * a.mat[k][j]) % mod;
        return res;
    }
} ans, a[N<<1][N], s[N<<1][N], p[N<<1][N];

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x<<1)+(x<<3)+(ch&15); ch = getchar(); }
    return x*f;
}

int n, b[N<<1];
signed main() {
    n = read(); m = read();
    int n2 = n, len = -1;
    while (n2) {
        len++;
        b[len] = n2 % m;
        n2 /= m;
    }
    len++;
    for (int i = 0; i <= m; ++i) ans.mat[0][i] = 1;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j <= m; ++j) a[i][0].mat[j][j] = 1;
        if (!i) {
            for (int j = 0; j < m; ++j) {//j: 第0位（最低位）填入的数字（0到m-1）
                a[i][j].mat[m][m] = 1;//在位置(m,m)设置1
                for (int k = 0; k < m; ++k) {
                    if (k != j) {
                        a[i][j].mat[k][k] = 1;
                        continue;
                    }
                    for (int l = 0; l <= m; ++l)
                        a[i][j].mat[k][l] = 1;
                }
            }
        } else {
            for (int j = 0; j < m; ++j) {
                if (!j) a[i][j] = s[i-1][0];
                else a[i][j] = s[i-1][j]*p[i-1][j-1];
            }
        }
        p[i][0] = a[i][0];
        for (int j = 1; j < m; ++j) p[i][j] = p[i][j-1]*a[i][j];
        s[i][m-1] = a[i][m-1];
        for (int j = m-2; j >= 0; --j) s[i][j] = a[i][j]*s[i][j+1];
    }
    int j = 0;
    for (int i = len-1; i >= 0; --i) {
        while (b[i]-- > 0) {
            ans = ans * a[i][j];
            j++;
            if (j == m) j = 0;
        }
    }
    cout << ans.mat[0][m] << '\n';
    return 0;
}