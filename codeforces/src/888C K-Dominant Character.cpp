//
// Created by Psy.C on 2026/10/8.
//
/**
先给一个上界/初始值：字符串长度一半 + 1
对每个字母 ch，遍历字符串：
lst 记录上一个 ch 出现的位置；
k 记录相邻两个 ch 之间（含端点）的最大间隔长度，即 max(j - lst)；
处理完后，最后一段从 lst 到末尾的长度为 s.size()-lst，也与 k 取 max。
这个 max(k, s.size()-lst) 表示：若选定字母 ch 作为最后存留的字符，需要多少轮操作才能把其它字符全删掉（间隔越大，需要的轮次越多）。
对所有字母取 ans = min(...)，即找能让轮次最少的那种"最后保留字母"
输出最小所需轮次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int ans;
int main() {
    fast;
    cin >> s;
    ans = s.size()/2 + 1;
    for (int i = 0; i < 26; ++i) {
        char ch = i + 'a';
        int lst = -1, k = 0xACACACAC;
        for (int j = 0; j < s.size(); ++j) {
            if (s[j] == ch)
                k = max(k, j-lst), lst = j;
        }
        ans = min(max(k, static_cast<int>(s.size())-lst), ans);
    }
    cout << ans << '\n';
    return 0;
}