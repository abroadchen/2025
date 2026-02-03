//
// Created by Psy.C on 2026/2/3.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1111111
#define rep(i,n) for (i=1; i<=(n); ++i)
using namespace std;


int main() {
    fast;
    int q[N], i; rep(i,1000) q[i*i] = 1;//标记了数组中的所有完全平方数
    int n, m, j = 0, k = 0, h = 0, flag = 0, x, y; cin >> n >> m;
    rep(i,100) {
        rep(j,100) {
            rep(k,100) {
                rep(h,100) {
                    const int a = (m-1)*i*i+j*j, b = (n-1)*i*i+k*k,
                    c = (m-1)*k*k+h*h, d = (n-1)*j*j+h*h;
                    if (q[a] && q[b] && q[c] && q[d]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag) break;
            }
            if (flag) break;
        }
        if (flag) break;
    }
    rep(x,n-1) {
        rep(y,m-1) cout << i << ' ';
        cout << j << '\n';//每行最后输出变量j的值
    }
    rep(x,m-1) cout << k << ' ';
    cout << h << '\n';
    return 0;
}