//
// Created by Psy.C on 2026/10/17.
//
/**
s：当前字符串（初始输入）。
t：目标字符串。
c[30]：字符计数差数组。
ans：记录每次操作的长度（操作是"翻转前 k 个、再 shift"等）
读入 n、s、t（从下标 1 开始存）。
统计每个字符在 s 中比 t 中多几个（c[s[i]]++、c[t[i]]--）。
若任意字符计数不为 0（即 s 和 t 的字符组成不同）→ 无法通过重排列得到 → 输出 -1 并退出。
第一步就保证了 s、t 是彼此的重排列，否则直接无解
外层循环 i 从 n 到 1，即从 t 的末尾往前逐个确定目标字符。
内层 j 从 n-i+1 扫到 n：也就是在 s 的右端（尚未处理的后缀区域）‍寻找一个等于 t[i] 的字符，记为位置 id。
找到这个字符在 s 中的位置 id，之后要把它"搬"到正确位置。
关键：内层扫描范围 [n-i+1, n] 是当前还没被固定的后缀。因为是从后往前构造，后半部分会被逐步确定
若 id != n：先把后缀 [id, n] 整体翻转（记录操作 n 的反转、以及 id-1 长度的操作序列，实际是两次翻转的组合），实际上这里 ans.push_back(n) 和 push_back(id-1) 配合两个 swap 翻转，得到某个中间态。
若 id != 1：执行一次"右移循环"——ans.push_back(1)，把最后一个字符移到开头（s[1] = s[n]，其余整体右移一位）。
这段整体效果是：将要放到位置 i 的字符精确放进目标位，用的是"翻转后缀 + 循环右移"的组合操作，每处理一个 i 就把它固定到 s 的末端/目标位置。由于是从后往前，处理完的字符不会再被扰动。
本质是贪心地从 t 的末尾往前，每次通过可逆翻转操作把需要的字符搬到指定位置并固定在右端
输出总操作次数（ans.size()），然后依次输出每个操作的长度
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e3+5;

char s[N], t[N];
int c[30];
vector<int> ans;
int main() {
    int n; cin >> n;
    scanf("%s%s", s+1, t+1);
    for (int i = 1; i <= n; ++i) { c[s[i]-'a']++; c[t[i]-'a']--; }
    for (int i = 0; i < 26; ++i) if (c[i]) { cout << -1; return 0; }
    for (int i = n; i >= 1; --i) {
        int id = n;
        for (int j = n-i+1; j <= n; ++j)
            if (s[j] == t[i]) { id = j; break; }
        if (id != 1) {
            if (id != n) {
                ans.push_back(n); ans.push_back(id-1);
                int l = id, r = n;
                while (l < r) {
                    swap(s[l], s[r]);
                    l++; r--;
                }
            }
            ans.push_back(1);
            char tmp = s[n];
            for (int j = n; j >= 2; --j) s[j] = s[j-1];
            s[1] = tmp;
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) cout << i << ' ';
    return 0;
}