//
// Created by Psy.C on 2026/3/13.
//
/**
求解ax + by = gcd(a,b)的整数解
比较两个长度为3的数组是否相等
用于验证哈希值是否匹配
N: 最大数组大小
M: 最大指数范围
mod: 模数
P: 三个不同的质数，用于多重哈希
n: 数据个数
a, b: 存储输入数据的数组
f: 三维数组，存储预计算的幂次结果

预计算所有a[i] * b[i]^j的结果
使用三个不同模数进行哈希以减少冲突
枚举第一个元素的所有可能指数
检查是否存在满足条件的指数使得所有元素相等
如果找到则输出结果并返回true

在预计算的幂次数组中查找给定值的指数
如果未找到返回-1

计算所有a[i]的最小值和所有b[i]的最大公约数
如果最大公约数为1则无解
预计算g2的幂次直到超过10^9
验证每个a[i]都能被g1整除
查找对应的幂次指数
如果找不到对应的指数则返回false
使用中国剩余定理的思想求解同余方程组
利用扩展欧几里得算法求解线性同余方程
调整B使其满足约束条件
输出最终结果

i: 第i个数据对 (a[i], b[i])
0: 指数为0的情况（即 b[i]^0 = 1）
j: 第j个哈希模数（使用3个不同的质数进行哈希）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

void ex_gcd(ll a, ll b, ll& x, ll& y) {
    if (!b) x = 1, y = 0;
    else ex_gcd(b, a % b, y, x), y -= a/b*x;
}

bool ok(ll *a, ll *b) {
    for (int i = 0; i < 3; ++i)
        if (a[i] != b[i]) return false;
    return true;
}

constexpr int N = 110, M = 900, mod = 1e9+7, P[3] = {
    mod, (int)1e9+9, 1004535809
};

ll ksm(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1, a=a*a%mod)
        if (b&1) res=res*a%mod;
    return res;
}

int n, a[N], b[N];
ll f[N][M+2][3];
bool out() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) f[i][0][j] = a[i] % P[j];
        for (int j = 1; j <= M; ++j)
            for (int k = 0; k < 3; ++k)
                f[i][j][k] = f[i][j-1][k]*b[i]%P[k];
    }
    for (int x = 0; x <= M; ++x) {
        int cnt = 0;
        for (int i = 2; i <= n; ++i)
            for (int j = 0; j <= M; ++j)
                if (ok(f[1][x], f[i][j])) {
                    cnt++; break;
                }
        if (cnt == n-1)
            return cout << f[1][x][0] << '\n', 1;
    }
    return false;
}

int m;
ll pw[M+2];
int get(int x) {
    for (int i = 0; i <= m; ++i)
        if (x == pw[i]) return i;
    return -1;
}

int q[N], p[N];
bool out2() {
    int g1 = a[1], g2 = b[1], w = 0;
    for (int i = 1; i <= n; ++i)
        g1 = min(g1, a[i]), g2 = __gcd(g2, b[i]);
    if (g2 == 1) return false;
    for (pw[0] = 1; pw[m]*g2 <= (int)1e9; pw[m+1] = pw[m]*g2, ++m) {}
    ll A = 1, B = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i]%g1) return false;
        int x = a[i]/g1;
        q[i] = get(x), p[i] = get(b[i]);
        if (p[i] == -1 || q[i] == -1) return false;
        w = max(w, q[i]);
    }
    for (int i = 1; i <= n; ++i) {
        ll ta = p[i], tb = q[i]%ta, g = __gcd(A, ta), x, y;
        if ((tb-B)%g) return false;
        ex_gcd(A, ta, x, y);
        __int128 s = B + (__int128)A*x*(tb-B)/g;
        A = A/__gcd(A, ta)*ta, B = (s%A+A)%A;
    }
    while (B < w) B += A;
    cout << g1*ksm(g2, B)%mod << '\n';
    return true;
}


int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    if (out()) return 0;
    if (out2()) return 0;
    cout << "-1\n";
    return 0;
}