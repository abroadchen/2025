//
// Created by Psy.C on 2025/11/27.
//
/*
 *v[0] = 1，表示前缀和为0的情况出现1次
 *x: 当前前缀中'1'的个数（前缀和）
 *
*遍历字符串的每个字符
如果当前字符是'1'，增加前缀和计数x
*如果当前前缀和x大于等于k：
查找之前是否有前缀和为(x-k)的情况
如果有，则说明存在子串其'1'的个数恰好为k
将对应的计数加到结果中
 *将当前前缀和x的出现次数加1
 *时间复杂度：O(n) 空间复杂度：O(n)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

int main() {
    fast;
    ll k; string s; cin >> k >> s;
    const ll n = static_cast<int>(s.size());
    vector<ll> v(n + 1, 0); v[0] = 1;
    ll x = 0, res = 0;
    for (ll i = 0; i < n; ++i) {
        if (s[i] == '1') ++x;
        if (x >= k) res += v[x - k];
        ++v[x];
    }
    cout << res << '\n';
    return 0;
}