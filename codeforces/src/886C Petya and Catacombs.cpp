//
// Created by Psy.C on 2026/10/8.
//
/**
读入 n 个数，a[x] 统计数值 x 出现的次数（桶计数）
遍历 1 到 n，若数值 i 从未出现（a[i] == 0），答案 ans 加一
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n, a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) { cin >> x; ++a[x]; }
    for (int i = 1; i <= n; ++i)
        if (!a[i]) ++ans;
    cout << ans << '\n';
    return 0;
}