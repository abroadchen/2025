//
// Created by Psy.C on 2026/10/7.
//
/**
从后往前扫描。当遇到字符 'h' 时，把它前面连续的一段 'k' 全部替换成空格（占位，表示"删掉"）。
注意内层循环先把 j--（跳到 h 前一个），然后一路向前把所有 'k' 置为空格，遇到非 'k' 或到字符串头停。最后 j++ 恢复。
这个规则的语义是："kh" 及其前面连续的 "k" 前缀可以消掉——更像规则是"连续 k 后面跟 h"，等价于 k 可以被 h（h 代表某个音）吞并/规范化。常见这类题（比如把 "kh" 全整合成单个 h，或把 k...kh 规约为 h）。这里具体是(a)把一串 a 前导 k 全部删除。
实际效果：把 "kkkh" 里的 "kkk" 删除，只留 "h"。这就是规则 1
跳过刚才置成空格（被删掉）的字符。
把每个 'u' 替换成字符串 "oo"（即把单字母 u 展开成两个 o），其余原样保留。
得到该串的规范形式 a[i]
第二轮遍历时，对每个 i，若 mp[a[i]] 仍为 1（即之前还没被计过），则 k++ 并清零——实现每类规范串只计一次。
输出 k = 去重后不同规范串的个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 405;
string s, a[N];
map<string, bool> mp;
int main() {
    fast;
    int n, k = 0; cin >> n;
    for (int i = 0, j; i< n; ++i) {
        cin >> s;
        for (j = s.size()-1; j > 0; j--)
            if (s[j] == 'h') {
                for (j--; j >= 0 && s[j] == 'k'; j--) s[j] = ' ';
                j++;
            }
        for (j = 0; j < s.size(); ++j)
            if (s[j] != ' ') {
                if (s[j] == 'u') a[i] = a[i] + "oo";
                else a[i] = a[i] + s[j];
            }
        mp[a[i]] = 1;
    }
    for (int i = 0; i < n; ++i) k += mp[a[i]], mp[a[i]] = 0;
    cout << k << '\n';
    return 0;
}