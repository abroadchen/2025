//
// Created by Psy.C on 2026/4/16.
//
///时间复杂度为O(n³log k)，其中n³来自矩阵乘法，log k来自快速幂
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 105, mod = 1e9+7;

struct node { ll a[N][N]; } p, q;//矩阵变量

int n;//矩阵大小
node mul(const node &a, const node &b) {
    node c{};//结果矩阵
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            c.a[i][j] = 0;
            for (int k = 1; k <= n; ++k)
                (c.a[i][j] += a.a[i][k] * b.a[k][j] % mod) %= mod;
        }
    return c;
}
node ksm(node a, ll k) {
    node ret(q);//单位矩阵q
    for (; k; k>>=1, a=mul(a, a))//二进制分解指数k
        if (k&1) ret = mul(ret, a);
    return ret;
}
ll check(ll x) {//x的二进制表示中1的个数
    int ret = 0;
    for (; x; x>>=1) ret += x&1;//右移x并累加最低位
    return ret%3 == 0;//返回1的个数是否能被3整除
}

ll k, a[N], ret;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) q.a[i][i] = 1;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            p.a[i][j] = check(a[i]^a[j]);//转移矩阵p
    auto ans = ksm(p, k-1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            (ret += ans.a[i][j]) %= mod;//累加结果矩阵ans的所有元素
    cout << ret << '\n';
    return 0;
}