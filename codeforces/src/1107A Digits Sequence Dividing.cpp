//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
只要 n 的值比 2 大就一定可以成功（分成两段：第一段是第一个数，第二段是剩下的所有数）。
当 n 的值刚好等于 2 时，就需要看 s
0
​
  和 s
1
​
  的数量关系了。
当 n 的值小于 2 时，肯定无法成功
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int q; cin >> q;
    while (q--) {
        int n; string s; cin >> n >> s;
        if (n < 2 || (n == 2 && s[1] <= s[0])) cout << "NO\n";
        else {
            cout << "YES\n" << 2 << '\n' << s[0] << ' ';
            for (int i = 1; i < n; i++) cout << s[i];
            cout << '\n';
        }
    }
    return 0;
}