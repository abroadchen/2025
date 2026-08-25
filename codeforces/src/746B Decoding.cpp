//
// Created by Psy.C on 2026/5/26.
//
/**
从倒数第二个字符开始向前遍历（索引为n-2）
每次递减2，即访问偶数索引位置的字符（从后往前）
输出这些字符
如果字符串长度为偶数，s.size()%2为0，!(s.size()%2)为1，从索引1开始
如果字符串长度为奇数，s.size()%2为1，!(s.size()%2)为0，从索引0开始
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
ll n;
string s;
int main() {
    fast;
    cin >> n >> s;
    for (ll i = n-2; i >= 0; i -= 2) cout << s[i];
    for (int i = !(s.size()%2); i < n; i += 2) cout << s[i];
    return 0;
}