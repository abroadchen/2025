//
// Created by Psy.C on 2026/10/20.
//
/**
s[i] 存前缀和：s[0]=0，s[i] = a1 + a2 + ... + ai。
这样 s[i] 表示前 i 个数的和，s[n]-s[i] 表示第 i+1 到 n 个数的和
枚举所有可能的切分点 i（从 1 到 n-1，保证两段都非空）。
对每个切分点：
前一段取模：s[i] % p
后一段取模：(s[n]-s[i]) % p
把两者相加，取所有 i 中的最大值作为答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;

int n;
ll p, s[N], ans;
int main() {
    fast;
    cin >> n >> p;
    for (int i = 1; i <= n; ++i) cin >> s[i], s[i] += s[i-1];
    for (int i = 1; i < n; ++i)
        ans = max(ans, s[i]%p+(s[n]-s[i])%p);
    cout << ans << '\n';
    return 0;
}