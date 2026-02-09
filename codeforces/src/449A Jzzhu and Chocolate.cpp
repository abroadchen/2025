//
// Created by Psy.C on 2026/2/9.
//
/**
生成候选值：O(√n)
枚举候选值：O(√n)
总体：O(√n)

A[i][j] = ⌊n/(i*j)⌋
第k小元素
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, k;
vector<ll> v;

int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i*i <= n; ++i) {
        v.push_back(n/i); v.push_back(i);
    }
    ll ans = -1;
    for (const ll i : v) {//遍历所有候选的⌊n/i⌋值
        const ll t = i, x = n/t; ll rt = k - (x - 1);//剩余位置数
        if (rt < 0) rt = 0;
        if (rt > m - 1) continue;
        if (const ll y = rt + 1; t * (m/y) > ans) ans = t * (m/y);
    }
    cout << ans << '\n';
    return 0;
}