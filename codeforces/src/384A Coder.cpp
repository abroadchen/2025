//
// Created by Psy.C on 2026/1/27.
//
/*
* 当 n 为偶数时：黑格和白格数量相等，各为 n²/2
当 n 为奇数时：一种颜色比另一种多1个，较多的颜色有 (n²+1)/2 个
O(n²)，需要输出整个 n×n 网格
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, ans = 0; cin >> n;
    n%2 == 0 ? ans = (n * n) >> 1 : ans = (n*n+1)>>1;
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i % 2 == j % 2) cout << 'C';//行号和列号的奇偶性相同
            else cout << '.';
        }
        cout << '\n';
    }
    return 0;
}