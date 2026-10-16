//
// Created by Psy.C on 2026/10/16.
//
/**
f(x)：把 x 的每一位非零数字相乘（0 位按 1 处理）。
g(x)：反复作用 f 直到结果小于 10（即数字根的多项式变体，称为 "digital root under product" 或 multiplicative digital root）。
题目要回答：[l, r] 内有多少个数满足 g(x) == k
对每一位数字取 x%10，max(1, 该位) 把 0 变成 1（0 不参与乘积）。
逐步乘积累，返回所有非零位数字的乘积
若 x 已是单个数字（<10），直接返回。
否则对 f(x) 递归，持续直到结果是一位数
N = 1e6，数组第二维开到 15（虽实际只需要 0..9，可能为了对齐或安全）。
a[i][j] = 在 [1, i]（注意数组从 1 计）范围内，满足 g(x) == j 的数的个数。
递推：新加一个数 i，若 g(i) == j 则在 a[i-1][j] 基础上 +1，否则继承前值。
a[0][0] = 1 作边界（可能作为 n=0 的占位，让查询 a[l-1][0] 不为 0 时的基）
区间 [l,r] 内 g==k 的数量 = a[r][k] - a[l-1][k]（前缀和相减）。
一次查询 O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e6+5;

int f(int x) {
    int ans = 1;
    while(x) { ans = ans*max(1, x%10); x/=10; }
    return ans;
}
int g(int x) {
    if (x < 10) return x;
    return g(f(x));
}

int a[N][15];
void init() {
    a[0][0] = 1;
    rep(i,1,N) rep(j,0,9) {
        if (j == g(i)) a[i][j] = a[i-1][j] + 1;
        else a[i][j] = a[i-1][j];
    }
}

void solve() {
    int l, r, k; cin >> l >> r >> k;
    cout << a[r][k] - a[l-1][k] << '\n';
}

int main() {
    fast;
    init();
    int q; cin >> q;
    while (q--) solve();
    return 0;
}