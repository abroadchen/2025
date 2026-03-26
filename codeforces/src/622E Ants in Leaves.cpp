//
// Created by Psy.C on 2026/3/26.
//
/**
v[N]：邻接表存储树结构
dep[N]：存储叶节点深度
cnt：叶节点计数器

找出从cur出发的叶节点及其深度
cur（当前节点），fa（父节点），h（当前深度）
遍历当前节点的所有邻居
跳过父节点避免回头
递归搜索子节点
if (len == 1)：如果是叶节点（除了根节点外的度为1的节点），记录深度

len = v[1].size()：根节点1的度数
遍历根节点的每个子树
对每个子树进行DFS，找出所有叶节点的深度
sort(dep + 1, dep + cnt + 1)：将叶节点深度从小到大排序
num[j] = max(num[j-1]+1, dep[j])：动态规划计算
num[j-1]+1：前一个节点分配值+1
dep[j]：当前节点的深度限制
选择较大的值确保满足深度约束
ans = max(ans, num[cnt])：更新全局最优解

时间复杂度：O(n log n)（主要是排序操作） 空间复杂度：O(n)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5;

vector<int> v[N];
int dep[N], cnt;
void dfs(int cur, int fa, int h) {
    int len = v[cur].size();
    for (int i = 0; i < len; ++i) {
        int x = v[cur][i];
        if (x == fa) continue;
        dfs(x, cur, h + 1);
    }
    if (len == 1) dep[++cnt] = h;
}

int n, num[N];
int main() {
    fast; cin >> n;
    for (int i = 1, x, y; i <= n-1; ++i) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
    }
    int len = v[1].size(), ans = 0;
    for (int i = 0; i < len; ++i) {
        cnt = 0;
        dfs(v[1][i], 1, 1);
        sort(dep + 1, dep + cnt + 1);
        for (int j = 1; j <= cnt; ++j)
            num[j] = max(num[j-1]+1, dep[j]);
        ans = max(ans, num[cnt]);
    }
    cout << ans << '\n';
    return 0;
}