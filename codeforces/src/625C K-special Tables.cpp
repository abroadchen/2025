//
// Created by Psy.C on 2026/3/27.
//
/**
对每行的第1列到第k-1列进行填充
按顺序填入递增的数字（1, 2, 3, ...）
对每行的第k列到第n列进行填充
继续按顺序填入递增的数字（继续之前的序列）
计算第k列所有元素的和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 505;
int n, k, a[N][N];
int main() {
    fast;
    cin >> n >> k;
    int num = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= k-1; ++j)
            a[i][j] = ++num;
    for (int i = 1; i <= n; ++i)
        for (int j = k; j <= n; ++j)
            a[i][j] = ++num;
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans += a[i][k];
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}