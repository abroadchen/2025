//
// Created by Psy.C on 2025/11/4.
//
/*
 *定义常量N=200（节点数上限）和M=50000（边数上限）
*n: 节点数，m: 边数，G: 第一种代价系数，S: 第二种代价系数
r[]: 并查集父节点数组
e[]: 边数组，每条边包含4个属性
 *
 *按照边的第4个属性（索引3）升序排序所有边
*创建映射mp，按键的第3个属性（索引2）分组存储边的索引
相同第三属性的边被归为一组
 *
 *cur: 当前选中的边索引列表
*遍历每个边的分组：
将当前选中的边cur和新组的边p.second合并排序
保持整体按边索引升序排列
 *
*初始化并查集
清空当前边列表
使用Kruskal算法构建最小生成树：
遍历合并后的边列表
如果边的两个端点不在同一连通分量，则加入生成树
 *
*如果成功构建了生成树（边数为n-1）：
计算当前方案的代价：G×当前组的键值 + S×生成树中最大边的第4属性
更新最小代价
 *
 */
#include <array>
#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
const int N = 200, M = 5e4;
const ll inf = 4e18;
int n, m, G, S, r[N+5];
array<int, 4> e[M+5];

int find(int x) { return x == r[x] ? x : r[x] = find(r[x]);}

int main() {
    scanf("%d%d%d%d", &n, &m, &G, &S);
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < 4; ++j) scanf("%d", &e[i][j]);
    }
    sort(e + 1, e + m + 1, [&](auto& a, auto& b) {
        return a[3] < b[3];
    });
    map<int, vector<int>> mp;
    for (int i = 1; i <= m; ++i) mp[e[i][2]].push_back(i);

    ll ans(inf);
    vector<int> cur;
    for (auto& p : mp) {
        vector<int> t;
        for (int i = 0, j = 0; i < cur.size() || j < p.second.size();) {
            if (j == p.second.size() ||
                (i < cur.size() && cur[i] < p.second[j])) {
                t.push_back(cur[i++]);
            } else {
                t.push_back(p.second[j++]);
            }
        }
        for (int i = 1; i <= n; ++i) r[i] = i;
        cur.clear();
        for (int i : t) {
            int x = find(e[i][0]), y = find(e[i][1]);
            if (x == y) continue;
            r[x] = y;
            cur.push_back(i);
        }
        if (cur.size() == n - 1) ans = min(ans,
            1ll * G * p.first + 1ll * S * e[cur.back()][3]);
    }
    if (ans < inf) printf("%lld\n", ans);
    else printf("-1\n");
    return 0;
}