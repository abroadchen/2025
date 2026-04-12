//
// Created by Psy.C on 2026/4/11.
//
/**
通过与现有基底向量进行XOR来减少x，如果能减少值则进行
如果减少后的x非零，将其添加到基底并返回true
如果x经过减少后变为零，返回false

对于每对(a[i], b[i])，计算c[i] = a[i]^b[i]
将c[i]添加到XOR基底中
在res中累积所有a[i]值的XOR

尝试将res（所有a[i]的XOR）添加到基底中
如果成功（意味着res不能表示为基底中元素的XOR），输出"1/1"
否则，计算2^cnt - 1除以2^cnt作为概率/分数
1ll<<cnt计算2^cnt
输出(2^cnt - 1)/2^cnt
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5+5, M = 105;
int cnt;
ll d[M];
bool add(ll x) {
    for (int i = 1; i <= cnt+1; ++i) {
        if ((d[i]^x) < x) x = d[i]^x;
    }
    if (x) {
        d[++cnt] = x;
        return true;
    }
    return false;
}
int n;
ll a[N], b[N], c[N], res;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n+1; ++i) {
        cin >> a[i] >> b[i];
        c[i] = a[i]^b[i];
        add(c[i]);
        res ^= a[i];
    }
    if (add(res))  cout << "1/1\n";
    else {
        ll ans = 1ll<<cnt;
        cout << ans - 1 << '/' << ans << '\n';
    }
    return 0;
}