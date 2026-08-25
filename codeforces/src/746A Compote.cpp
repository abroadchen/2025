//
// Created by Psy.C on 2026/5/26.
//
/**
i ≤ a（基础单位不能超过a）
2*i ≤ b（双倍单位不能超过b）
4*i ≤ c（四倍单位不能超过c）
目标是最大化i + 2*i + 4*i = 7*i
实际上是在寻找满足约束条件的最大i值，然后输出7*i
ans = min(a, min(b/2, c/4)) * 7
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c;
int main() {
    fast;
    cin >> a >> b >> c;
    int ans = 0;
    for (int i = 1; i <= a; ++i) {
        if (b >= 2*i && c >= 4*i)
            ans = max(ans, i+2*i+4*i);
    }
    cout << ans << '\n';
    return 0;
}