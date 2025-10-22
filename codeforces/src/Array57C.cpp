//
// Created by Psy.C on 2025/10/22.
//
/*
*fac[N]: 存储阶乘值
inv_fac[N]: 存储阶乘的模逆元
inv[N]: 存储数字的模逆元
 *
*定义加法函数add：执行模加运算，如果结果大于等于mod则减去mod
定义乘法函数mul：执行模乘运算，先转为long long防止溢出，再对mod取模
 *
 *使用递推公式计算2到N-1的模逆元：inv[i] = mod - (mod/i) * inv[mod%i] % mod
 *
*fac[i] = i * fac[i-1] (即i!)
inv_fac[i] = inv[i] * inv_fac[i-1] (即1/i!)
 *
*组合数计算函数C(n,r) = n!/(r!(n-r)!)
使用预计算的阶乘和阶乘逆元来快速计算组合数
如果r>n则返回0
 *
 *计算答案：2 * C(2n-1, n-1) - n，结果对mod取模
 *
 */
#include <ios>
#include <iostream>
#define mod 1000000007
using namespace std;

typedef long long ll;
const int N = 2e5+3;
int fac[N], inv_fac[N], inv[N];

int add(int a, int b) { if ((a += b) >= mod) a -= mod; return a; }
int mul(int a, int b) { return 1ll * a * b % mod; }

void init() {
    inv[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = mod - mul(mod / i, inv[mod % i]);
    fac[0] = inv_fac[0] = 1;
    for (int i = 1; i < N; ++i) {
        fac[i] = mul(i, fac[i-1]);
        inv_fac[i] = mul(inv[i], inv_fac[i-1]);
    }
}

int ncr(int n, int r) {
    if (r > n) return 0;
    return mul(fac[n], mul(inv_fac[n - r], inv_fac[r]));
}

void solve() {
    int n; cin >> n;
    int ans = add(mul(2, ncr(2 * n - 1, n - 1)), mod - n);
    cout << ans << '\n';
}


int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    init(), solve();
    return 0;
}