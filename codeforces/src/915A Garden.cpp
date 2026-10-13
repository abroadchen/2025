//
// Created by Psy.C on 2026/10/13.
//
/**
从最大的 a[i] 开始（因为降序），找第一个能整除 k（k % a[i] == 0）的数，输出 k / a[i] 并立刻结束程序；若全部都不整除 k，则什么都不输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

bool cmp(int a, int b) { return a > b; }

int main() {
    fast;
    int n, k; cin >> n >> k;
    int a[n+1], i;
    for (i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1, cmp);
    for (i = 1; i <= n; ++i)
        if (k%a[i] == 0) {
            cout << k/a[i] << '\n';
            return 0;
        }
    return 0;
}