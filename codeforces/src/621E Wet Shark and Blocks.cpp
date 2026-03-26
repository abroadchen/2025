//
// Created by Psy.C on 2026/3/26.
//
/**
x：模数（在全局域定义，也作为矩阵大小）
n, m：矩阵行列数
a[N][N]：矩阵元素，初始化为0
构造n×m的矩阵
f为true时构造单位矩阵（对角线为1）
n：数字种类数
b：要选的数字个数
k：目标余数
A：转移矩阵
B：结果矩阵，初始化为单位矩阵
读入n个数字
对于当前数字v，从状态j转移到状态(j*10+v)%x
从单位矩阵B开始，对矩阵A进行b次幂运算
输出res[0][k]，即从状态0经过b次转移后到达状态k的方案数
时间复杂度：O(x³log b) 空间复杂度：O(x²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 105, mod = 1e9+7;

ll x;
struct node {
    ll n, m, a[N][N]{};
    node(ll x, ll y, bool f) {
        n = x, m = y;
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n && f; ++i) a[i][i] = 1;
    }
    node operator*(const node& o) const {
        node res(x, x, 0);
        for (int i = 0; i < x; ++i)
            for (int j = 0; j < x; ++j)
                for (int k = 0; k < x; ++k)
                    (res.a[i][j] += a[i][k]*o.a[k][j]%mod) %= mod;
        return res;
    }
    ll *operator[](ll x) { return a[x]; }
};

node ksm(const node &b, node a, ll k) {
    node ans = b;
    for (; k; k >>= 1, a=a*a)
        if (k&1) ans = ans*a;
    return ans;
}

ll n, b, k, v;
int main() {
    fast;
    cin >> n >> b >> k >> x;
    node A(n, n, 0), B(x, x, 0);
    for (int i = 0; i < x; ++i) B[i][i] = 1;
    for (int i = 0; i < n; ++i) {
        cin >> v;
        for (int j = 0; j < x; ++j)
            A[j][(j*10+v)%x]++;
    }
    node res = ksm(B, A, b);
    cout << res[0][k];
    return 0;
}