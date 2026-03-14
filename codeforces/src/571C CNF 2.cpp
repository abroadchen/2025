//
// Created by Psy.C on 2026/3/13.
//
/**
flag[N]：标记节点是否已处理
b[N]：标记边是否已访问
ans[N]：记录答案
f[N]：构建的图结构

DFS函数：寻找增广路径
flag[x] = true：标记当前节点已访问
遍历邻接节点，尝试匹配
如果找到增广路径，更新答案并返回true

n：节点数，m：边数
c[N]：存储最终结果
a[N]：邻接表
对每个节点i，读取其连接的边
将边的绝对值作为索引，存储节点i和边的类型（正数为1，负数为0）
处理每条边：
如果边只连接一个节点，直接赋值并标记
如果边连接两个节点且类型相同，直接赋值并标记
如果边连接两个不同类型节点，构建二分图
对未处理的节点执行DFS
如果无法找到匹配，输出"NO"并退出
输出"YES"
根据匹配结果更新c数组
输出最终结果字符串

 */
#include <bits/stdc++.h>
#define ii pair<int, int>
#define abs(x) ((x)>0?(x):-(x))
using namespace std;
constexpr int N = 2e5+5;

bool flag[N], b[N];
int ans[N];
vector<ii> f[N];
bool dfs(int x) {
    flag[x] = true;
    for (int i = 0; i < f[x].size(); ++i) {
        int t1 = f[x][i].first, t2 = f[x][i].second;
        if (b[t2]) continue; b[t2] = true;
        if (flag[t1]) { ans[x] = t2; return true; }
        if (dfs(t1)) { ans[x] = t2; return true; }
        ans[t1] = t2;
    }
    return false;
}

int n, m, c[N];
vector<ii> a[N];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, q, x; i <= n; ++i) {
        scanf("%d", &q);
        while (q--) {
            scanf("%d", &x);
            a[abs(x)].push_back({i, x < 0 ? 0 : 1});
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (a[i].size() == 0) continue;
        if (a[i].size() == 1)
            c[i] = a[i][0].second, flag[a[i][0].first] = true;
        if (a[i].size() == 2) {
            if (a[i][0].second == a[i][1].second)
                c[i] = a[i][0].second, flag[a[i][0].first] = flag[a[i][1].first] = true;
            else
                f[a[i][0].first].push_back({a[i][1].first, i}),
                f[a[i][1].first].push_back({a[i][0].first, i});
        }
    }
    for (int i = 1; i <= n; ++i) if (!flag[i]) {
        if (!dfs(i))
            return puts("NO"), 0;
    }
    puts("YES");
    for (int i = 1; i <= n; ++i) if (ans[i]) {
        for (int j = 0; j < a[ans[i]].size(); ++j)
            if (a[ans[i]][j].first == i)
                c[ans[i]] = a[ans[i]][j].second;
    }
    for (int i = 1; i <= m; ++i) putchar(c[i] + '0'); puts("");
    return 0;
}