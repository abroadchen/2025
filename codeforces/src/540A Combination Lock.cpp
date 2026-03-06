//
// Created by Psy.C on 2026/3/5.
//
/**
for (int i = 0; i < n; ++i): 遍历字符串的每个位置
int t = abs(a[i] - b[i]): 计算第i位字符的ASCII差值的绝对值
由于题目处理的是数字字符('0'-'9')，所以a[i] - '0'和b[i] - '0'才是实际的数字值
if (t > 5) t = 10 - t: 这是关键逻辑，计算在环形数字(0-9)中两个数字的最小距离
ans += t: 累加每个位置的最小移动距离
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1001;
int n;
char a[N], b[N];
int main() {
    fast;
    cin >> n;
    int ans = 0;
    cin >> a >> b;
    for (int i = 0; i < n; ++i) {
        int t = abs(a[i] - b[i]);
        if (t > 5) t = 10 - t;
        ans += t;
    }
    cout << ans << '\n';
    return 0;
}