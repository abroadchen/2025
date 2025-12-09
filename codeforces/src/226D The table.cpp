//
// Created by Psy.C on 2025/12/9.
//
/*
*遍历每一行i：
初始化变量s为0
遍历该行的所有列j，计算该行的加权和：
如果x[i] ^ y[j]为真（异或，表示一个为true一个为false），则减去a[i][j]
否则加上a[i][j]
如果s小于0，则翻转x[i]的状态，并设置ok为false表示发生了改变
 *
*遍历每一列j：
初始化变量s为0
遍历该列的所有行i，计算该列的加权和：
如果x[i] ^ y[j]为真，则减去a[i][j]
否则加上a[i][j]
如果s小于0，则翻转y[j]的状态，并设置ok为false表示发生了改变
 *
 *如果本轮没有发生任何改变（ok仍为true），则退出循环
*输出数组x中标记为true的索引
输出数组y中标记为true的索引
 *
 *
*每轮：O(n×m)
轮数：取决于具体数据，最坏情况可能较多轮
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 105
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

void out(const bool *f, const int n) {
    int t = 0;
    rep(i,n) t += f[i]; cout << t << ' ';//统计f数组中true的个数
    rep(i,n) f[i] && cout << i << ' ';//输出所有为true的索引
    cout << '\n';
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    int a[N][N];
    rep(i,n) rep(j,m) cin >> a[i][j];
    bool x[N], y[N];//标记行和列的状态
    for (;;) {
        bool ok = true;//本轮没有发生改变
        rep(i,n) {
            int s = 0;
            rep(j,m) s += x[i] ^ y[j] ? -a[i][j] : a[i][j];
            if (s < 0) x[i] ^= 1, ok = false;
        }
        rep(j,m) {
            int s = 0;
            rep(i,n) s += x[i] ^ y[j] ? -a[i][j] : a[i][j];
            if (s < 0) y[j] ^= 1, ok = false;
        }
        if (ok) break;
    }
    out(x, n); out(y, m);
    return 0;
}