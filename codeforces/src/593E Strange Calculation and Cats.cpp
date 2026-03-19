//
// Created by Psy.C on 2026/3/19.
//
/**
int n{}, m{}：矩阵的行数和列数（默认初始化为0）
mat[N][N]{}：矩阵元素（默认初始化为0）

设置单位矩阵的尺寸
构造单位矩阵（对角线为1）
设置转移矩阵mv的尺寸
构造转移矩阵mv，表示网格中每个位置可以转移到相邻位置
(i-1)*m+j：将二维坐标(i,j)转换为一维索引
设置转移关系：当前位置可以转移到自身以及四个相邻位置（上下左右）
t：状态矩阵，表示当前状态分布
lst = 1：记录上一次的时间
auto it = ksm(mv, tim - lst)：计算从上次操作到现在的时间间隔内的转移
t = t*it; lst = tim：更新状态矩阵，记录当前时间
if (op == 1)：查询操作，输出位置(x,y)的状态值
else if (op == 2)：删除操作，将位置(x,y)及其转移关系设为0
else：恢复操作，将位置(x,y)及其转移关系恢复为1

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;
constexpr int N = 25, mod = 1e9+7;

struct node {
    int n{}, m{}, mat[N][N]{};
    node() { memset(mat, 0, sizeof(mat)); }
    node operator*(node x) const {
        node y; y.n = n, y.m = m;
        rep(i,n) rep(j,m) rep(k,x.m)
            (y.mat[i][k] += mat[i][j]*x.mat[j][k]%mod) %= mod;
        return y;
    }
} t, mv, I;

node ksm(node x, int y) {
    node ans = I;
    while (y) {
        if (y&1) ans = ans * x;
        x = x * x;
        y >>= 1;
    }
    return ans;
}

int n, m, q;
signed main() {
    fast;
    cin >> n >> m >> q; I.n = n*m, I.m = n*m;
    rep(i,n*m) I.mat[i][i] = 1;
    mv.n = n*m, mv.m = n*m;
    rep(i,n) rep(j,m) {
        mv.mat[(i-1)*m+j][(i-1)*m+j] = 1;
        if (j != 1) mv.mat[(i-1)*m+j-1][(i-1)*m+j] = 1;
        if (j != m) mv.mat[(i-1)*m+j+1][(i-1)*m+j] = 1;
        if (i != 1) mv.mat[(i-2)*m+j][(i-1)*m+j] = 1;
        if (i != n) mv.mat[i*m+j][(i-1)*m+j] = 1;
    }
    t.n = 1, t.m = n*m, t.mat[1][1] = 1;
    int lst = 1;
    while (q--) {
        int op, x, y, tim; cin >> op >> x >> y >> tim;
        auto it = ksm(mv, tim - lst); t = t*it; lst = tim;
        if (op == 1) cout << t.mat[1][(x-1)*m+y] << '\n';
        else if (op == 2) {
            t.mat[1][(x-1)*m+y] = 0;
            mv.mat[(x-1)*m+y][(x-1)*m+y] = 0;
            if (y != 1) mv.mat[(x-1)*m+y-1][(x-1)*m+y] = 0;
            if (y != m) mv.mat[(x-1)*m+y+1][(x-1)*m+y] = 0;
            if (x != 1) mv.mat[(x-2)*m+y][(x-1)*m+y] = 0;
            if (x != n) mv.mat[x*m+y][(x-1)*m+y] = 0;
        } else {
            mv.mat[(x-1)*m+y][(x-1)*m+y] = 1;
            if (y != 1) mv.mat[(x-1)*m+y-1][(x-1)*m+y] = 1;
            if (y != m) mv.mat[(x-1)*m+y+1][(x-1)*m+y] = 1;
            if (x != 1) mv.mat[(x-2)*m+y][(x-1)*m+y] = 1;
            if (x != n) mv.mat[x*m+y][(x-1)*m+y] = 1;
        }
    }
    return 0;
}