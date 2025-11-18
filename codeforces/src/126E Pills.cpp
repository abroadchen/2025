//
// Created by Psy.C on 2025/11/18.
//
/*
*cl[][]: 存储网格中每个位置的颜色
cnt[]: 每种颜色对的需求量
rl[][]: 记录连接状态（1=垂直连接，2=水平连接，-1=被连接，0=未连接）
 *
*dis[]：距离数组，lst[]：前驱边数组，pos[]：当前弧数组
v[]：邻接表，存储每个节点的出边
 *
 *s[]：输入网格，ans[]：输出结果，sc[]：颜色对字符串数组
*tx[], ty[]：边索引数组
txy[][]：交叉边索引
rcnt[]：实际连接计数
nc[], nr[]：列/行剩余容量
 *
*st：状态集合，用于去重
to[]：连接目标数组
 *
 */
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#define rep(i,n) for(int i=0;i<(n);++i)
#define sz(x) ((int)(x).size())
using namespace std;

typedef long long ll;
constexpr int inf = 0x3f3f3f3f;
const int id[][4] = {//将不同颜色组合映射到编号0-9
    {3,2,1,0},
    {2,6,5,4},
    {1,5,8,7},
    {0,4,7,9}
};

int n, m, mxc;
template<int N, int M>//N为节点数，M为边数
struct mf {
    int s, t, n, cnt;//源点 s，汇点 t，节点数 n，边计数器 cnt
    struct edge {
        int a, b, w;//起点 a，终点 b，容量 w
        void assign(int _a, int _b, int _w) { a = _a; b = _b; w = _w; }
    } e[M<<1];//存储边 正向边和反向边
    int dis[N], lst[N], pos[N];
    vector<int> v[N];
    bool bfs() {
        queue<int> q; q.push(s);
        rep(i,n) dis[i] = inf; dis[s] = 0;//源点距离为 0
        while (!q.empty()) {//寻找增广路径
            int x = q.front(); q.pop();
            for (int i : v[x]) if (e[i].w) {//有剩余容量且能松弛距离，则更新并入队
                int y = e[i].b;
                if (dis[y] > dis[x] + 1) {
                    lst[y] = i;
                    dis[y] = dis[x] + 1;
                    q.push(y);
                }
            }
        }
        return dis[t] < inf;//返回能否到达汇点
    }
public:
    void init(int _s, int _t, int _n) { s = _s; t = _t; n = _n; cnt = 0; }
    int addedge(int a, int b, int w) {
        int ct = cnt;
        v[a].push_back(cnt);
        e[cnt++].assign(a, b, w);
        v[b].push_back(cnt);
        e[cnt++].assign(b, a, 0);
        return ct;//返回正向边的索引
    }
    int dfs(int u, int fl) {//寻找增广路流量
        if (fl == 0) return 0;//如果流量为 0 或到达汇点，返回相应值
        if (u == t) return fl;
        int sum = 0;
        for (int& i = pos[u]; i < sz(v[u]); i++) if (dis[e[v[u][i]].b] == dis[u] + 1) {
            int j = v[u][i], w = dfs(e[j].b, min(fl - sum, e[j].w));
            sum += w;
            e[j].w -= w;
            e[j^1].w += w;
            if (fl - sum == 0) break;
        }
        return sum;
    }
    int calc() {
        int ans = 0;
        while (bfs()) { rep(i,n) pos[i] = 0; ans += dfs(s, inf); }
        return ans;
    }
};
mf<25,300> g;
string s[10], ans[20], sc[] = {//10种颜色对组合
    "BY", "BW", "BR", "BB", "RY",
    "RW", "RR", "WY", "WW", "YY"
};
int cl[10][10], cnt[10], rl[10][10],
tx[10], ty[10], txy[10][10], rcnt[10],
nc[10], nr[10];
set<int> st;
vector<int> to[10];

void dfs(int x, int y) {//枚举所有连接方案
    if (x == n) {//到达网格末尾
        int hs = 0;//计算哈希值用于状态去重
        rep(i,10) hs = hs << 6 | rcnt[i];
        if (st.count(hs)) return;//如果已存在该状态则返回
        st.insert(hs);
        rep(i,10) rep(j,10) if (~txy[i][j]) {
            g.e[txy[i][j]].w = inf;//设置交叉边容量为无穷大
            g.e[txy[i][j]^1].w = 0;
        }
        int cs = 0;//计算直接匹配数量
        rep(i,10) {//设置源汇边容量
            int rx = min(rcnt[i], cnt[i]);
            cs += rx;
            g.e[tx[i]].w = nr[i] = rcnt[i] - rx;
            g.e[tx[i]^1].w = 0;
            g.e[ty[i]].w = nc[i] = cnt[i] - rx;
            g.e[ty[i]^1].w = 0;
        }
        int cur = cs * 2 + g.calc();//计算当前解的价值
        if (cur <= mxc) return;
        mxc = cur;//更新最优解
        rep(i,10) {//构建连接方案：先处理直接匹配
            to[i].clear();
            int rx = min(rcnt[i], cnt[i]);
            rep(_,rx) to[i].push_back(i);
            rep(j,10) if (~txy[i][j]) {//再处理通过交叉边的匹配
                rx = g.e[txy[i][j]^1].w;
                nr[i] -= rx; nc[j] -= rx;
                rep(_,rx) to[i].push_back(j);
            }
        }
        rep(i,10) rep(j,10) {//处理剩余的匹配
            int rx = min(nr[i], nc[j]);
            nr[i] -= rx; nc[j] -= rx;
            rep(_,rx) to[i].push_back(j);
        }
        int sp[10] = {};//初始化答案数组和指针数组
        rep(i,n*2-1) ans[i] = string(m*2-1, '.');
        rep(i,n) rep(j,m) {
            if (rl[i][j] == 1) {//处理垂直连接：绘制竖线，分配颜色对
                ans[i*2+1][j*2] = '|';
                int cid = id[cl[i][j]][cl[i+1][j]],
                rp = to[cid][sp[cid]++];
                if (s[i][j] != sc[rp][0] && s[i+1][j] != sc[rp][1]) {
                    ans[i*2][j*2] = sc[rp][1];
                    ans[i*2+2][j*2] = sc[rp][0];
                } else {
                    ans[i*2][j*2] = sc[rp][0];
                    ans[i*2+2][j*2] = sc[rp][1];
                }
            }
            if (rl[i][j] == 2) {//处理水平连接：绘制横线，分配颜色对
                ans[i*2][j*2+1] = '-';
                int cid = id[cl[i][j]][cl[i][j+1]],
                rp = to[cid][sp[cid]++];
                if (s[i][j] != sc[rp][0] && s[i][j+1] != sc[rp][1]) {
                    ans[i*2][j*2] = sc[rp][1];
                    ans[i*2][j*2+2] = sc[rp][0];
                } else {
                    ans[i*2][j*2] = sc[rp][0];
                    ans[i*2][j*2+2] = sc[rp][1];
                }
            }
        }
        return;
    }
    if (y == m) { dfs(x + 1, 0); return; }//如果处理完一行，进入下一行
    if (rl[x][y]) { dfs(x, y + 1); return; }//如果当前位置已有连接，处理下一个位置
    if (!rl[x+1][y]) {// 垂直连接
        rl[x][y] = 1; rl[x+1][y] = -1;
        rcnt[id[cl[x][y]][cl[x+1][y]]]++;
        dfs(x, y+1);
        rcnt[id[cl[x][y]][cl[x+1][y]]]--;
        rl[x][y] = rl[x+1][y] = 0;
    }
    if (!rl[x][y+1]) {//水平连接
        rl[x][y] = 2; rl[x][y+1] = -1;
        rcnt[id[cl[x][y]][cl[x][y+1]]]++;
        dfs(x, y+1);
        rcnt[id[cl[x][y]][cl[x][y+1]]]--;
        rl[x][y] = rl[x][y+1] = 0;
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    n = 7, m = 8;
    rep(i,n) {
        cin >> s[i];
        rep(j,m) {
            char c = s[i][j];
            if (c == 'B') cl[i][j] = 0;//将颜色映射为数字
            if (c == 'R') cl[i][j] = 1;
            if (c == 'W') cl[i][j] = 2;
            if (c == 'Y') cl[i][j] = 3;
        }
    }
    rep(i,10) cin >> cnt[i];//每种颜色对的需求量
    rep(i,10) rep(j,10) if (i >= n || j >= m) rl[i][j] = 1;//设置边界条件
    g.init(20, 21, 22);//源点 20，汇点 21，共 22 个节点
    rep(i,10) tx[i] = g.addedge(20, i, 0);//添加源点到各颜色节点的边
    rep(i,10) ty[i] = g.addedge(i+10, 21, 0);//添加各颜色节点到汇点的边
    rep(i,10) rep(j,10) txy[i][j] = -1;//初始化交叉边索引为 -1
    rep(i,4) rep(j,4) rep(k,4) {//添加颜色间的交叉边
        int x = id[i][j], y = id[j][k];
        if (x != y && txy[x][y] < 0) txy[x][y] = g.addedge(x, y+10, 0);
    }
    mxc = -1;
    dfs(0, 0);
    cout << mxc << '\n';//输出最优解价值和连接方案
    rep(i,n*2-1) cout << ans[i] << '\n';
    return 0;
}