//
// Created by Psy.C on 2026/4/17.
//
/**
a[0][0] = mod-1：在模运算下，mod-1 ≡ -1 (mod mod)，这表示某种负数操作
a[0][1] = 1：单位系数
a[1][0] = 0：表示第二维对第一维无直接影响
a[1][1] = 2：第二维的放大倍数

q*(mod+1)/2%mod 是一种计算模意义下除以2的技巧写法，等价于
q * pow(2, mod-2, mod) % mod
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int mod = 1e9+7;
typedef ll M[2][2];///矩阵类型M为2×2的长整型数组
void mul(M& a, M b) {
    M c;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < 2; ++k)
                c[i][j] += a[i][k] * b[k][j];
        }
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            a[i][j] = c[i][j] % mod;//结果对mod取模
}

void ksm(M& a, ll k) {//矩阵的k次幂
    M b;
    b[0][0] = b[1][1] = 1; b[0][1] = b[1][0] = 0;//单位矩阵
    while (k) {
        if (k&1) mul(b, a);
        mul(a, a);
        k >>= 1;
    }
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            a[i][j] = b[i][j];//将结果赋回给a
}

int Pow(int a, ll b) {//a^b mod mod的数值快速幂
    int ans = 1;
    while (b) {
        if (b&1) ans = (ll)ans*a%mod;
        a = (ll)a*a%mod;
        b >>= 1;
    }
    return ans;
}

int k;
int main() {
    fast;
    //初始化转移矩阵
    cin >> k; M a; a[0][0] = mod-1, a[0][1] = 1, a[1][0] = 0, a[1][1] = 2;
    int p = 1, q = 2;//初始分子分母
    while (k--) {
        ll x; cin >> x;
        q = Pow(q, x);//分母进行x次幂运算
        ksm(a, x);//矩阵进行x次幂运算
    }
    p = a[0][1]; q = (ll)q*(mod+1)/2%mod;//更新分母
    p = (q - p + mod)%mod;//更新分子
    cout << p << '/' << q << '\n';
    return 0;
}