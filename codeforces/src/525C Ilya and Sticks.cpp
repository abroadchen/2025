//
// Created by Psy.C on 2026/3/2.
//
///时间复杂度：O(n log n)（主要是排序的复杂度）
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+1;
int n;
ll a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    ll l = 0, w = 0, ans = 0;
    for (int i = n - 1; i >= 1; --i) {
        if (a[i] == a[i-1] || a[i] == a[i-1] + 1) {//相邻元素是否相等或相差1
            if (l == 0) l = a[i-1], i--;//l还未赋值
            else if (w == 0) w = a[i-1], i--;
        }
        if (l != 0 && w != 0) {
            ans += l*w;
            l = 0; w = 0;
        }
    }
    cout << ans << '\n';
    return 0;
}