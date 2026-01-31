//
// Created by Psy.C on 2026/1/31.
//
/**
* 如果fa[x]==x说明x是根节点，返回x
否则递归查找根节点并压缩路径
 *将每个节点的父节点设为自己
 *
 *起点x、终点y、权值v
*n: 节点总数
m: 边总数
k: 组数
a[i]: 第i组的节点数
 *
*x=type[e[i].x]表示边起点所属的组
y=type[e[i].y]表示边终点所属的组
更新组间最短距离
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100000
#define M 505
#define inf 1000000000
using namespace std;

int fa[N+5];
int find(const int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void init() { for (int i = 1; i <= N; ++i) fa[i] = i; }

struct node { int x, y, v; } e[N+5];
int n, m, k, a[N+5];
void input() {
    cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> e[i].x >> e[i].y >> e[i].v;
}

void uni(int x, int y) {
    x = find(x); y = find(y);
    if (x != y) fa[x] = y;
}

int type[N+5];//每个节点属于哪个组
void get() {
    ///i：当前处理的组编号（从1到k）
    ///t：累计已处理的节点数（前i-1组的节点总数）
    for (int i = 1, t = 0; i <= k; ++i) {
        type[t+1] = i;//当前组的第一个节点标记为属于组i
        ///j：当前处理的节点编号
        ///从t+2开始（组的第二个节点）到t+a[i]结束（当前组的最后一个节点）
        ///遍历当前组除第一个节点外的所有节点
        for (int j = t + 2; j <= t + a[i]; ++j) {
            type[j] = i;//将当前节点j标记为属于组i
            //节点j和当前组的第一个节点(t+1)是否在同一连通分量中
            ///find(j)：节点j所在集合的根节点
            ///find(t + 1)：当前组首节点所在集合的根节点
            if (find(j) != find(t + 1)) {
                cout << "No";
                exit(0);
            }
        }
        t += a[i];//当前组的节点数a[i]加到累计节点数t上
    }
}

int dp[M][M];
void init_dp() {
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j) dp[i][j] = inf;
        dp[i][i] = 0;//自己到自己的距离设为0
    }
}

void floyd() {
    for (int t = 1; t <= k; ++t)//以中间节点t为中介更新所有最短距离
        for (int i = 1; i <= k; ++i)
            for (int j = 1; j <= k; ++j)
                dp[i][j] = min(dp[i][j], dp[i][t]+dp[t][j]);
}

void out() {
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (dp[i][j] == inf) cout << "-1 ";
            else cout << dp[i][j] << ' ';//输出实际距离
        }
        cout << '\n';
    }
}

int main() {
    fast;
    init(); input();
    //权值为0的边对应的节点在并查集中合并
    for (int i = 1; i <= m; ++i) if (e[i].v == 0) uni(e[i].x, e[i].y);
    get(); cout << "Yes\n"; init_dp();
    for (int i = 1; i <= m; ++i) {
        const int x = type[e[i].x], y = type[e[i].y];
        dp[x][y] = dp[y][x] = min(dp[x][y], e[i].v);
    }
    floyd(); out();
    return 0;
}