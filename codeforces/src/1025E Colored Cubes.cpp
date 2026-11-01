//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
h[x][y]：棋盘哈希，记录格子上是谁，0 表示空格。
x[i], y[i]：维护每个棋子当前坐标（随移动实时更新）
cnt 步数
move 做三件事：记录步骤 → 更新棋盘哈希 → 更新棋子坐标。这就是所有移动的唯一出口
t1(x,y,fx)：想把格子 (x,y) 上的棋子沿方向 fx（±1）推一格到 y+fx。
若目标格越界 → 失败。
若目标格是空格 → 成功。
否则目标格有棋子 → 递归先把这个 前方的棋子 沿同方向推走，腾出空位，再移动自己。
这就是"连锁挪动"：像推箱子里把一串方块整体往一个方向推。
t12：先试右推，失败再试左推。注意：t1 是横向（改 y 坐标），列方向不变
t2(x,y,fx)：想把 (x,y) 上的棋子纵向推一格到 x+fx（改 x 坐标）。
t22：先试向上（x-1），失败再试向下
让棋子 i 沿水平方向一步步逼近 mx。
每一步：先令目标格为空格（t12 连锁挪走挡路的），再 move 一步
让棋子 i 沿垂直方向一步步逼近 my
每次随机一种移动顺序（shuffle），并随机选择"先 f1 后 f2"或相反。
对所有棋子依次尝试搬运到位。
用 check() 判断是否全部到位，若没有就再来一轮随机，直到成功。
因为空格足够多，随机化贪心大概率在若干轮内收敛，得到一组合法解
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i = 1; i <= n; i++)
using namespace std;

constexpr int N = 60, M = 1e5+1e3;

tuple<int,int,int,int> ans[M];//记录一步移动：from(x,y) -> to(u,v)
int cnt, h[N][N], x[N], y[N];
void move(int x, int y, int u, int v) {
    ans[++cnt] = {x,y,u,v};//记录一步
    int id = h[x][y];//取出被移动的棋子编号
    h[x][y] = 0, h[u][v] = id;//原格清空 新格放置
    ::x[id] = u, ::y[id] = v;//更新该棋子当前坐标（用::避免与形参重名）
}

int n;
bool t1(int x, int y, int fx) {//尝试把 (x,y) 上棋子向右(fx=1)或左(fx=-1)推
    if (x < 1 || x > n || y < 1 || y > n) return 0;//越界
    if (h[x][y] == 0) return 1;//目标格是空格，可行（递归出口）
    if (t1(x,y+fx,fx)) { move(x,y,x,y+fx); return 1; }//递归挪走前方的，再挪自己
    return 0;
}
void t12(int x, int y) {
    if (t1(x,y,1)) return;//先试向右
    t1(x,y,-1);//不行再试向左
}
bool t2(int x, int y, int fx) {
    if (x < 1 || x > n || y < 1 || y > n) return 0;
    if (h[x][y] == 0) return 1;
    if (t2(x+fx,y,fx)) { move(x,y,x+fx,y); return 1; }
    return 0;
}
void t22(int x, int y) {
    if (t2(x,y,-1)) return;
    t2(x,y,1);
}

int xx[N], yy[N];
void f1(int i) {
    int x = ::x[i], y = ::y[i], mx = xx[i], my = yy[i];//当前坐标、目标坐标
    while (x < mx) {//目标列在右边 → 向右走
        int u = x + 1, v = y;
        t12(u, v); move(x,y,u,v);//先给目标格 (u,v) 腾出空格
        x = u, y = v;
    }
    while (x > mx) {//目标列在左边 → 向左走
        int u = x - 1, v = y;
        t12(u, v); move(x,y,u,v);
        x = u, y = v;
    }
}
void f2(int i) {
    int x = ::x[i], y = ::y[i], mx = xx[i], my = yy[i];
    while (y < my) {
        int u = x, v = y + 1;
        t22(u,v); move(x,y,u,v);
        x = u, y = v;
    }
    while (y > my) {
        int u = x, v = y - 1;
        t22(u,v); move(x,y,u,v);
        x = u, y = v;
    }
}

int m;
bool check() {
    rep(i,m) if (x[i] != xx[i] || y[i] != yy[i]) return 0;
    return 1;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}
template<typename T,typename...Args>
void write(const T x,const Args...y) {
    write(x),putchar(' '),write(y...),sizeof...(y)==1?putchar('\n'):0;
}

int ux[N], uy[N], p[N];
mt19937 rng(20120515);//梅森旋转随机数种子（固定）
int main() {
    read(n,m);
    rep(i,m) read(x[i],y[i]), h[x[i]][y[i]] = i, ux[i] = x[i], uy[i] = y[i], p[i] = i;
    rep(i,m) read(xx[i],yy[i]);
    while (!check()) {//只要还没全部到位，就反复试
        shuffle(p+1,p+1+m,rng);
        rep(i,m) {
            int id = p[i];
            if (rng()&1) f1(id), f2(id);//随机选：先调行再调列
            else f2(id), f1(id);
        }
    }
    write(cnt), putchar('\n');
    rep(i,cnt) write(get<0>(ans[i]), get<1>(ans[i]), get<2>(ans[i]), get<3>(ans[i]));
    return 0;
}