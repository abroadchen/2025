//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
l1, l2：两个字符串的长度（虽然代码里多数靠 s1.size()，长度变量只用于最开始的快速判断）。
s1：模式串，包含特殊字符 *（题目规定至多一个 *）。
s2：目标串，需匹配的对象
* 在 s1 中可以匹配任意长度（无限个字符）。若 s1 长度比 s2 长 1 以上（且唯一的 * 只能补充 1 个字符，即 * 至少要占一位），则不可能匹配，直接判 No
两串完全相等 → 直接 Yes
从左到右逐位对齐比较：

如果当前位置 s1[i] 是 *，进入"后半段匹配"处理（见下节）。
否则要求 s1[i] == s2[i]，有一位不等就直接 No
前面已经用下标 i（到 * 为止）比完了 s1 的前缀与 s2 对应位置。
现在用两个指针从各自末尾倒着比较，让 * 之前的前缀和 * 之后的后缀都能对上，中间被 * "吞掉"即可。
s1.size() - 1 > s2.size() 判断：排除 * 后剩余长度仍大于 s2，不可能匹配。
倒着比到再次碰到 * 所在位置（即 s1[p1] == '*'），说明 * 前后都匹配成功 → Yes
处理 * 出现在字符串末尾的边界情况：此时 * 前面的所有字符需与 s2 对应部分全部相等。
若前半段全部匹配且末尾是 * → Yes
前面所有成功分支都返回了，到这里说明匹配失败 → No
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int l1, l2;
string s1, s2;
int main() {
    fast;
    cin >> l1 >> l2 >> s1 >> s2;
    if (l1 > l2 + 1) { cout << "No\n"; return 0; }
    if (s1 == s2) { cout << "Yes"; return 0; }
    for (int i = 0; i < min(s1.size(), s2.size()); i++) {
        if (s1[i] == '*') {
            if (s1.size() - 1 > s2.size()) { cout << "No\n"; return 0; }
            int p1 = s1.size(), p2 = s2.size();
            while (true) {
                if (s1[p1] != s2[p2]) { cout << "No\n"; return 0; }
                --p1, --p2;
                if (s1[p1] == '*') { cout << "Yes\n"; return 0; }
            }
        }
        if (s1[i] != s2[i]) { cout << "No\n"; return 0; }
    }
    bool flg = true;
    for (int i = 0; i < s1.size()-1; i++)
        if (s1[i] != s2[i]) { flg = false; break; }
    if (flg && s1[s1.size()-1] == '*') { cout << "Yes"; return 0; }
    cout << "No\n";
    return 0;
}