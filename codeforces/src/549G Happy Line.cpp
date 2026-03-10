//
// Created by Psy.C on 2026/3/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n, a[N], b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], a[i] += i - n;//将数组元素与其索引相关联
    sort(a + 1, a + n + 1);
    for (int i = 2; i <= n; ++i)
        if (a[i] == a[i-1]) return cout << ":(", 0;//排序后的数组是否有重复元素
    for (int i = 0; i < n; ++i) b[n-i] = a[n-i] + i;//从a数组恢复到b数组
    for (int i = 1; i <= n; ++i) cout << b[i] << ' ';
    return 0;
}