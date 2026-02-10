//
// Created by Psy.C on 2026/2/10.
//
/**
[f(n)]   = [1 -1] * [f(n-1)]
[f(n-1)]   [1  0]   [f(n-2)]

[f(n)] = A^(n-2) * [f(2)] = A^(n-2) * [y]
[f(n-1)] [f(1)] [x]

时间复杂度：O(log n)，矩阵快速幂
空间复杂度：O(1)，只使用常数空间
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
#define N 2
using namespace std;

struct node {
    ll mat[N][N];
    node operator*(const node& a) const {
        node ans{};
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                ans.mat[i][j] = 0;
                for (int k = 0; k < N; ++k)
                    ans.mat[i][j] = (ans.mat[i][j] + mat[i][k] * a.mat[k][j] % mod) % mod;
            }
        return ans;
    }
};

node ksm(node a, ll b) {
    node ans{};
    memset(ans.mat, 0, sizeof(ans.mat));
    for (int i = 0; i < N; ++i) ans.mat[i][i] = 1;
    while (b) {
        if (b&1) ans = ans * a;
        b >>= 1;
        a = a * a;
    }
    return ans;
}

//数列的前两项
ll x, y, n;//要求解的位置

int main() {
    fast;
    cin >> x >> y;
    node a{}; cin >> n;
    a.mat[0][0] = 1; a.mat[0][1] = -1; a.mat[1][0] = 1; a.mat[1][1] = 0;
    if (n == 1) cout << (x % mod + mod) % mod << '\n';
    else if (n == 2) cout << (y % mod + mod) % mod << '\n';
    else {
        a = ksm(a, n - 2);//转移矩阵的(n-2)次幂
        const ll ans = (((a.mat[0][0]*y + a.mat[0][1]*x)%mod)+mod)%mod;
        cout << ans << '\n';
    }
    return 0;
}