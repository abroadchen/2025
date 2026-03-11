//
// Created by Psy.C on 2026/3/11.
//
/**
N: 最大输入数量 M: 值域上限
n: 输入数字的数量
vis[N]: 访问标记数组（记录被第几个数字访问过）
s[N]: 总步数累加器
cnt[N]: 每个数字被多少个原始数字访问过
q: BFS队列，存储 {当前值, 步数}
将每个数字作为BFS起点，步数为0

t1<<1: 左移一位，相当于乘以2
t1>>1: 右移一位，相当于除以2（向下取整）
t2+1: 步数加1
t1 > M+3: 限制搜索范围，避免无限扩展
vis[t1] == i: 避免同一个原始数字重复访问同一位置
累加步数到s[t1]，增加访问计数cnt[t1]
遍历所有可能的目标数字
找到被所有n个原始数字都能到达的数字
在这些数字中选择总步数最小的

每个数字进行BFS搜索：O(搜索范围)
总体复杂度取决于数字大小和搜索深度
由于有M的限制，实际复杂度是可控的
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5+5, M = 1e5, inf = 0x3f3f3f3f;
int n, vis[N], s[N], cnt[N];
queue<ii> q;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; q.push({x, 0});
        while (!q.empty()) {
            auto t1 = q.front().first, t2 = q.front().second; q.pop();
            if (t1 > M+3) continue;
            if (vis[t1] == i) continue;
            vis[t1] = i; s[t1] += t2; cnt[t1]++;
            q.push({t1<<1, t2 + 1}); q.push({t1>>1, t2 + 1});
        }
    }
    int res = inf;
    for (int i = 0; i <= M; ++i)
        if (cnt[i] == n)
            if (res > s[i]) res = s[i];
    cout << res;
    return 0;
}