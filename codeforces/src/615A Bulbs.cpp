//
// Created by Psy.C on 2026/3/24.
//
/**
n: 学生数量
m: 题目数量（1到m）
flag[105]: 标记数组，flag[i]表示第i道题是否被解决

遍历每个学生
tn: 当前学生解决的题目数量
t: 题目编号
对于每个学生，读入他们解决的题目编号，并标记为已解决

初始化答案为true
遍历所有题目（1到m）
如果发现任何一道题目没有被解决（flag[i]为false），设置ans为false并跳出循环
时间复杂度：O(n + m + 总题目数)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
bool flag[105];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) flag[i] = false;
    for (int i = 1, tn, t; i <= n; ++i) {
        cin >> tn;
        while (tn--) {
            cin >> t;
            flag[t] = true;
        }
    }
    bool ans = true;
    for (int i = 1; i <= m; ++i)
        if (!flag[i]) {
            ans = false;
            break;
        }
    if (ans) cout << "YES\n"; else cout << "NO\n";
    return 0;
}