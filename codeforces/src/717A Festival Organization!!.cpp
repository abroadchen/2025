//
// Created by Psy.C on 2026/4/21.
//
/**
add 规范化函数：确保结果在[0, mod)范围内
快速幂算法：计算x^k mod mod
(x1+y1√5)(x2+y2√5) = (x1x2+5y1y2) + (x1y2+x2y1)√5
自定义复数的快速幂
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 207, mod = 1e9+7;
int add(int x) {
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
    return x;
}
int ksm(int x, int k) {
    int ret = 1;
    while (k) {
        if (k&1) ret = 1ll*ret*x % mod;
        x = 1ll*x*x % mod;
        k >>= 1;
    }
    return ret;
}

struct node {
    int x, y;
    node operator+(const node& o) const {
        return {add(x+o.x), add(y+o.y)};
    }
    node operator-(const node& o) const {
        return {add(x-o.x), add(y-o.y)};
    }
    node operator*(const node& o) const {
        return {(1ll*x*o.x+1ll*y*o.y%mod*5)%mod,
            (1ll*x*o.y+1ll*y*o.x)%mod};
    }
} A[N], B[N], x1[N], x2[N], one;

node ksm(node x, int k) {
    node ret = one;
    while (k) {
        if (k&1) ret = ret*x;
        x = x*x;
        k >>= 1;
    }
    return ret;
}

int s[N][N], c[N][N], k;
void init() {
    s[0][0] = 1;
    for (int i = 1; i <= k; ++i)//第二类斯特林数
        for (int j = 1; j <= i; ++j)
            s[i][j] = (s[i-1][j-1] + 1ll*s[i-1][j]*(i-1)) % mod;
    for (int i = 0; i <= k; ++i) c[i][0] = 1;//组合数
    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= i; ++j)
            c[i][j] = add(c[i-1][j-1]+c[i-1][j]);
    one = node(1, 0);//单位元 (1+0√5)
    int tp = ksm(5, mod-2);//5的逆元
    //A=(0,1/5), B=(0,-1/5)
    A[1] = node(0, tp); B[1] = node(0, add(-tp));
    tp = ksm(2, mod-2); //2的逆元
    x1[1] = node(tp, tp);//x1=(1/2,1/2)
    x2[1] = node(tp, add(-tp));//x2=(1/2,-1/2)
    A[0] = B[0] = x1[0] = x2[0] = one;//初始化为单位元
    for (int i = 2; i <= k; ++i) A[i] = A[i-1]*A[1];//预计算A的幂
    for (int i = 2; i <= k; ++i) B[i] = B[i-1]*B[1];//预计算B的幂
    for (int i = 2; i <= k; ++i) x1[i] = x1[i-1]*x1[1];//预计算x1的幂
    for (int i = 2; i <= k; ++i) x2[i] = x2[i-1]*x2[1];//预计算x2的幂
}

///计算复数的逆元：利用共轭复数 (a+b√5)⁻¹ = (a-b√5)/(a²-5b²)
node inv(node x) {
    int tp = add((1ll*x.x*x.x - 1ll*x.y*x.y%mod*5)%mod);
    tp = ksm(tp, mod-2);
    return node(1ll*x.x*tp%mod, add(-1ll*x.y*tp%mod));
}

int tl, ans, l, r, len;
node calc(node x) {//等比数列求和：计算 ∑(i=l to r) x^i
    //如果x=1，则∑x^i = len
    if (x.x == 1 && x.y == 0) return node(tl, 0);
    //等比数列求和: x^l * (1-x^len) / (1-x)
    return ksm(x, l)*(one-ksm(x, len))*inv(one-x);
}

signed main() {
    cin >> k >> l >> r; l += 2; r += 2; init();
    len = r - l + 1; tl = len%mod;//区间长度
    for (int j = 0, fx=k&1?add(-1):1; j <= k; ++j, fx=add(-fx)) {
        int tp = 0;
        for (int t = 0; t <= j; ++t) {//枚举组合
            node d = calc(x1[t]*x2[j-t]);//计算等比数列和
            d = d*A[t]*B[j-t];//乘以系数
            tp = (tp + 1ll*c[j][t]*d.x) % mod;//累加到tp
        }
        ans = (ans + 1ll*s[k][j]*fx%mod*tp)%mod;//乘以斯特林数和符号
    }
    int ml = 1;
    for (int i = 2; i <= k; ++i) ml = 1ll*ml*i%mod;//计算k!
    ml = ksm(ml, mod-2);//k!的逆元
    ans = 1ll*ans*ml%mod;//除以k!
    cout << ans << '\n';
    return 0;
}