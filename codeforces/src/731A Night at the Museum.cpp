//
// Created by Psy.C on 2026/4/26.
//
/**
直线距离：从字符t到字符s[i]的顺时针距离
环形距离：绕一圈回到起点的距离
res += ...: 将当前步长累加到结果中
t = s[i]: 将当前位置更新为当前字符
O(n)，其中n是字符串长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 107;
char s[N], t = 'a';
int main() {
    fast;
    cin >> s;
    int res = 0;
    for (int i = 0; s[i]; ++i)
        res += min(max(t, s[i]) - min(t, s[i]),
            min(t, s[i]) + 26 - max(t, s[i])), t = s[i];
    cout << res << '\n';
    return 0;
}