//
// Created by Psy.C on 2026/9/12.
//
/**
m1[d] = 第一个数组里数字 d 出现的次数；m2[d] 同理
对每个数字 i（1..5）：
(m1[i]+m2[i])%2 != 0：两个数组加起来该数字总数必须是偶数，否则两个数组总元素数 n 相同却无法两边分得一样多 → 无解，输出 -1。
ans += abs(m1[i]-m2[i])/2：每个"超出/不足"的数字，需要调整 abs(m1[i]-m2[i])/2 次跨越（把多余的移到另一边）。
cout << ans/2：因为一次交换可以同时修正两个数字的差额（比如数组1多一个 1、少一个 2，数组2相反，交换一次 1 和 2 就同时修好两边），所以实际交换次数 = 总差额的一半，即 ans/2
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

map<int, int> m1, m2;
int main() {
    fast;
    int n, s; cin >> n;
    for (int i = 0; i <= n-1; ++i) { cin >> s; m1[s]++; }
    for (int i = 0; i <= n-1; ++i) { cin >> s; m2[s]++; }
    int ans = 0;
    for (int i = 1; i <= 5; ++i) {
        if ((m1[i]+m2[i])%2 != 0) { cout << -1 << '\n'; return 0; }
        ans += abs(m1[i] - m2[i])/2;
    }
    cout << ans/2 << '\n';
    return 0;
}