//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
a[] 存原始元素，sum 记录总和，q[] 存 m 个询问
排序后 a 升序，那么第 q[i] 大的数就是升序后下标 n-q[i]+1 处的元素。
第 1 大 → 下标 n；第 2 大 → 下标 n-1；……第 q 大 → 下标 n-q+1（因为数组从 1 开始）。
每个询问直接输出 sum - 那个数，即去掉该数后的剩余和
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 3e5+10;

ll n, a[N], sum, m, q[N];
void solve() {
    cin >> n;
    rep(i,n) { cin >> a[i]; sum += a[i]; }
    cin >> m;
    rep(i,m) cin >> q[i];
    sort(a+1,a+1+n);
    rep(i,m) cout << sum-a[n-q[i]+1] << '\n';
}

int main() {
    fast;
    solve();
    return 0;
}