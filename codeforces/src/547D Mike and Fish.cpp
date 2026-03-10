//
// Created by Psy.C on 2026/3/8.
//
/**
vis[N]：访问标记数组，同时记录颜色（0或1）
p[N]：邻接表，存储图的边
dfs函数：
如果节点x已被访问，返回
标记节点x的颜色为y
对x的所有邻居递归调用DFS，颜色为y^1（异或1，即取反）

ans[x][0]存储与x关联的第一个位置，ans[x][1]存储第二个位置
处理x：
如果ans[x][0]已有值（即之前有元素与x关联）：
在i和ans[x][0]之间建立边
将ans[x][0]重置为0
否则：将i存储到ans[x][0]
处理y：
如果ans[y][1]已有值：
在i和ans[y][1]之间建立边
将ans[y][1]重置为0
否则：将i存储到ans[y][1]

对每个未访问的节点执行DFS，从颜色0开始
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5;

int vis[N];
vector<int> p[N];
void dfs(int x, int y) {
    if (vis[x]) return;
    vis[x] = y;
    for (int i : p[x]) dfs(i, y^1);
}

int n, ans[N][2];
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        if (ans[x][0]) {
            p[i].push_back(ans[x][0]);
            p[ans[x][0]].push_back(i);
            ans[x][0] = 0;
        } else ans[x][0] = i;
        if (ans[y][1]) {
            p[i].push_back(ans[y][1]);
            p[ans[y][1]].push_back(i);
            ans[y][1] = 0;
        } else ans[y][1] = i;
    }
    for (int i = 1; i <= n; ++i) {
        dfs(i, 0);
        if (vis[i]) cout << 'r'; else cout << 'b';
    }
    return 0;
}