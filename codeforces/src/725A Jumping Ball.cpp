//
// Created by Psy.C on 2026/4/24.
//
/**
n: 字符串长度
ans: 答案计数器（初始化为0）
s: 输入的字符串

从字符串开头开始遍历
遇到'<'字符就增加计数器ans，移动到下一个位置
遇到非'<'字符就停止
从字符串末尾开始向前遍历
遇到'>'字符就增加计数器ans，向前移动一个位置
遇到非'>'字符就停止
输出总的连续字符数量
时间复杂度: O(n) - 最多遍历整个字符串两次
空间复杂度: O(1) - 除了输入外只使用常数额外空间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, ans;
string s;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ) {
        if (s[i] == '<') { ans++; i++; }
        else break;
    }
    for (int i = n-1; i >= 0; ) {
        if (s[i] == '>') { ans++; i--; }
        else break;
    }
    cout << ans << '\n';
    return 0;
}