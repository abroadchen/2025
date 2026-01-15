//
// Created by Psy.C on 2026/1/14.
//
/**
* n: 节点总数
b[N]: 每个节点的特殊标记数组
x: 临时变量
vis[N]: 访问计数数组
 *g[i]存储节点i指向的节点
 *dis[N]: 存储从每个节点开始的路径序列
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;


int main() {
    fast;
    int n, b[N], x, vis[N]; cin >> n;
    vector<int> g[N], dis[N];
    rep(i,n) cin >> b[i];
    rep(i,n) {
        cin >> x;//读入节点i指向的目标节点
        if (x != 0) { g[i].push_back(x); vis[x]++; }//目标节点存在 在邻接表中添加边i->x  统计节点x的入度
    }
    rep(i,n) if (b[i] != 0) {
        dis[i].push_back(i);//将起始节点i加入路径
        if (g[i].empty()) continue;//如果没有出边，跳过
        int y = g[i][0];//获取从i出发的第一个节点
        while (true) {//遍历路径
            if (b[y] == 1) break;//遇到b[y]=1的节点 停止
            if (vis[y] > 1) break;//遇到入度大于1的节点，停止（避免重复访问）
            if (g[y].empty()) {//y没有出边
                dis[i].push_back(y);//添加y并跳出
                break;
            }
            dis[i].push_back(y);//添加当前节点到路径
            y = g[y][0];// 移动到下一个节点
        }
    }
    int ans = -1;
    rep(i,n) ans = max(ans, static_cast<int>(dis[i].size()));
    cout << ans << '\n';//最长路径的长度
    rep(i,n) if (dis[i].size() == ans) {
        for (int j = static_cast<int>(dis[i].size()) - 1; j >= 0; --j)
            cout << dis[i][j] << ' ';//输出路径上的节点（反向输出）
        break;
    }
    return 0;
}