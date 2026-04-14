//
// Created by Psy.C on 2026/4/14.
//
/**
p(x): 计算x³（立方函数）
ap: 记录立方数个数的最大值
ans: 记录立方数之和的最大值
m: 剩余的数值
x: 当前立方数的个数
y: 当前立方数的和
如果m <= 0，检查是否更新最优解：
x > ap: 立方数个数更多，更新
x == ap && y > ans: 个数相同但和更大，更新
找到最大的t，使得(t+1)³ > m，即t³ ≤ m
t是满足条件的最大整数

选择t³：
dfs(m - p(t), x + 1, y + p(t))
用掉一个t³，剩余m-p(t)
选择(t-1)³（如果t>1）：
dfs(p(t) - 1 - p(t-1), x + 1, y + p(t-1))
这个分支处理t³-1-p(t-1)的剩余部分
用掉一个(t-1)³

读入m
从m开始，立方数个数为0，立方数和为0
执行DFS
输出最大立方数个数和对应的立方数之和


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll p(int x) { return 1ll*x*x*x; }
ll ap, ans;
void dfs(ll m, ll x, ll y) {
    if (m <= 0) {
        if (x > ap || (x == ap && y > ans)) {
            ap = x, ans = y;
        }
        return;
    }
    int t = 0;
    while (p(t+1) <= m) t++;
    dfs(m - p(t), x + 1, y + p(t));
    if (t > 1) dfs(p(t) - 1 - p(t-1), x + 1, y + p(t-1));
}
ll m;
int main() {
    fast;
    cin >> m; dfs(m, 0, 0);
    cout << ap << ' ' << ans;
    return 0;
}