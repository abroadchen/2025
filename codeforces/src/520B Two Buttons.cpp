//
// Created by Psy.C on 2026/3/1.
//
/**
逆向思维，从 m 反推到 n：
当 m 是奇数时，说明它是由 m-1 得来的，所以 m-- 并增加一步
当 m 是偶数时，说明它可能是由 m/2 乘以2得来的，所以 m/=2 并增加一步
最后当 m <= n 时，只需要做 n-m 次加法操作即可
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
int main() {
    fast;
    cin >> n >> m;
    int ans = 0;//操作步数
    for (; m > n; m >>= 1, ++ans)
        if (m&1) ++m, ++ans;
    cout << ans + n - m << '\n';
    return 0;
}