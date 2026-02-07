//
// Created by Psy.C on 2026/2/7.
//
/**
n, m: 三维矩阵的前两个维度
w: 权重参数
c[N][M][M]: 存储k个n×m的字符矩阵

功能: 计算矩阵a和矩阵b之间的差异度
过程: 遍历两个矩阵的所有位置，统计不同字符的数量
异或运算: ^ 用于比较字符是否不同
返回值: 不同位置数量乘以权重w

node: 存储连接关系的结构体(x为当前节点，y为父节点)
ans: 存储最小生成树的边
k: 矩阵总数
res: 总成本
cnt: 已选择边的数量
vis: 访问标记数组
dis: 距离数组(第一个元素是最小距离，第二个是父节点)

初始化tot为无穷大，p为0（代表无有效节点）
遍历所有节点j（从1到k）
查找满足以下条件的节点：
!vis[j]: 未被访问过的节点
dis[j].first < tot: 当前距离比已知最小距离更小
更新tot为找到的最小距离，p为对应节点编号

如果p == 0，说明没有找到任何未访问的节点
这通常发生在图不连通的情况下
继续下一轮循环

res += tot: 将当前边的权重加到总成本中
vis[p] = true: 将节点p标记为已加入MST
ans[++cnt] = {p, dis[p].second}: 记录这条边的两个端点
p: 当前加入的节点
dis[p].second: 与p相连的父节点

遍历所有节点j
计算节点p和j之间的距离：ct(p, j)
如果新距离比当前记录的最小距离更短：
dis[j].first = sum: 更新最短距离
dis[j].second = p: 更新父节点为p
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= (n); ++i)
#define ii pair<int,int>
using namespace std;

constexpr int N = 10100, M = 20, inf = 1e5;

int n, m, w;
char c[N][M][M];
inline int ct(const int &a, const int &b) {
    int cnt = 0, i, j;
    rep(i,n) rep(j,m) if (c[a][i][j]^c[b][i][j]) ++cnt;
    return cnt * w;
}

struct node { int x, y; };
vector<node> ans(N);
int k, res, cnt;
vector<bool> vis(N);
ii dis[N];
void get() {
    int i, j;
    rep(i,k) {
        int tot = inf, p = 0;//无有效节点
        rep(j,k) if (!vis[j] && dis[j].first < tot)
            tot = dis[j].first, p = j;
        if (p == 0) continue;
        res += tot;
        vis[p] = true;
        ans[++cnt] = {p, dis[p].second};
        rep(j,k) {
            if (const int sum = ct(p, j); sum < dis[j].first)
                dis[j].first = sum, dis[j].second = p;
        }
    }
}


int main() {
    fast;
    cin >> n >> m >> k >> w; int i, j, p;
    rep(i,k) dis[i].first = n*m;
    rep(i,k) rep(j,n) rep(p,m) cin >> c[i][j][p];
    get();
    cout << res << '\n';//总权重
    rep(i,cnt) cout << ans[i].x << ' ' << ans[i].y << '\n';//边的连接关系
    return 0;
}