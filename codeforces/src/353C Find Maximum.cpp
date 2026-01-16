//
// Created by Psy.C on 2026/1/16.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    fast;
    int n, i, a[N], mx; cin >> n;
    for (i = 0; i < n; ++i) cin >> a[i];
    char s[N]; cin >> s;
    int sum = mx = 0;
    for (i = 0; i < n; ++i) {
        if (s[i] & 15) {//ASCII值的低4位是否非零
            if (mx > a[i]) {//当前最大值mx大于当前元素a[i]
                sum += mx;
                mx = a[i];//mx更新为a[i] 重新积累
            } else sum += a[i];
        } else mx += a[i];
    }
    cout << sum << '\n';
    return 0;
}