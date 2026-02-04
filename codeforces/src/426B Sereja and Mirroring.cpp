//
// Created by Psy.C on 2026/2/4.
//
/**
* 最坏情况：O(n×m×log n)
最好情况：O(n×m)
平均情况：取决于矩阵的对称性
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 105
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int a[N][N]{}, t = n;
    rep(i,n) rep(j,m) cin >> a[i][j];
    while (t%2 == 0) {//偶数时才检查对称性
        bool flag = false;
        rep(i,t>>1) {
            rep(j,m) if (a[i][j] != a[t-i+1][j]) {
                flag = true; break;
            }
            if (flag) break;
        }
        if (flag) break;
        t >>= 1;
    }
    cout << t;
    return 0;
}