//
// Created by Psy.C on 2026/3/2.
//
///x, y：记录匹配位置
/**
i遍历t的索引，cnt计数已匹配的字符数
匹配逻辑：
t[i] == s[cnt]：如果t的当前字符等于s的当前字符
cnt++：匹配计数加1
x = i：记录当前匹配位置在t中的索引
终止条件：当s的所有字符都匹配完成时跳出循环

i从t的末尾开始向前遍历
匹配逻辑：
t[i] == s[res]：如果t的当前字符等于s的当前字符（从末尾开始）
res--：res向前移动一位
y = i：记录当前匹配位置在t中的索引
终止条件：当s的所有字符都从后向前匹配完成时跳出循环

y - x表示两个匹配位置之间的距离，max(..., 0)确保结果非负
输出最大距离
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s, t;
int res, x, y, ans;
int main() {
    fast;
    cin >> s >> t; res = s.size()-1;//s的索引
    for (int i = 0, cnt = 0; i < t.size(); ++i) {
        if (t[i] == s[cnt]) { cnt++; x = i; }
        if (cnt == s.size()) break;
    }
    for (int i = t.size()-1; i >= 0; --i) {
        if (t[i] == s[res]) { res--; y = i; }
        if (res == -1) break;
    }
    ans = max(y - x, 0);
    cout << ans << '\n';
    return 0;
}