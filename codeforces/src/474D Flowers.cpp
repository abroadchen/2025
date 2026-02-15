//
// Created by Psy.C on 2026/2/15.
//
/**
预处理复杂度: O(N)
单次查询复杂度: O(1)
总体复杂度: O(N + t)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100001
#define mod 1000000007
using namespace std;

int t, k, a[N], sum[N];

int main() {
    fast;
    cin >> t >> k;
    for (int i = 0; i < k; ++i) a[i] = 1;
    for (int i = k; i < N; ++i) {
        a[i] = a[i-1] + a[i-k];
        a[i] %= mod;
    }
    sum[0] = 0;
    for (int i = 1; i < N; ++i) {
        sum[i] = sum[i-1] + a[i];
        sum[i] %= mod;
    }
    for (int i = 0, a1, b; i < t; ++i) {
        cin >> a1 >> b;//查询区间
        cout << (sum[b] - sum[a1-1] + mod) % mod << '\n';
    }
    return 0;
}