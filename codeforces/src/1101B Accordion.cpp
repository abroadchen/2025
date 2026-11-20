//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
ls：字符串长度；l, r：分别记录最左端开头和最右端结尾的关键位置；cnt：统计 | 个数；f：标志位
第一趟从左往右扫：先找第一个 [ 位置（f 变为 1），然后再找这个 [ 之后的第一个 :。这个 : 的位置记为左边界 l，找到就 break。
这组成了 [: 这个开头结构。
如果 l 还是 0（即根本没找到 [，或 [ 后没有 :），说明构不成最小的 [:，输出 -1 结束
第二趟从右往左扫（从 ls-1 到 l+1，跳过已确定的左 :）：先找第一个 ]，再找这个 ] 之前的第一个 :，记为右边界 r。
这组成了 :] 的结尾结构。
若找不到 r，输出 -1 结束。
这样 l 是最靠左可行的 :，r 是最靠右可行的 :（保证 | 最多）
统计从 l 到 r 之间（含两端）共有多少个 |，记为 cnt
总长度 = | 的个数 + 4（即 [、:, :、] 四个符号）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5e5+5;

string s;
int main() {
    fast;
    cin >> s;
    int ls = s.size(), l = 0, r = 0, cnt = 0;
    bool f = 0;
    for (int i = 0; i < ls; i++) {
        if (s[i] == '[' && !f) f = 1;
        if (s[i] == ':' && f) { l = i; break; }
    }
    if (!l) { cout << "-1"; return 0; }
    f = 0;
    for (int i = ls-1; i > l; i--) {
        if (s[i] == ']' && !f) f = 1;
        if (s[i] == ':' && f) { r = i; break; }
    }
    if (!r) { cout << "-1"; return 0; }
    for (int i = l; i <= r; i++) if (s[i] == '|') cnt++;
    cout << cnt+4;
    return 0;
}