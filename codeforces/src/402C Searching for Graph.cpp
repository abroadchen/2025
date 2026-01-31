//
// Created by Psy.C on 2026/1/31.
//
/**
* 如果(2*n + p)大于所有可能的数对数量C(n,2) = n*(n-1)/2，则只输出所有可能的数对
如果(2*n + p)较小，则只输出前m对
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int q; cin >> q;
    while (q--) {
        int n, p; cin >> n >> p;
        int m = (n<<1) + p;
        for (int a = 1; a <= n; ++a) {//所有可能的数对(a,b)
            for (int b = a + 1; b <= n; ++b) {
                cout << a << ' ' << b << '\n';
                m--;//每输出一对后，m减1
                if (m == 0) break;
            }
            if (m == 0) break;//防止进入下一次迭代
        }
    }
    return 0;
}