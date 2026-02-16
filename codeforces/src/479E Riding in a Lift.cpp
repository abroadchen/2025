//
// Created by Psy.C on 2026/2/16.
//
/**
f[i]: 当前在位置i的方案数
g[i]: 下一步在位置i的方案数

f[(j+b-1)/2]: 从中点位置(j+b-1)/2转移到位置j的方案数

时间复杂度：
O(k × b)，其中k是步数，b是区间长度
空间复杂度：
O(b)，使用滚动数组优化
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int mod = 1e9+7;

ll n, a, b, k;
int main() {
    fast;
    cin >> n >> a >> b >> k;
    if (a > b) {//关于中点对称变换
        a = n + 1 - a;
        b = n + 1 - b;
    }
    vector<ll> f(b), g(b);//两个长度为b的数组
    f[a] = 1;//位置a的方案数为1
    for (int i = 0; i < k; ++i) {
        for (int j = 1; j < b; ++j) g[j] = (mod - f[j]) % mod;
        for (int j = 1; j < b; ++j) {
            f[j] += f[j-1]; f[j] %= mod;
        }
        for (int j = 1; j < b; ++j) {
            g[j] += f[(j+b-1)/2]; g[j] %= mod;
        }
        vector<ll> t = f; f = g; g = f;
    }
    ll tot = 0;
    for (int i = 1; i < b; ++i) {
        tot += f[i]; tot %= mod;
    }
    cout << tot << '\n';
    return 0;
}