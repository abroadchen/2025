//
// Created by Psy.C on 2026/4/16.
//
///时间复杂度为O(w³ log c)，其中w³来自矩阵乘法，log c来自快速幂
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 105, mod = 1e6+3;

ll w;
struct node {
    ll a[N][N];//矩阵元素数组
    ll* operator[](ll x) { return a[x]; }//通过索引访问矩阵行
    node operator*(node o) const {//矩阵乘法
        node t{};
        for (int i = 0; i <= w; ++i)
            for (int j = 0; j <= w; ++j)
                for (int k = 0; k <= w; ++k)
                    (t[i][j] += a[i][k]*o[k][j]) %= mod;
        return t;
    }
} ans, a;//矩阵变量

void ksm(ll b) {//ans = ans * a^b
    while (b) {
        if (b&1) ans = ans*a;
        a = a*a;
        b >>= 1;
    }
}

ll c, h, res;
int main() {
    fast;
    cin >> c >> w >> h; ans[0][0] = 1;
    for (int i = 0; i <= w; ++i)
        a[i][0] = 1, a[i][i+1] = h;//对角线下一位置
    ksm(c);//a^c并乘以ans
    for (int i = 0; i <= w; ++i)
        (res += ans[0][i]) %= mod;
    cout << res;
    return 0;
}