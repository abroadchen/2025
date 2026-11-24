//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
读入两矩阵，arr 保存逐位异或后的差异（1=需翻转）
分别统计每行 1 的个数（h[i]）和每列 1 的个数（l[j]）
若任意一行的 1 个数为奇数，或任意一列的 1 个数为奇数 → 不可行，输出 no。
全部为偶 → 可行，输出 yes
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

constexpr int N = 505;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int a, b, arr[N][N], h[N], l[N];
int main() {
    fast;
    read(a); read(b);
    rep(i,a) rep(j,b) read(arr[i][j]);
    rep(i,a) rep(j,b) { int t; read(t); arr[i][j] ^= t; }
    rep(i,a) rep(j,b) { h[i] += arr[i][j]; l[j] += arr[i][j]; }
    rep(i,a) if (h[i]&1) { cout << "no\n"; return 0; }
    rep(j,b) if (l[j]&1) { cout << "no\n"; return 0; }
    cout << "yes\n";
    return 0;
}