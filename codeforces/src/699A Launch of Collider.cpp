//
// Created by Psy.C on 2026/4/17.
//
/**
n: 物体数量
num[i]: 第i个物体的初始位置
a[i]: 第i个物体的运动方向 ('L' 或 'R')
num[i+1] - num[i]：两物体之间的初始距离
两物体相向运动，相对速度是2，所以相遇时间为距离/2
时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5, inf = 1e9;
int n, num[N];
char a[N];
int main() {
    cin >> n;
    scanf("%s", a + 1);
    for (int i = 1; i <= n; i++) cin >> num[i];
    int ans = inf, flag = 0;
    for (int i = 1; i < n; i++)
        if (a[i] == 'R' && a[i+1] == 'L') {//第i个物体向右移动，第i+1个物体向左移动
            flag = 1;
            ans = min(ans, (num[i+1]-num[i])>>1);
        }
    flag ? cout << ans << '\n' : cout << "-1\n";
    return 0;
}