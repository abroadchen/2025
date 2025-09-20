//
// Created by Psy.C on 2025/9/20.
//

/*
 *
*p[N]: 存储每个节点的访问顺序（时间戳），-1表示未指定
mn[N]: 存储每个节点子树中最小的访问时间戳
pre: 记录上一个访问的节点时间戳，初始化为-1
v[N]: 邻接表，存储图的连接关系
ans: 存储遍历结果的向量
 *
*DFS函数计算每个节点子树中的最小时间戳
如果节点u有指定的时间戳，则mn[u] = p[u]
否则初始化为400（一个较大的值）
*遍历节点u的所有邻接节点
跳过父节点fa
递归计算子节点的mn值，并更新当前节点的mn值为最小值
 *
*第二次DFS验证是否存在有效的遍历顺序
将当前节点添加到结果向量中
*如果当前节点有指定的时间戳
检查是否违反了时间顺序（当前时间戳小于上一个）
如果违反顺序返回false，否则更新pre为当前时间戳
 *
*遍历排序后的邻接节点
递归调用dfs2，如果返回false则直接返回false
在回溯时将当前节点再次添加到结果中（欧拉路径）
如果所有子树都满足条件，返回true
 *
 *
 *
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 400;

int p[N], mn[N], pre = -1;
vector<int> v[N], ans;

bool cmp(int a, int b) {
    return mn[a] < mn[b];
}

int dfs(int u, int fa) {
    if (p[u] != -1) mn[u] = p[u];
    else mn[u] = 400;

    for (int i = 0; i < (int)v[u].size(); ++i) {
        if (v[u][i] == fa) continue;
        mn[u] = min(mn[u], dfs(v[u][i], u));
    }
    sort(v[u].begin(), v[u].end(), cmp);
    return mn[u];
}

bool dfs2(int u, int fa) {
    ans.push_back(u);
    if (p[u] != -1) {
        if (p[u] < pre) return false;
        else pre = p[u];
    }
    for (int i = 0; i < (int)v[u].size(); ++i) {
        if (v[u][i] == fa) continue;
        if (!dfs2(v[u][i], u)) return false;
        ans.push_back(u);
    }
    return true;
}

int main() {

    int n, i, x, y, cnt = 0;
    scanf("%d", &n);
    ans.clear();
    memset(p, -1, sizeof(p));
    for (i = 1; i <= n; ++i) v[i].clear();
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    //读取需要按特定顺序访问的节点，为其分配时间戳
    while (scanf("%d", &x) != EOF) p[x] = cnt++;

    dfs(1, -1);
    if (!dfs2(1, -1)) printf("-1\n");
    else {
        for (i = 0; i < (int)ans.size(); ++i) printf("%d ", ans[i]);
        printf("\n");
    }

    return 0;
}