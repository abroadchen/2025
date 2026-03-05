//
// Created by Psy.C on 2026/3/5.
//
/**
for (int i = 1; i <= n; i *= 10): i依次代表个位、十位、百位...（1, 10, 100, 1000...）
int res = n/i%10: 获取n在第i位上的数字
例如n=234, i=10时，n/i=23, 再%10得到3（十位数字）
ans = max(ans, res): 更新最大数位值
内层循环 for (int j = 1; j <= res; ++j) num[j] += i:
将当前位的权重值i加到num[1]到num[res]上
这是在统计每个数字在各个数位上出现的情况
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, ans, num[11];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i *= 10) {
        int res = n/i%10;
        ans = max(ans, res);
        for (int j = 1; j <= res; ++j)
            num[j] += i;
    }
    cout << ans << '\n';
    for (int i = ans; i; --i) cout << num[i] << ' ';
    if (ans) cout << '\n';
    return 0;
}