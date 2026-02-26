//
// Created by Psy.C on 2026/2/26.
//
/**
n, m: 矩阵的行数和列数
w[N][N]: 输入矩阵
a[N], b[N]: 分解后的行和列向量
sum: 用于GCD计算
e[N][N]: 误差矩阵
flag: 标志位
k: 结果值

根据第一行计算b[i] = w[0][i] - a[0]
根据第一列计算a[i] = w[i][0] - b[0]
初始化sum为a[0] + b[0] - w[0][0]（理论上应该为0）
计算每个位置的误差e[i][j] = |a[i] + b[j] - w[i][j]|
计算所有误差值的GCD

如果sum不为0（说明存在无法分解的情况）：
检查是否有sum <= w[i][j]的情况
如果有，则输出"NO"并退出
否则设置k = sum
如果sum为0（完美分解），设置k为所有w[i][j]+1的最大值

输出"YES"和k值
输出修正后的a数组（负值会被调整）
输出b数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (int i=0; i<(n); ++i)
using namespace std;
constexpr int N = 101;

ll gcd(const ll x, const ll y) {
    if (y > 0) return gcd(y, x%y);
    return x;
}

int n, m;
ll w[N][N], a[N], b[N], sum, e[N][N], flag, k;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) cin >> w[i][j]; a[0] = 0;
    rep(i,m) b[i] = w[0][i] - a[0];
    for (int i = 1; i < n; ++i) a[i] = w[i][0] - b[0];
    sum = a[0] + b[0] - w[0][0];
    rep(i,n) rep(j,m) {
        e[i][j] = abs(a[i] + b[j] - w[i][j]);
        sum = gcd(sum, e[i][j]);
    }
    if (sum != 0) {
        rep(i,n) rep(j,m) if (sum <= w[i][j]) {
            flag = 1;
            break;
        }
        if (flag) { cout << "NO\n"; return 0; }
        k = sum;
    } else {
        rep(i,n) rep(j,m) k = max(k, w[i][j]+1);
    }
    cout << "YES\n" << k << '\n';
    rep(i,n) {
        if (a[i] < 0) cout << w[i][0] - b[0] + k << ' ';
        else cout << a[i] << ' ';
    }
    cout << '\n';
    rep(i,m) cout << b[i] << ' ';
    return 0;
}