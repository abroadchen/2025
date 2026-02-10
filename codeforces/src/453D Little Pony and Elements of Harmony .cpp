//
// Created by Psy.C on 2026/2/10.
//
/**
e0[]（初始数据）和b[]（系数数组）

根据每个索引的二进制1的个数来选择b数组中的值
将a数组赋值给e数组
对e0和e数组分别进行正向FWT变换
计算e0[i] = e[i]^t * e0[i] mod p（这相当于在频域中进行幂运算和乘法）
对结果进行逆FWT变换

 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2000006
using namespace std;

__int128 get(__int128 a1) {//二进制中1的个数
    __int128 c1 = 0;
    while (a1 != 0) {
        c1 += a1 % 2;
        a1 /= 2;
    }
    return c1;
}

ll n, p;
void init(__int128 *f, const ll x) {//快速Walsh-Hadamard变换（FWT）
    for (int o = 2, k = 1; o <= n; o *= 2, k *= 2)
        for (int i = 0; i <= n - 1; i += o)
            for (int j = 0; j <= k - 1; ++j) {
                f[i+j] = (f[i+j] + f[i+j+k]) % p;
                f[i+j+k] = (f[i+j] - f[i+j+k] - f[i+j+k] + p*2) % p;
                f[i+j] %= p;
                f[i+j+k] %= p;
            }
    if (x == 0) {//逆变换（除以n）
        for (int i = 0; i <= n - 1; ++i) f[i] = f[i]/n;
    }
}

__int128 ksm(__int128 a1, ll b1) {
    __int128 c1 = 1;
    while (b1) {
        if (b1&1) c1 = c1 * a1 % p;
        a1 = a1 * a1 % p;
        b1 >>= 1;
    }
    return c1;
}

ll m, t, st;
__int128 e0[N], b[N], a[N], e[N];

int main() {
    fast;
    cin >> m >> t >> p; n = 1<<m; p = p*n;
    for (int i = 0; i <= n - 1; ++i) {
        cin >> st;
        e0[i] = st; e0[i] %= p;
    }
    for (int i = 0; i <= m; ++i) { cin >> st; b[i] = st; }
    for (int i = 0; i <= n - 1; ++i) a[i] = b[get(i)];
    for (int i = 0; i <= n - 1; ++i) e[i] = a[i];
    init(e0, 1); init(e, 1);
    for (int i = 0; i <= n - 1; ++i) e0[i] = ksm(e[i], t)*e0[i]%p;
    init(e0, 0);
    for (int i = 0; i <= n - 1; ++i)
        cout << (static_cast<ll>(e0[i]+p)%p) << '\n';
    return 0;
}