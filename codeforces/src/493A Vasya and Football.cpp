//
// Created by Psy.C on 2026/2/19.
//
/**
t: 提交时间
x: 题目编号
op: 操作类型 ('h'表示H题, 's'表示S题)
c: 提交结果 ('y'表示正确, 'n'表示错误)
mp[op][x]: 记录操作类型op、题目x的提交状态
ok[op][x]: 标记操作类型op、题目x是否已完成

当题目尚未完成(!ok[a[i].op][a[i].x]) 且 状态值≥2时
输出队伍名称、题目编号、完成时间
标记该题已完成

mp[op][x] >= 2 表示需要至少一次正确提交（1分）或两次错误提交（2分）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node {
    int t, x;
    char op, c;
} a[100];
string s1, s2;
int n;
map<int, map<int, int>> mp, ok;
int main() {
    fast;
    cin >> s1 >> s2 >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].t >> a[i].op >> a[i].x >> a[i].c;
        if (a[i].c == 'y') mp[a[i].op][a[i].x]++;
        else mp[a[i].op][a[i].x] += 2;
        if (!ok[a[i].op][a[i].x] && mp[a[i].op][a[i].x] >= 2) {
            cout << (a[i].op == 'h' ? s1 : s2) << ' ' << a[i].x << ' '
                << a[i].t << '\n';
            ok[a[i].op][a[i].x] = 1;
        }
    }
    return 0;
}