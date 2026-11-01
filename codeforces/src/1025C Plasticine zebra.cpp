//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
从位置 0 开始向右扫描，只要相邻字符不同（s[i]!=s[i+1]）就累计 cnt。
一旦遇到第一处 s[i]==s[i+1]（相邻相同，破坏了"不能相邻相同"），就把到目前为止的连续长度 cnt 记入 s1 并 break。
含义：s1 = 从字符串开头连续延伸到第一个"相邻相同"位置之前的可接受长度（即开头能无冲突地连续取多长）
从最后一个字符开始向左扫描，同理累计 cnt。
遇到第一处相邻相同就记入 s2 并 break。
含义：s2 = 从字符串末尾向前延伸的长度
这里处理环形特性：如果首字符 ≠ 尾字符，说明环被打断处（首尾交界）没有相邻相同，可以把开头段 s1 和末尾段 s2 首尾拼接成一段更长的连续可取长度。
所以把 ans 初值设为 s1 + s2（仅当首尾不同时成立）。
若首尾相同，则它们相邻相等、不能拼在一起，ans 保持 0，后面会由整串扫描来更新
遍历整个串，累计每段连续"相邻不同"的子串长度。
每遇到相邻相同处，就把当前累计长度与 ans 取 max，然后重置。
最后补一次 max 结算末尾那段。
输出 ans（最大长度）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define per(i,n) for (int i = n; i >= 1; i--)
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    int cnt(1), s1 = 0, s2 = 0, ans = 0;
    rep(i,s.size()-1) {
        if (s[i] != s[i+1]) cnt++;
        else { s1 += cnt; break; }
    }
    cnt = 1;
    per(i,s.size()-1) {
        if (s[i] != s[i-1]) cnt++;
        else { s2 += cnt; break; }
    }
    if (s[0] != s[s.size()-1]) ans = s1 + s2;
    cnt = 1;
    rep(i,s.size()-1) {
        if (s[i] != s[i+1]) cnt++;
        else { ans = max(ans, cnt); cnt = 1; }
    }
    ans = max(ans, cnt);
    cout << ans;
    return 0;
}