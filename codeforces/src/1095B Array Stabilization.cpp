//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
n == 2：只有两个点，去掉任意一个后只剩 1 个点，跨度 = 0，输出 0。
n > 2：只剩两个候选方案——
去掉最右端（a[n-1]）：剩余跨度 = a[n-2] - a[0]（最大变成 a[n-2]）。
去掉最左端（a[0]）：剩余跨度 = a[n-1] - a[1]（最小变成 a[1]）。
取两者较小值为答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

constexpr int N = 1e5+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    sort(a, a+n);
    if (n == 2) cout << "0\n";
    else cout << min(a[n-2]-a[0],a[n-1]-a[1]) << '\n';
    return 0;
}