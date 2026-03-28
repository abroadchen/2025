//
// Created by Psy.C on 2026/3/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 27;
int n, a[N];
map<int, bool> mp;///某个数字是否已被使用
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    ll ans = 0;
    for (int i = n; i >= 1; --i) {
        int t = a[i];
        //从当前值开始向下寻找，直到找到一个未被使用的数字或降到0
        while (t > 0 && mp[t]) t--;
        if (t > 0) {//如果找到了可用的正数
            ans += 1ll*t;//将该数字加到答案中
            mp[t] = true;//标记这个数字已被使用
        }
    }
    cout << ans << '\n';
    return 0;
}