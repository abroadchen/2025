//
// Created by Psy.C on 2026/10/22.
//
/**
读入 n 和长度为 n 的字符串（逐字符存到 a[1..n]，下标从 1 开始）
从 i=1 遍历到 n-2，检查每个长度为 3 的窗口 a[i], a[i+1], a[i+2]。
若三者相等且都为 'x'（即连续三个 x），则 ans++
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 105;

int n, i, ans;
char a[N];
int main() {
    fast;
    cin >> n;
    for (i = 1; i <= n; i++) cin >> a[i];
    for (i = 1; i <= n-2; i++)
        if (a[i] == a[i+1] && a[i+1] == a[i+2] && a[i] == 'x')
            ans++;
    cout << ans;
    return 0;
}