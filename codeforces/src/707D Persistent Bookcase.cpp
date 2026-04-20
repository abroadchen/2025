//
// Created by Psy.C on 2026/4/19.
//
/**
v[M]: 树的邻接表，v[i]存储节点i的子节点
op[M]: 操作类型
l[M], r[M]: 操作参数
ans[M]: 每个操作后的结果
b[N]: N个位集数组
c: 辅助位集
if (!x): 如果是根节点0，递归处理所有子节点
操作1：设置位并计数
b[l[x]].test(r[x]): 检查位r[x]是否已设置
如果未设置：b[l[x]].set(r[x])，ans[x]++
flag记录原始状态，回溯时恢复
操作2：清除位并计数
如果位已设置：清除该位，ans[x]--
操作3：位集异或
b[l[x]].count(): 计算位集中1的个数
b[l[x]] ^= c: 位集异或操作
回溯时撤销异或操作
操作4：普通节点
传递当前结果，继续递归

n: 位集数量
m: 位数
q: 操作数
c.set(i): 设置c的第i位
op[i] < 3: 读入l[i], r[i]参数
op[i] < 4: 添加父子关系 i-1 -> i
op[i] == 4: 添加父子关系 l[i] -> i
从根节点0开始DFS
输出每个操作的结果
O(q × N): 每个操作可能影响N个位
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1007, M = 1e5+7;

vector<int> v[M];
int op[M], l[M], r[M], ans[M];
bitset<N> b[N], c;
void dfs(int x) {
    int i;
    if (!x) {
        for (i = 0; i < v[x].size(); ++i)
            dfs(v[x][i]);
    }
    if (op[x] == 1) {
        bool flag = false;
        if (b[l[x]].test(r[x])) flag = true;
        else b[l[x]].set(r[x]), ans[x]++;
        for (i = 0; i < v[x].size(); ++i)
            ans[v[x][i]] = ans[x], dfs(v[x][i]);
        if (!flag) b[l[x]].reset(r[x]);
    }
    if (op[x] == 2) {
        bool flag = true;
        if (b[l[x]].test(r[x])) b[l[x]].reset(r[x]), ans[x]--;
        else flag = false;
        for (i = 0; i < v[x].size(); ++i)
            ans[v[x][i]] = ans[x], dfs(v[x][i]);
        if (flag) b[l[x]].set(r[x]);
    }
    if (op[x] == 3) {
        ans[x] -= b[l[x]].count();
        b[l[x]] ^= c;
        ans[x] += b[l[x]].count();
        for (i = 0; i < v[x].size(); ++i)
            ans[v[x][i]] = ans[x], dfs(v[x][i]);
        b[l[x]] ^= c;
    }
    if (op[x] == 4) {
        for (i = 0; i < v[x].size(); ++i)
            ans[v[x][i]] = ans[x], dfs(v[x][i]);
    }
}

int n, m, q, i;
int main() {
    fast;
    cin >> n >> m >> q;
    for (i = 1; i <= m; ++i) c.set(i);
    for (i = 1; i <= q; ++i) {
        cin >> op[i];
        if (op[i] < 3) cin >> l[i] >> r[i];
        else cin >> l[i];
        if (op[i] < 4) v[i-1].push_back(i);
        else v[l[i]].push_back(i);
    }
    dfs(0);
    for (i = 1; i <= q; ++i) cout << ans[i] << '\n';
    return 0;
}