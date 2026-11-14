//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
当找到 1 0 1 时：

移除中间 0，把这个三元组压缩；
把 a[i+1]（第三个 1）置为 0，是为了阻止它再作为某个"101"模式的右端 1 被重复计数，保证每个 1 只参与一次计数。
这相当于"每遇到一个 101，就把最右边的 1 标记为已用"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 101;

int n, a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 2; i <= n-1; i++)
        if (a[i] == 0 && a[i-1] == 1 && a[i+1] == 1)
            ans++, a[i+1] = 0;
    cout << ans << '\n';
    return 0;
}