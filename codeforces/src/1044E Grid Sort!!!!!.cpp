//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
康托展开：把 9! 种排列映射成 0..362879 整数，作为 BFS 状态。
定义 8 种"2×2 子块"的旋转/位移方式（dx[i][*],dy[i][*] 是第 i 种操作对 4 个格子的坐标偏移）。get(a,id) 执行第 id 种 2×2 顺时针/逆时针移动
dx[id][*]、dy[id][*] 是第 id 种操作涉及的 4 个格子坐标。
它把 4 个格子的数字做一次轮换（最后一个移到第一个，其余顺移）。
因为 2×2 旋转 = 4 格轮换，i 与 i^4 是互为反向的操作（所以 BFS 里 get(a,i) 之后用 get(a,i^4) 把棋盘转回来）
预计算阶段（离线）‍：对 3×3 目标态，BFS 求解所有 9! 状态到目标的最短路（记录前驱 lst 和所用操作 ap）。再枚举 3×3 内任意两格置换，通过 lst 回溯得到"只用 2×2 旋转把这两格交换、且至多影响这两格"的操作序列，存入 tr[][][][]。

这是配置表：tr[i][j][k][l] = 在 3×3 中把 (i,j) 与 (k,l) 两格交换所需的最小操作序列（该序列是"局部置换"，不破坏周围其它已排好的格子）
move(vi,vi)：在一对坐标数组（4格）上做旋转并记录操作（v.push_back）。
move(x,y,id)：在位置 (x,y) 执行第 id 种 2×2 旋转。
move(x,y,X,Y)：将两格 (x,y) 与 (X,Y) 交换——通过 tr 表（前提：它们被平移到同一 3×3 局部）还原。
贪心逐步归位：对每个目标位置 i，找到数字 i+1 当前所在 (X,Y)，用 rw/lw/up 把它一步步移动到目标 (x,y)（每移动都做一次 2×2 旋转并记录）。这样按顺序把每个数字归位到正确格子
输出所有执行过的 2×2 旋转（移动序列），格式为"每组 4 个坐标"。


a[i] 表示第 i 个位置放的数字。
这是康托展开的变体：对每个 i，统计后面比 a[i] 小的个数（逆序对），乘以对应阶乘，累加得到唯一序号。
所以 code 把 {0,1,2,...,8} 这个有序排列编码成唯一整数。

a[i] = val % (9-i)：取余数得到系数 c_i。
val /= 9-i：去掉这一位，继续提下一位。
ch[i]=0：顺手清零标记数组。
注意：这里 a[i] 暂时存的是系数（不是最终数字），第二步才把它们转成真实排列。
外层遍历位置 i，对每个位置：

j 从小到大找第一个未使用且满足条件的数字。
关键逻辑是 !a[i]--：先判断 a[i] 是否为 0，再让 a[i] 减 1；若为 0 则满足，把 a[i] 还原成真实数字 j；若不为 0，则 a[i] 减 1 后跳到下一个 j 继续。
具体地，对位置 i：

当前 a[i] 是一个系数 c，含义是：在所有剩余未用数字中，选第 c 小的那个。
内层 j 从 0 开始逐个扫：
若 ch[j] 为 true（已用）跳过。
否则若 a[i]==0 → 当前 j 就是"第 0 小"，选中 j，标记已用。
若 a[i]>0 → a[i]-- 后继续看下一个未用 j，直到减到 0 就选中当时那个 j
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<(n); i++)
#define per(i,n) for (int i=n; i>=0; i--)
#define vi vector<int>
using namespace std;

constexpr int N = 362880, M = 1e3;


int code(int *a) {
    int ret = 0;
    rep(i,9) {
        ret = 1ll*ret*(9-i);
        for (int j = i+1; j < 9; j++) ret += a[i] > a[j];
    }
    return ret;
}
void decode(int val, int *a) {
    static bool ch[9];
    per(i,8) a[i] = val%(9-i), val /= 9-i, ch[i] = 0;
    rep(i,9) rep(j,9)
        if (!ch[j] && !a[i]--) { a[i] = j; ch[j] = 1; break; }
}

int dx[][4] = {
    {0,0,1,1},{0,0,1,1},{1,1,2,2},{1,1,2,2},
    {0,1,1,0},{0,1,1,0},{1,2,2,1},{1,2,2,1}
}, dy[][4] = {
    {0,1,1,0},{1,2,2,1},{0,1,1,0},{1,2,2,1},
    {0,0,1,1},{1,1,2,2},{0,0,1,1},{1,1,2,2}
};



void get(int *a, int id) {
    int t = a[dx[id][3]*3 + dy[id][3]];
    per(i,2) a[dx[id][i+1]*3 + dy[id][i+1]] = a[dx[id][i]*3 + dy[id][i]];
    a[dx[id][0]*3 + dy[id][0]] = t;
}

int dis[N], a[9], ap[N], lst[N];
queue<int> q;
vi tr[3][3][3][3];
void bfs() {
    memset(dis,-1,sizeof(dis)); dis[0] = 0; q.push(0);
    while (!q.empty()) {
        int x = q.front(), y; q.pop();
        decode(x, a);
        rep(i,8) {
            get(a,i); y = code(a);//新棋盘 → 新序号
            if (dis[y] == -1)//首次到达 → 记录最短路
                dis[y] = dis[x] + 1, lst[y] = x, ap[y] = i, q.push(y);
            get(a, i^4);//回转棋盘，恢复现场
        }
    }
    rep(i,3) rep(j,3) rep(k,3) rep(l,3) {
        if (i == k && j == l) continue;//跳过同一格
        rep(t,9) a[t] = t;//用目标棋盘当"现场"
        swap(a[i*3+j], a[k*3+l]);//手动交换这两格 → 造一个"错位态"
        int x = code(a);//编码成状态序号
        //从该错位态回溯到目标态 记录用到的操作
        while (x) tr[i][j][k][l].push_back(ap[x]), x = lst[x];//沿前驱链
        ranges::reverse(tr[i][j][k][l]);//复盘 → 正向操作序列
    }
}

int b[M], m;
vector<vi> v;
void move(vi x, vi y) {
    vi u;
    rep(i,4) u.push_back(b[x[i]*m+y[i]]);
    v.push_back(u);
    int tmp = b[x[3]*m+y[3]];
    per(i,2) b[x[i+1]*m+y[i+1]] = b[x[i]*m+y[i]];
    b[x[0]*m+y[0]] = tmp;
}
void move(int x, int y, int id) {
    vi X(4), Y(4);
    rep(i,4) X[i] = dx[id][i] + x, Y[i] = dy[id][i] + y;
    move(X, Y);
}
void move(int x, int y, int X, int Y) {
    int xx = max(0, max(x, X)-2), yy = max(0, max(y, Y)-2);//平移避免越界
    x -= xx, y -= yy; X -= xx, Y -= yy;
    for (auto i : tr[x][y][X][Y]) move(xx, yy, i);//执行预计算的置换序列
}

int n;
void rw(int &x, int &y) {//向右挪动当前目标，同时 2×2 旋转
    if (x == n-1) move(x, y, x, y+1);
    else move({x,x,x+1,x+1}, {y,y+1,y+1,y});
    y++;
}
void lw(int &x, int &y) {
    if (x == n-1) move(x, y, x, y-1);
    else move({x,x,x+1,x+1}, {y,y-1,y-1,y});
    y--;
}
void up(int &x, int &y) {
    if (y == m-1) move(x, y, x-1, y);
    else move({x-1,x-1,x,x}, {y,y+1,y+1,y});
    x--;
}


int main() {
    fast;
    bfs(); cin >> n >> m;
    rep(i,n) rep(j,m) cin >> b[i*m+j];
    rep(i,n*m) {
        int x = i/m, y = i%m, X, Y;//目标位置 i 应在的格子
        for (int j = i; j < n*m; j++)
            if (b[j] == i+1) X = j/m, Y = j%m;
        if (x == X && y == Y) continue;
        if (X == n-1 && x < n-2) up(X, Y);//特殊处理最后一行
        while (Y < y) rw(X, Y);//把该数字平移到目标列
        while (Y > y) lw(X, Y);
        while (X > x) up(X, Y);//再平移到目标行
    }
    cout << v.size() << '\n';
    for (const auto& i : v) {
        cout << i.size() << ' ';//每组操作的格数（4）
        for (auto j : i) cout << j << ' ';//被移动的编号
        cout << '\n';
    }
    return 0;
}