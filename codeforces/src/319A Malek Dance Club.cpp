//
// Created by Psy.C on 2026/1/7.
//
/**
* 第一个循环：将二进制字符串转换为十进制数
ans *= 2: 将ans左移一位（乘以2）
ans += s[i] - '0': 加上当前位的数值（字符转数字）
ans %= mod: 对结果取模防止溢出
*第二个循环：将结果再乘以2^(n-1)
循环n-1次，每次ans乘以2并取模
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    const ll n = static_cast<ll>(s.size()); ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ans *= 2; ans += s[i] - '0'; ans %= mod;
    }
    for (int i = 1; i < n; ++i) { ans *= 2; ans %= mod; }
    cout << ans;
    return 0;
}