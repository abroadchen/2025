//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
由于 s[1]==s[n]，两端是同一种字符。
t = 从开头数，连续等于该字符的个数。
w = 从末尾数，连续等于该字符的个数。
结果为 (t+1)*(w+1)。
直观解释：这种情形下，允许在"开头这块 t 个"和"末尾这块 w 个"各选一个切分点（含不切，即可以不选），形成 (t+1) 和 (w+1)。乘积代表选择数。模 mod 输出
t = 开头连续 = s[1] 的个数。
w = 末尾连续 = s[n] 的个数。
结果为 t+w+1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define per(i,n) for (int i=n; i>=1; i--)
#define ll long long
using namespace std;

constexpr int mod = 998244353;
int n;
string s;
int main() {
    fast;
    cin >> n >> s; s = ' ' + s;
    if (s[1] == s[n]) {
        ll t = 0, w = 0;
        rep(i,n) { if (s[i] == s[1]) t++; else break; }
        per(i,n) { if (s[i] == s[1]) w++; else break; }
        cout << (t+1)*(w+1)%mod;
    } else {
        ll t = 0, w = 0;
        rep(i,n) { if (s[i] == s[1]) t++; else break; }
        per(i,n) { if (s[i] == s[n]) w++; else break; }
        cout << (t+w+1)%mod;
    }
    return 0;
}