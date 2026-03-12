//
// Created by Psy.C on 2026/3/12.
//
/**
每个项目是否被添加（1表示已添加，0表示未添加）
ans: 记录最大撤销失败次数
d: 当前可撤销的操作数量
x: 当前撤销失败的次数
读入操作类型s和项目编号k

添加操作 (s[0] == '+'):
if (d > 0): 如果有可撤销的操作
d--: 消耗一个撤销机会
mp[k] = 1: 将项目k标记为已添加
else: 如果没有可撤销的操作
x++: 撤销失败次数加1
mp[k] = 1: 将项目k标记为已添加
删除操作 (s[0] == '-'):
if (mp[k] == 1): 如果项目k确实存在
mp[k] = 0: 将项目k标记为未添加
d++: 可撤销操作数加1
else: 如果项目k不存在（撤销失败）
x++: 撤销失败次数加1
d++: 可撤销操作数加1

时间复杂度：O(n log n)，主要是map操作
空间复杂度：O(n)，存储映射关系
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
string s;
map<int, int> mp;
int main() {
    fast;
    cin >> n;
    int ans = 0;
    for (int i = 0, k, d = 0, x = 0; i < n; ++i) {
        cin >> s >> k;
        if (s[0] == '+') {
            if (d > 0) { d--; mp[k] = 1; }
            else { x++; mp[k] = 1; }
        } else {
            if (mp[k] == 1) mp[k] = 0, d++;
            else x++, d++;
        }
        ans = max(ans, x);
    }
    cout << ans << '\n';
    return 0;
}