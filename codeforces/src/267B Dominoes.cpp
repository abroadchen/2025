//
// Created by Psy.C on 2025/12/21.
//
/*
*v: 邻接顶点
c: 方向标记（'+'或'-'）
 *
*从顶点x开始深度优先搜索：
遍历从x出发的所有边
t = e[i].v: 边的终点
id = i>>1: 边的编号（因为每条边存储两次）
如果边未被访问：
标记边已访问
递归访问终点
将边信息加入结果（后序遍历）
 *
 *倒序输出结果（因为是后序遍历记录的）
 *
*读取n条边的信息：
每条边存储两次（无向图）：
e[i<<1]: 从a到b的方向，标记为'+'
e[i<<1|1]: 从b到a的方向，标记为'-'
更新邻接表
 *
*寻找奇度顶点：
u: 起始顶点（初始化为第一条边的终点）
sum: 奇度顶点计数
1&v[i].size(): 检查度数是否为奇数
*检查是否存在欧拉路径：
奇度顶点数为0（欧拉回路）或2（欧拉路径）时存在解
从合适的起点开始DFS
如果所有边都被遍历，输出结果；否则无解
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node { int v; char c; } e[220];
vector<node> ans;//存储结果路径
vector<int> v[10];//从顶点i出发的所有边的索引
bool flag[110];//第i条边是否已被访问
void dfs(const int x) {
    for (const int i : v[x]) {
        const int t = e[i].v, id = i>>1;
        if (!flag[id]) {
            flag[id] = true;
            dfs(t);
            ans.push_back({id,e[i].c});
        }
    }
}

int n;
void out() {
    for (int i = n - 1; i >= 0; --i)
        cout << ans[i].v + 1 << ' ' << ans[i].c << '\n';
}

int main() {
    fast;
    cin >> n;
    for (int i = 0, a, b; i < n; ++i) {
        cin >> a >> b;
        e[i<<1] = {b,'+'}; v[a].push_back(i<<1);
        e[i<<1|1] = {a, '-'}; v[b].push_back(i<<1|1);
    }
    int u = e[0].v, sum = 0;
    for (int i = 0; i <= 6; ++i) if (1&v[i].size()) u = i, sum++;
    if (sum == 0 || sum == 2) {
        dfs(u);
        if (ans.size() == n) out();
        else cout << "No solution";
    } else cout << "No solution";
    return 0;
}