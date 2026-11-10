//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
把 a 和 b 都升序排序。
排序后 对应位置（第 k 小的 a 配第 k 小的 b）取 max，累加
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

ll n, sum, a[N], b[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i] >> b[i];
    sort(a+1, a+n+1); sort(b+1, b+n+1);
    rep(i,n) sum += max(a[i], b[i]);
    cout << sum + n;
    return 0;
}