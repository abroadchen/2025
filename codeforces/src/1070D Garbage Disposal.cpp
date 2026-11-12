//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n, k, c;
int main() {
    fast;
    cin >> n >> k;
    ll ans = 0;
    for (int i = 0, x; i< n; i++) {
        cin >> x;
        if (c) {//当前组已有内容
            c += x;//累加进当前组
            if (c >= k) ans += c/k, c = c%k;//先把 c 里能凑出的"完整k"整组数计入 余数留作下一组开头
            else c = 0, ans++;//若还不够 k
        } else {//当前组是空的
            c += x;
            if (c >= k) ans += (ll)(c/k), c = c%k;
        }
    }
    if (c) ans++;//循环结束后若还有剩余，算最后一组
    cout << ans << '\n';
    return 0;
}