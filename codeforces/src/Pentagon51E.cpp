//
// Created by Psy.C on 2025/10/15.
//
/*
*n: 节点数
m: 边数
e[N][N]: 邻接矩阵，e[i][j]=1表示节点i和j之间有边
cnt[N][N]: 计数矩阵，cnt[i][j]表示与节点i和j都相连的公共邻居数
deg[N]: 度数数组，deg[i]表示节点i的度数（连接的边数）
 *
*读入m条边，对于每条边：
在邻接矩阵中标记两点相连（无向图，所以双向标记）
更新两个节点的度数
 *
*计算任意两点间的公共邻居数：
三层循环遍历所有三元组(i,j,k)
如果节点i与k相连且节点k与j相连，则k是i和j的公共邻居
增加cnt[i][j]的计数
 *
*初始化答案为0
三层循环遍历所有三元组(i,j,k)
跳过相同节点的情况
确保j和k之间有边（构成三角形的一部分）
 *
*核心计算：统计包含节点i,j,k的四元组数量
(cnt[i][j] - e[i][k])：与i和j都相连但不包括k的节点数
(cnt[i][k] - e[i][j])：与i和k都相连但不包括j的节点数
两者相乘得到可以形成4-cycle的数量
 *
*特殊情况处理：如果i与j、k都相连
需要减去重复计算的部分
 *输出结果除以10（因为每个4-cycle被重复计算了10次）
 *
 *时间复杂度为O(n³)，空间复杂度为O(n²)。
 *
 *
 */
#include <ios>
#include <iostream>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;
typedef long long ll;
const int N = 707;
int n, m, e[N][N], cnt[N][N], deg[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    rep(i,m) {
        int a, b; cin>>a>>b;
        e[a][b] = e[b][a] = 1;
        deg[a]++, deg[b]++;
    }
    rep(i,n) rep(j,n) rep(k,n) if (e[i][k] && e[k][j]) cnt[i][j]++;
    ll ans(0);
    rep(i,n) rep(j,n) {
        if (i == j) continue;
        rep(k,n) {
            if (i == k || j == k) continue;
            if (!e[j][k]) continue;
            ans += (cnt[i][j] - e[i][k]) * (cnt[i][k] - e[i][j]);
            if (e[i][j] && e[i][k]) ans -= deg[i] - 2;
        }
    }
    cout << ans/10 << endl;
    return 0;
}