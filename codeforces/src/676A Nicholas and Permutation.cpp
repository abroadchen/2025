//
// Created by Psy.C on 2026/4/13.
//
/**
flag[N]: 记录每个值对应的位置索引

考虑四种情况：把1移到开头/结尾，把n移到开头/结尾
abs(n - flag[1]): 1到数组末尾的距离
flag[1]是值1的位置，n是数组末尾位置
这是把1移到末尾需要的移动距离
abs(flag[n] - 1): n到数组开头的距离
flag[n]是值n的位置，1是数组开头位置
这是把n移到开头需要的移动距离
abs(n - flag[n]): n到数组末尾的距离
flag[n]是值n的位置，n是数组末尾位置
这是把n移到末尾需要的移动距离
abs(flag[1] - 1): 1到数组开头的距离
flag[1]是值1的位置，1是数组开头位置
这是把1移到开头需要的移动距离

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, a[N], flag[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; flag[a[i]] = i;
    }
    int ans = 0;
    ans = max(ans, abs(n - flag[1]));
    ans = max(ans, abs(flag[n] - 1));
    ans = max(ans, abs(n - flag[n]));
    ans = max(ans, abs(flag[1] - 1));
    cout << ans << '\n';
    return 0;
}