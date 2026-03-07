//
// Created by Psy.C on 2026/3/7.
//
/**
k：需要分割成的子串数量
cnt：当前已分割的子串数量
s：输入的字符串
ans[N]：存储分割后的各个子串
vis：字符访问标记的映射，记录字符是否出现过

读入k（目标子串数）和字符串s
初始化cnt=1（当前子串编号）
将s的第一个字符添加到第一个子串ans[1]中
标记s[0]字符已被使用
从第二个字符开始遍历字符串s
如果当前字符s[i]未出现过（!vis[s[i]]）：
增加子串计数（cnt++）
如果子串数超过k（cnt > k）：
将剩余所有字符都添加到最后一个有效的子串中
跳出循环
标记当前字符为已使用
将当前字符添加到当前子串ans[cnt]中

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int k, cnt;
string s, ans[N];
map<char, int> vis;
int main() {
    fast;
    cin >> k >> s; cnt = 1;
    ans[cnt] += s[0]; vis[s[0]] = 1;
    for (int i = 1; i < s.size(); ++i) {
        if (!vis[s[i]]) {
            cnt++;
            if (cnt > k) {
                for (int j = i; j < s.size(); ++j)
                    ans[cnt-1] += s[j];
                break;
            }
            vis[s[i]] = 1;
        }
        ans[cnt] += s[i];
    }
    if (cnt < k) return cout << "NO\n", 0;
    cout << "YES\n";
    for (int i = 1; i <= cnt; ++i)
        cout << ans[i] << '\n';
    return 0;
}