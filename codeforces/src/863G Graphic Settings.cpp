//
// Created by Psy.C on 2026/10/4.
//
/**
宏把二维下标 (x,y) 线性化映射为一维索引：(y-1)*a[1]+(x-1)。所以它把网格排成 a[1] 列 × c 行，x∈[1,a[1]] 是第一维（列），y∈[1,c] 是展开后其余维度合成的"第二维"（行）。
方向常量：R=0（右），L=1（左），D=2（下），U=3（上）。g(x,y) 存的是格子 (x,y) 的"下一步方向"。
网格规模：r = a[1]（列数），c = a[2]*a[3]*a[4]*a[5]*a[6]（行数，其余 m-1 维展开成一维）
不足 6 维的维度补为长度 1。
用多重循环枚举除第 1 维外所有维度的组合，按字典序线性化为行号 y（从 1 到 c）。
w(x,y,z)：网格格点 (x,y) 在第 z 维上的实际坐标。它实现了一种蛇形（serpentine）编码：奇数位置正序、偶数位置反序（如 i&1 ? j : a[5]-j+1），把高维坐标转成二维网格。
所以二维网格中相邻移动（上下左右）在真实 m 维空间中也是对相邻格点的移动——这是把商空间映射
给出当前格 (x,y) 与下一个格 (tx,ty)，找出它们在第几个维度上坐标不同，输出该维度的 inc（增大）或 dec（减小）
luh = 左行上蛇（left-up horizontal）：从行首横走到底再向下换行，方向朝右上方向推进。
luv = left-up vertical。
ruh = right-up horizontal。
ruv = right-up vertical。
ldh = left-down horizontal。
ldv = left-down vertical。
rdh = right-down horizontal。
rdv = right-down vertical
第 1 个字母（l/r）= 起点在左/右；第 2 个字母（u/d）= 推进方向向上/向下；第 3 个字母（h/v）= 蛇形主轴为水平/垂直（每行蛇形折返 or 每列蛇形折返
luh(lx,rx,ly,ry)
在 [lx..rx] 行 × [ly..ry] 列子矩形内做行蛇形：奇偶行交错左右扫描，行末向下过渡到下一行。其余 7 个函数是不同角落/方向的变体，用于拼装不同起点的完整路径
dx/dy 对应方向 R(0)、L(1)、D(2、U(3) 的坐标增量
情况 1：一维（m==1）
一维线段：仅起点在端点时可遍历全段（Path）；恰 2 个点时还能往返成 Cycle；起点在中点则 No。
情况 2：多维
把起点 b[] 编码后的 m 维坐标映射回二维网格坐标 (x,y)（x 即 b[1]，y 在网格中搜索匹配行）。
布尔 fe 在 main 中定义：fe |= !(a[i]&1)，即是否存在偶数长度的维度。fe 用来判断能否构成 Cycle。

分支 A：fe 为真 → 输出 Cycle

说明某个维度长度是偶数，故奇偶性可配对，构成哈密顿回路
用蛇形模板铺满整个网格并收尾连回起点，形成回路，输出每一步指令。
分支 B：fe 为假 → 输出 Path（若奇偶性匹配）
网格总格数 r*c，若 r 为奇数且总格数为奇数，则黑白染色（棋盘染色）后起点与终点必须同色才能形成覆盖全部格的路径。这里用 (x^y)&1 判断起点所在格的"颜色"与要求是否矛盾——若奇数总数且起点落在黑色（位运算判相等）会 No。
然后按起点位置（角落 / 边 / 中间奇偶）选择 8 个蛇形模板的组合，铺出一条从起点出发走遍 r*c-1 步的哈密顿路径：
每种情况把网格划分成若干子矩形，用不同方向的蛇形模板覆盖，并手工修补衔接方向，构造起点到终点的完整遍历。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define w(x,y,z) w[(y-1)*a[1]+(x-1)][z-1]
#define g(x,y) g[(y-1)*a[1]+(x-1)]
#define R 0
#define L 1
#define D 2
#define U 3
using namespace std;
constexpr int N = 1e5+5;
int m, a[8], b[8], w[N][8], r, c;
void init() {
    for (int i = m+1; i <= 6; ++i) a[i] = b[i] = 1;
    rep(i,a[6]) rep(j,a[5]) rep(k,a[4]) rep(p,a[3]) rep(q,a[2]) {
        int y = (i-1)*a[5]*a[4]*a[3]*a[2]+(j-1)*a[4]*a[3]*a[2]+(k-1)*a[3]*a[2]+(p-1)*a[2]+q;
        rep(x,a[1]) {
            w(x,y,1) = x;
            w(x,y,2) = ((i-1)*a[5]*a[4]*a[3]+(j-1)*a[4]*a[3]+(k-1)*a[3]+p)&1 ? q : a[2]-q+1;
            w(x,y,3) = ((i-1)*a[5]*a[4]+(j-1)*a[4]+k)&1 ? p : a[3]-p+1;
            w(x,y,4) = ((i-1)*a[5]+j)&1 ? k : a[4]-k+1;
            w(x,y,5) = i&1 ? j : a[5]-j+1;
            w(x,y,6) = i;
        }
    }
    r = a[1], c = a[2]*a[3]*a[4]*a[5]*a[6];
}

inline void go(int x, int y, int tx, int ty) {
    rep(i,m) {
        if (w(x,y,i) != w(tx,ty,i)) {
            if (w(x,y,i) < w(tx,ty,i)) cout << "inc " << i << '\n';
            else cout << "dec " << i << '\n';
            return;
        }
    }
}

int g[N];
inline void luh(int lx, int rx, int ly, int ry) {
    for (int i = lx; i <= rx; i += 2) {
        for (int j = ly; j < ry; ++j) g(i,j) = R;
        g(i,ry) = D;
    }
    for (int i = lx+1; i <= rx; i += 2) {
        for (int j = ry; j > ly; --j) g(i,j) = L;
        g(i,ly) = D;
    }
}
inline void luv(int lx, int rx, int ly, int ry) {
    for (int j = ly; j <= ry; j += 2) {
        for (int i = lx; i < rx; ++i) g(i,j) = D;
        g(rx,j) = R;
    }
    for (int j = ly+1; j <= ry; j += 2) {
        for (int i = rx; i > lx; --i) g(i,j) = U;
        g(lx,j) = R;
    }
}
inline void ruh(int lx, int rx, int ly, int ry) {
    for (int i = lx; i <= rx; i += 2) {
        for (int j = ry; j > ly; --j) g(i,j) = L;
        g(i,ly) = D;
    }
    for (int i = lx+1; i <= rx; i += 2) {
        for (int j = ly; j < ry; ++j) g(i,j) = R;
        g(i,ry) = D;
    }
}
inline void ruv(int lx, int rx, int ly, int ry) {
    for (int j = ry; j >= ly; j -= 2) {
        for (int i = lx; i < rx; ++i) g(i,j) = D;
        g(rx,j) = L;
    }
    for (int j = ry-1; j >= ly; j -= 2) {
        for (int i = rx; i > lx; --i) g(i,j) = U;
        g(lx,j) = L;
    }
}
inline void ldh(int lx, int rx, int ly, int ry) {
    for (int i = rx; i >= lx; i -= 2) {
        for (int j = ly; j < ry; ++j) g(i,j) = R;
        g(i,ry) = U;
    }
    for (int i = rx-1; i >= lx; i -= 2) {
        for (int j = ry; j > ly; --j) g(i,j) = L;
        g(i,ly) = U;
    }
}
inline void ldv(int lx, int rx, int ly, int ry) {
    for (int j = ly; j <= ry; j += 2) {
        for (int i = rx; i > lx; --i) g(i,j) = U;
        g(lx,j) = R;
    }
    for (int j = ly+1; j <= ry; j += 2) {
        for (int i = lx; i < rx; ++i) g(i,j) = D;
        g(rx, j) = R;
    }
}
inline void rdh(int lx, int rx, int ly, int ry) {
    for (int i = rx; i >= lx; i -= 2) {
        for (int j = ry; j > ly; --j) g(i,j) = L;
        g(i,ly) = U;
    }
    for (int i = rx-1; i >= lx; i -= 2) {
        for (int j = ly; j < ry; ++j) g(i,j) = R;
        g(i,ry) = U;
    }
}
inline void rdv(int lx, int rx, int ly, int ry) {
    for (int j = ry; j >= ly; j -= 2) {
        for (int i = rx; i > lx; --i) g(i,j) = U;
        g(lx,j) = L;
    }
    for (int j = ry-1; j >= ly; j -= 2) {
        for (int i = lx; i < rx; ++i) g(i,j) = D;
        g(rx,j) = L;
    }
}

bool fe;
int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
void solve() {
    if (m == 1) {
        if (a[1] == 2) {
            cout << "Cycle\n";
            if (b[1] == 1) { cout << "inc 1\n"; cout << "dec 1\n"; }
            else { cout << "dec 1\n"; cout << "inc 1\n"; }
        } else if (b[1] == 1) {
            cout << "Path\n";
            rep(i,a[1]-1) cout << "inc 1\n";
        } else if (b[1] == a[1]) {
            cout << "Path\n";
            rep(i,a[1]-1) cout << "dec 1\n";
        } else cout << "No\n";
        return;
    }
    init();
    int x = b[1], y = -1;
    rep(i,c) {
        if (w(x,i,2) == b[2] && w(x,i,3) == b[3] && w(x,i,4) == b[4] &&
            w(x,i,5) == b[5] && w(x,i,6) == b[6]) {
            y = i; break;
        }
    }
    if (fe) {
        cout << "Cycle\n";
        if (c&1) {
            g(1,1) = R;
            luh(1, r, 2, c);
            g(r, 2) = L;
            for (int i = r; i >= 2; --i) g(i,1) = U;
        } else {
            g(1,1) = D;
            luv(2, r, 1, c);
            g(2,c) = U;
            for (int i = c; i >= 2; --i) g(1,i) = L;
        }
        rep(i,r*c) {
            int tx = x + dx[g(x,y)], ty = y + dy[g(x,y)];
            go(x, y, tx, ty);
            x = tx, y = ty;
        }
    } else {
        if ((x^y)&1) { cout << "No\n"; return; }
        cout << "Path\n";
        if (x == 1) {
            ruh(1, r-1, 1, y);
            g(r-1,y) = R;
            ldv(1, r-1, y+1, c);
            g(r-1,c) = D;
            for (int i = c; i >= 2; --i) g(r,i) = L;
        } else if (x == r) {
            rdh(2, r, 1, y);
            g(2,y) = R;
            luv(2, r, y+1, c);
            g(2,c) = U;
            for (int i = c; i >= 2; --i) g(1,i) = L;
        } else if (y == 1) {
            ldv(1, x, 1, c-1);
            g(x,c-1) = D;
            ruh(x+1, r, 1, c-1);
            g(r,c-1) = R;
            for (int i = r; i >= 2; --i) g(i,c) = U;
        } else if (y == c) {
            rdv(1, x, 2, c);
            g(x,2) = D;
            luh(x+1, r, 2, c);
            g(r,2) = L;
            for (int i = r; i >= 2; --i) g(i,1) = U;
        } else if (x&1) {
            for (int i = x; i >= 2; --i) g(i,y) = U;
            g(1,y) = L;
            ruh(1, x, 1, y-1);
            g(x,1) = D;
            luv(x+1, r, 1, y);
            g(r,y) = R;
            ldv(1, r, y+1, c);
        } else {
            rdv(1, x, 1, y);
            g(x,1) = D;
            luh(x+1, r, 1, y);
            g(r,y) = R;
            ldv(1, r, y+1, c);
        }
        rep(i,r*c-1) {
            int tx = x + dx[g(x,y)], ty = y + dy[g(x,y)];
            go(x, y, tx, ty);
            x = tx, y = ty;
        }
    }
}

int main() {
    fast;
    cin >> m;
    rep(i,m) { cin >> a[i]; fe |= !(a[i]&1); }
    rep(i,m) cin >> b[i];
    solve();
    return 0;
}