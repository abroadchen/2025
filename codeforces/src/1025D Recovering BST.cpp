//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
f[i][i][0] = f[i][i][1] = 1：长度为 1 的区间（单个点）两个状态都设为"可行"
因为一个单点本身就是一棵叶子子树，它的左右两侧都能作为对外连接端点
g[i][j] = a[i] 与 a[j] 的最大公约数。O(n²) 预处理，供后续快速判断
1	len	当前处理子问题的区间长度，从 2 到 n
2	l, r	区间左右端点，[l, r] 长度为 len
3	k	枚举分割点：把 [l,r] 分成 [l,k] 和 [k+1,r]
要使 [l,r] 可行，需要存在某分割点 k，同时满足：

左子区间 [l,k] 可行且其右端 a[k] 能对外（f[l][k][0]）
右子区间 [k+1,r] 可行且其左端 a[k+1] 能对外（f[k+1][r][1]）
这时把 [l,k] 和 [k+1,r] 通过根连接起来：

若 a[k] 与 a[r] 互质条件 g[k][r] > 1，则整棵子树右端暴露给父（f[l][r][0] = 1）。
若 a[k+1] 与 a[l] 互质条件 g[k+1][l] > 1，则整棵子树左端暴露给父（f[l][r][1] = 1）。
本质上是在枚举"哪一侧端点用来与外部父结点相连"，只有当相连端点的 gcd>1 才允许露出那一侧
遍历分割点 i，若存在 i 使得：
左整体区间 [1,i] 可行且其左端能对外连（f[1][i][1]）
右整体区间 [i,n] 可行且其右端能对外连（f[i][n][0]）
则整棵二叉树可构造，输出 Yes。
遍历完没有则输出 No
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 720;

int n, a[N], g[N][N];
bool f[N][N][2];
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> a[i]; f[i][i][0] = f[i][i][1] = 1; }
    rep(i,n) rep(j,n) g[i][j] = __gcd(a[i], a[j]);
    for (int len = 2; len <= n; ++len)//枚举区间长度
        for (int l = 1, r = len; r <= n; ++l, ++r)//枚举左端点，平移区间
            //枚举分割点（根的位置）
            for (int k = l; k < r; ++k) if (f[l][k][0] && f[k+1][r][1]) {//左右子区间都可行
                if (g[k][r] > 1) f[l][r][0] = 1;
                if (g[k+1][l] > 1) f[l][r][1] = 1;
            }
    rep(i,n) if (f[1][i][1] && f[i][n][0]) { cout << "Yes\n"; return 0; }
    cout << "No\n";
    return 0;
}