//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 101;

int n, k, a[N], ans, mx;
int main() {
    fast;
    cin >> n >> k;
    rep(i,n) { cin >> a[i]; ans += a[i]; }
    rep(i,k) {//枚举 k 个余数类
        int l = ans;//从总和开始
        for (int j = i; j <= n; j += k) l -= a[j];//去掉下标≡i(mod k) 的那组，得"剩余和"
        if (l < 0) l = -l;//取绝对值
        if (l > mx) mx = l;//更新最大值
    }
    cout << mx << '\n';
    return 0;
}