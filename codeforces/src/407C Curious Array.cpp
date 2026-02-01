//
// Created by Psy.C on 2026/2/1.
//
/**
* inv[i]：i! mod p（阶乘）
mul[i]：i!^(-1) mod p（阶乘的逆元）
 *C(a,b) = a!/(b!(a-b)!)
 *
*sy = k + r - l：计算组合数的上标
kx = r - l：计算组合数的下标
 *
 *
*两步恢复
每行内部做前缀和（横向）
每列做前缀和（纵向，从高维到低维）
 *
 *ans[i][j-1]：同一维度i，前一个位置j-1的累积值
 *ans[i-1][j]：低一维度i-1，相同位置j
 *
 *
*预处理：O(N)
查询处理：O(MK)，其中K是最大k值
恢复操作：O(MN)
总体：O(N + MK + MN)
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 200010
#define M 122
#define mod 1000000007
using namespace std;

int inv[N], mul[N];
int get(const int a, const int b) {
    return inv[a] * mul[a-b] % mod * mul[b] % mod;
}

signed main() {
    fast;
    int n, m, a[N]; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    inv[0] = inv[1] = mul[0] = mul[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = i*inv[i-1] % mod;
    for (int i = 2; i < N; ++i) mul[i] = mul[mod%i] * (mod - mod/i) % mod;//i的逆元
    for (int i = 2; i < N; ++i) mul[i] = mul[i-1] * mul[i] % mod;//修正mul数组，使其存储阶乘逆元 i阶乘的逆元
    int ans[M][N]={};
    for (int i = 1, l, r, k; i <= m; ++i) {
        cin >> l >> r >> k;
        ans[k+1][l]++;//在位置(l,k+1)进行差分标记
        const int sy = k + r - l, kx = r - l;
        for (int j = 0; j <= k; ++j)
            ans[j+1][r+1] = (ans[j+1][r+1] - get(sy-j, kx)) % mod;//对于每个j，减去相应的组合数贡献
    }
    for (int i = 101; i > 0; --i) {//从高维到低维
        for (int j = 1; j <= n; ++j) ans[i][j] = (ans[i][j] + ans[i][j-1]) % mod;
        for (int j = 1; j <= n; ++j) ans[i-1][j] = (ans[i-1][j] + ans[i][j]) % mod;
    }
    for (int i = 1; i <= n; ++i) cout << ((ans[0][i] + a[i])%mod + mod) % mod << ' ';
    return 0;
}