//
// Created by Psy.C on 2026/1/15.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int unsigned int
#define N 21
#define inf 2e9
#define rep(i,n) for (int i=0; i<n; ++i)
using namespace std;

void minn(int& x, const int y) { x = x < y ? x : y; }
int n;
struct node {
    int x[N][N]{};
    node() {
        rep(i,N) rep(j,N) x[i][j] = i == j ? 0 : inf;//对角线为0，其余为inf
    }
    node operator*(const node& o) const {
        node a{};
        rep(i,n+1) rep(j,n+1) {
            a.x[i][j] = inf;
            rep(k,n+1) minn(a.x[i][j], x[i][k] + o.x[k][j]);
        }
        return a;
    }
} A, B;

void get(const int a, const int b) {
    rep(i,n+1) {
        if (i < n) A.x[i+1][i] = a;//从i+1到i的边权为a
        if (i < n) A.x[i][i+1] = b;//从i到i+1的边权为b
    }
}

node pw(node x, int a) {
    node s{};
    rep(i,n+1) s.x[i][i] = 0;
    while (a) {
        if (a&1) s = s * x;
        x = x * x;
        a >>= 1;
    }
    return s;
}

signed main() {
    fast;
    int m, a[N], b[N]; cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    B = {};
    rep(i,n+1) rep(j,n+1) B.x[i][j] = i == j ? 0 : inf;
    rep(i,n) {
        rep(j,n+1) rep(k,n+1) A.x[j][k] = inf;
        get(a[i], b[i]);
        B = A * B;
    }
    B = pw(B, m);
    cout << B.x[0][0] << '\n';//从节点0到节点0经过m轮操作的最短路径
    return 0;
}