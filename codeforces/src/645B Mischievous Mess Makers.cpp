//
// Created by Psy.C on 2026/4/1.
//
/**
n*(n-1)/2: 计算n个元素中任意两个元素的组合数（总配对数）
res*(res-1)/2: 计算res个有效元素中任意两个元素的组合数（有效配对数）
n*(n-1)/2-res*(res-1)/2: 计算受限制的配对数
时间复杂度：O(1)，空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m;
int main() {
    fast;
    cin >> n >> m;
    ll res = max(n-2*m, 0ll);
    cout << n*(n-1)/2-res*(res-1)/2 << '\n';
    return 0;
}