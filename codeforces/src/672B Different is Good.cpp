//
// Created by Psy.C on 2026/4/13.
//
/**
n: 字符串长度
vis[M]: 记录每个字符出现次数的数组
a[N]: 存储输入字符串的字符数组

ok: 标记是否可能完成任务（1表示可能，0表示不可能）
ans: 需要替换的字符数量
遍历字符串中的每个字符：
如果字符a[i]出现次数大于1（重复字符）：
尝试找到一个未使用的字符（a-z中vis[j]==0）
找到后：
ans++: 替换次数+1
flag = 1: 标记找到可替换字符
vis[j] = 1: 标记该字符已被使用
vis[a[i]]--: 原字符出现次数-1
break: 结束内层循环
如果没找到可替换字符（flag == 0），设置ok = 0

再次遍历字符串，检查是否仍有重复字符
如果还有字符出现次数大于1，设置ok = 0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 300;
int n, vis[M];
char a[N];
int main() {
    fast;
    cin >> n >> a;
    for (int i = 0; i < n; ++i) vis[a[i]]++;
    int ok = 1, ans = 0;
    for (int i = 0; i < n; ++i)
        if (vis[a[i]] > 1) {
            int flag = 0;
            for (int j = 'a'; j <= 'z'; ++j)
                if (vis[j] == 0) {
                    ans++;
                    flag = 1;
                    vis[j] = 1;
                    vis[a[i]]--;
                    break;
                }
            if (flag == 0) ok = 0;
        }
    for (int i = 0; i < n; ++i)
        if (vis[a[i]] > 1) ok = 0;
    if (ok == 0) cout << "-1\n";
    else cout << ans << '\n';
    return 0;
}