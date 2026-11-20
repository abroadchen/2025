//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
越界检查：x&&y&&x<N&&y<N → 要求 x、y 都在 [1, N-1]（即 1..999）
判断 (a,b) 与 (c,d) 是否八方向相邻（切比雪夫距离为 1）
若要去的格子 (c,d) 已被敌方占据，则从它周围 8 邻居里找一个"你也相邻"的格子上前"吃"掉它 → exit(0)（游戏结束）。
否则移动过去，读回某个敌方棋子的新坐标并更新 vis
把玩家从当前 (p,q) 斜线/直线逼近到目标 (a,b)：
每步往目标方向走一格（切比雪夫直线接近），每次走都带上"吃"检测。
先冲到中心，统计四个角区域敌人的数量。
敌人最少的那个区域（mn）对应的对角角点胜出——即优先把玩家赶到"敌人最少的对角"，从而逼对面敌人聚集区被"踩"到。
持续 run 逼近，期间 go 不断尝试吃。
游戏结束条件：吃掉（exit(0) 于 go 中）或交互方发送 id<0
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
using namespace std;

constexpr int N = 1e3, M = 5e2;

bool check(int x, int y) { return x&&y&&x<N&&y<N; }
bool ok(int a, int b, int c, int d) { return max(abs(a-c),abs(b-d)) == 1; }

bitset<N+5> vis[N+5];
int dx[] = {1,1,1,0,-1,-1,-1,0}, dy[] = {1,0,-1,1,1,0,-1,-1};
int id, px, py, p, q, x[N+5], y[N+5];
void go(int a, int b, int c, int d) {
    if (vis[c][d]) rep(i,0,7) {
        int nx = c + dx[i], ny = d + dy[i];
        if (check(nx,ny)&&ok(a,b,nx,ny))
            cout << nx << ' ' << ny << endl, cin >> id >> px >> py, exit(0);
    }
    cout << c << ' ' << d << endl, p = c, q = d;//否则移动到 (c,d)
    cin >> id >> px >> py;//读回敌方某棋子的新位置
    if (id < 0) exit(0);//交互结束
    // 旧位置清空 更新该棋子新坐标 新位置标记
    vis[x[id]][y[id]] = 0, x[id] = px, y[id] = py, vis[x[id]][y[id]] = 1;
}
void run(int a, int b) {
    while (p^a || q^b) {
        //x 方向朝 a 挪一步  y 方向朝 b 挪一步
        int nx = p+(p<a?1:(p>a?-1:0)), ny = q+(q<b?1:(q>b?-1:0));
        go(p,q,nx,ny);
    }
}

int c1, c2, c3, c4;
void solve() {
    cin >> p >> q;//读初始玩家位置
    rep(i,1,666) cin >> x[i] >> y[i], vis[x[i]][y[i]] = 1;//读 666 个敌人坐标
    run(M,M);//先冲到中心 (500,500)
    //统计四个象限(角区)里各有多少敌人
    rep(i,1,M-1) rep(j,1,M-1) c1 += vis[i][j];//左上(1..499 × 1..499)
    rep(i,M+1,N-1) rep(j,1,M-1) c2 += vis[i][j];//右上
    rep(i,1,M-1) rep(j,M+1,N-1) c3 += vis[i][j];//左下
    rep(i,M+1,N-1) rep(j,M+1,N-1) c4 += vis[i][j];//右下
    //把敌人最少(最空)的角清空,即把敌人往该角赶? 其实是最少的那边先丢 → 逼到对面人多角
    int mn = min({c1,c2,c3,c4});
    if (c1 == mn) run(N-1,N-1);//冲到右下
    if (c2 == mn) run(1,N-1);
    if (c3 == mn) run(N-1, 1);
    if (c4 == mn) run(1,1);
}

int main() {
    fast;
    solve();
    return 0;
}