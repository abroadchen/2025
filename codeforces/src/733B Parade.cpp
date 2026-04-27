//
// Created by Psy.C on 2026/4/26.
//
/**
n, a[N] - 输入数量和差值数组
s1, s2 - 分别存储正差值和负差值的总和
找出数组中的最大值mx及其位置l
找出数组中的最小值mn及其位置r
位置从1开始计数（i+1）
情况1：无需交换
mx <= 0 - 所有差值都非正
mn >= 0 - 所有差值都非负
输出：0（表示不需要交换）
情况2：选择最小值位置
条件：abs(s1) + abs(mn) >= abs(s2) + abs(mx)
意义：当移除最小值后剩余正数绝对值之和比移除最大值后剩余负数绝对值之和更大
输出：r（最小值位置）
情况3：选择最大值位置
其他情况
输出：l（最大值位置）
时间复杂度：O(n)，两次遍历数组
空间复杂度：O(n)，存储差值数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7, inf = 0xffffff;//约16777215
int n, a[N];
int main() {
    fast;
    cin >> n;
    int s1 = 0, s2 = 0;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;
        a[i] = x - y;
        if (a[i] > 0) s1 += a[i];
        else s2 += a[i];
    }
    int mx = 0, mn = inf, l = 0, r = 0;
    for (int i = 0; i < n; ++i) {
        if (mx < a[i]) { mx = a[i]; l = i + 1; }
        if (mn > a[i]) { mn = a[i]; r = i + 1; }
    }
    if (mx <= 0 || mn >= 0) cout << "0\n";
    else if (abs(s1) + abs(mn) >= abs(s2) + abs(mx)) cout << r << '\n';
    else cout << l << '\n';
    return 0;
}