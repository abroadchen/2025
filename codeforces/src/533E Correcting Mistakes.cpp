//
// Created by Psy.C on 2026/3/4.
//
/**
遍历字符串，找到第一个和最后一个不匹配的位置
l: 最左边的不匹配位置
r: 最右边的不匹配位置

初始化两个标志：a1 = 1, a2 = 1（表示两种操作都可行）
从l+1到r遍历：
a1: 检查是否可以通过移动s1来匹配s2（s1向右移一位）
检查s1[i]是否等于s2[i-1]
a2: 检查是否可以通过移动s2来匹配s1（s2向右移一位）
检查s1[i-1]是否等于s2[i]
输出可行操作的数量（0、1或2）

时间复杂度为O(n)，空间复杂度为O(1)（除了输入字符串）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int inf = 0x3f3f3f3f;
int n;
string s1, s2;
int main() {
    fast;
    cin >> n >> s1 >> s2;
    int l = inf, r = -inf;
    for (int i = 0; i < n; ++i)
        if (s1[i] != s2[i]) {
            l = min(l, i);
            r = max(r, i);
        }
    int a1 = 1, a2 = 1;
    for (int i = l+1; i <= r; ++i) {
        if (s1[i] != s2[i-1]) a1 = 0;
        if (s1[i-1] != s2[i]) a2 = 0;
    }
    cout << a1 + a2 << '\n';
    return 0;
}