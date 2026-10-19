//
// Created by Psy.C on 2026/10/18.
//
/**
读入字符串 s。
变量 a 初始为 'a'——这是当前期望放置的字母（从 'a' 开始逐步 +1 到 'z'
遍历字符串每个位置 i。

if (s[i] <= a)：如果当前位置的字符小于等于当前需要的字母 a。

由于最终要求严格递增且必须从 'a' 依次放，若当前位置字符 ≤ a，说明把这个位置改成 a 之后仍然能满足"不小于前一个"且是最小可能的选择，所以 把 s[i] 改成 a，然后 a++ 进入下一个字母。
if (a > 'z') break;：一旦 26 个字母（a…z）都已经放完，任务完成，提前退出循环（后面的字符已经不重要了，只要是合法递增且改了也不影响——但题目里这里通常停止后直接输出）。

简单说：能改成 a 就改，改完一个推进一格；当 a 越过 'z' 时表示 a–z 全部放置完毕
如果循环结束后 a 仍 ≤ 'z'，说明没能把 26 个字母全部放完（要么字符串长度 < 26，要么某些位置因为 s[i] > a 而无法放入当前字母），无法构造出合法答案，输出 -1
否则说明 a–z 已全部成功放置，直接输出修改后的 s
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

string s;
char a = 'a';
int main() {
    fast;
    cin >> s;
    rep(i,s.length()) {
        if (s[i] <= a) {
            s[i] = a; a++;
            if (a > 'z') break;
        }
    }
    if (a <= 'z') { cout << "-1"; return 0; }
    cout << s;
    return 0;
}