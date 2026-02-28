//
// Created by Psy.C on 2026/2/28.
//
/**
n：输入数量
x：幂次

M.a[0][j] = c[j+1]：第0行存储转移系数（各种数字的个数）
M.a[0][N-1] = 1：常数项
M.a[i][i-1] = 1：表示状态转移关系（前一个状态转移到当前状态）
M.a[N-1][N-1] = 1：常数项的转移
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101, mod = 1e9+7;

struct node {
    int a[N][N]{};
    node() { memset(a, 0, sizeof(a)); }
    void init() {
        for (int i = 0; i < N; ++i) a[i][i] = 1;//单位矩阵
    }
    node operator*(const node& o) const {//矩阵乘法：b = this × o
        node b;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k)
                    b.a[i][j] = (b.a[i][j]+1ll*a[i][k]*o.a[k][j])%mod;
        return b;
    }
    node operator^(int o) const {//矩阵的x次幂
        node b; b.init();//结果矩阵（初始为单位矩阵）
        node x = *this;//当前的底数矩阵
        while (o) {
            if (o&1) b = b * x;
            x = x * x;
            o >>= 1;
        }
        return b;
    }
} M;

int n, x, c[N];//计数数组
int main() {
    fast;
    cin >> n >> x;
    for (int i = 1, t; i <= n; ++i) {
        cin >> t; c[t]++;//每个数字的出现次数
    }
    for (int j = 0; j < N-1; ++j) M.a[0][j] = c[j+1];
    M.a[0][N-1] = 1;
    for (int i = 1; i < N-1; ++i) M.a[i][i-1] = 1;
    M.a[N-1][N-1] = 1;
    auto y = M^x;
    cout << (y.a[0][0] + y.a[0][N-1])%mod << '\n';
    return 0;
}