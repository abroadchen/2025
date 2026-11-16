//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
输入 n 个点、m 条边路径，每条路径给出 l 个点。
路径上相邻两点连边，dis 初始化为 n（表示"无穷大"），直连边 dis=1，dis[i][i]=0。
之后跑 Floyd（三层 k,i,j 那个）求全源最短路径。
这里的 dis 是"已知的图"，用于后面交互时的距离比较
候选集 c：所有可能成为目标 q 的点，初始为全部 n 个点。
选择查询点 rt：对每个点 x，计算其"最差情况"——对每个邻居 y，统计候选集里"目标比 y 更远"（dis[x][z] > dis[y][z]）的候选数量，取这些的最大值 mx；选择 mx 最小的 x 作为查询点（类似"最小化最大分支"的决策树思想）。
交互询问 rt：
若返回 FOUND，说明 rt 就是目标，结束本轮。
否则评测机返回 res（它声称"离目标最近的点/路径上的点"），于是把候选集收缩为：那些 dis[rt][x] > dis[res][x] 的点（即"离 res 比离 rt 更近"的候选）——因为目标肯定在靠近 res 的方向，从而剪掉一半候选，进入下一轮。
反复直到命中，再处理下一个点 q
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
#define vi vector<int>
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<vi> dis(n, vi(n,n)), e(n);
    rep(i,n) dis[i][i] = 0;
    while (m--) {
        int l; cin >> l;
        int lst = -1;
        while (l--) {
            int x; cin >> x; --x;
            if (~lst) {
                e[lst].push_back(x); e[x].push_back(lst);
                dis[x][lst] = dis[lst][x] = 1;
            }
            lst = x;
        }
    }
    rep(k,n) rep(i,n) rep(j,n) dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
    rep(q,n) {//对每个点 q 执行一轮"定位"
        vi c(n);
        rep(i,n) c.push_back(i);//候选集，初始为全部点
        while (1) {
            int rt = -1, rem = n;
            rep(x,n) {//枚举每个点 x 作为候选查询点
                int mx = 0;
                for (auto y : e[x]) {//对 x 的每个邻居 y
                    int cur = 0;
                    for (auto z : c) if (dis[x][z] > dis[y][z]) ++cur;//统计比 dist(y) 更远的候选
                    mx = max(mx, cur);
                }
                if (rem > mx) { rem = mx; rt = x; }
            }
            cout << rt+1 << endl;
            string t; cin >> t;
            if (t == "FOUND") break;
            int res; cin >> res; --res;//得到"离目标最近的邻居"之一
            vi now;//收缩候选集
            for (auto x : c) if (dis[rt][x] > dis[res][x]) now.push_back(x);
            swap(c, now);
        }
    }
    return 0;
}