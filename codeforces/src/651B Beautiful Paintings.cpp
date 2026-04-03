//
// Created by Psy.C on 2026/4/2.
//
/**
n: 数组长度
a[N]: 输入数组
f[N]: 标记数组，记录某个位置是否已被配对
cnt: 配对计数器
外层循环遍历每个元素作为较小元素
内层循环寻找比a[i]大的最小未使用元素
a[i] < a[j]: 确保a[j]确实比a[i]大
!f[j]: 确保a[j]还未被配对
cnt++: 配对成功，计数器加1
f[j] = 1: 标记j位置元素已被使用
break: 找到第一个合适的元素后就停止内层循环
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;
int n, a[N], f[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (a[i] < a[j] && !f[j]) {
                cnt++; f[j] = 1;
                break;
            }
    cout << cnt;
    return 0;
}