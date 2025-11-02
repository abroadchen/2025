//
// Created by Psy.C on 2025/11/1.
//
/*
*ans(9): 最终答案，初始值为9
N: 当前点的数量
a[1<<4]: 存储用特定三角形组合能构造的最少点数
dp[1<<4]: 动态规划数组
point: 二维点结构体
tri[10]: 存储4个三角形的三边长度（已排序）
p[20]: 存储当前构造的点
 *
 *
*通过DFS尝试将所有三角形放置到平面上：

mask: 二进制位表示哪些三角形已经被放置
检查现有点中是否已经存在满足三角形边长要求的三点组合
如果不存在，则尝试通过两圆交点构造新的点
 *
*i&j == j: 检查j是否是i的子集（在二进制表示下）
i^j: 计算i和j的对称差集，即属于i但不属于j的元素
 *
*1<<a：创建只有第a位为1的数
1<<b：创建只有第b位为1的数
1<<c：创建只有第c位为1的数
用|将这三个数合并，结果是第a、b、c位都为1的数
 *
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#define rep(i,n) for(i=0;i<(n);++i)
#define eps 1.0e-9
#define inf 1<<29
using namespace std;

int i, j, k, l, ans(9), N,
a[1<<4], dp[1<<4];
struct point { double x, y; };
vector<double> tri[10];
point p[20];
//计算两点间欧几里得距离
double dist(point a, point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
//读取第id个三角形的三个顶点坐标，计算三边长度并排序
void read(int id) {
    point p, q, r;
    cin >> p.x >> p.y >> q.x >> q.y >> r.x >> r.y;
    tri[id].push_back(dist(p, q));
    tri[id].push_back(dist(p, r));
    tri[id].push_back(dist(q, r));
    sort(tri[id].begin(), tri[id].end());
}
//检查四条边能否构成四边形（四边形不等式）
bool quad(double a, double b, double c, double d) {
    double x[] = {a, b, c, d};
    sort(x, x + 4);
    return (x[0] + x[1] + x[2] + eps > x[3]);
}
//计算两个圆的交点（用于三角形定位）
vector<point> cr(point o1, double r1, point o2, double r2) {
    double d = dist(o1, o2),
    t = (d * d + r1 * r1 - r2 * r2) / 2.0 / d / d,
    fx = o1.x + (o2.x - o1.x) * t, fy = o1.y + (o2.y - o1.y) * t,
    h = sqrt(r1 * r1 - t * d * t * d),
    dx = (o2.y - o1.y) / d * h, dy = (o1.x - o2.x) / d * h;
    vector<point> ans;
    point ans1 = {fx + dx, fy + dy}; ans.push_back(ans1);
    point ans2 = {fx - dx, fy - dy}; ans.push_back(ans2);
    return ans;
}
//浮点数相等比较函数
bool equals(double a, double b) {
    return (a - b < eps && a - b > -eps);
}

void dfs(int mask) {
    int i, x, y, z;
    a[mask] = min(a[mask], N);
    rep(i,4) if (!(mask & (1 << i))) {
        int mask2 = mask | (1 << i);
        bool found = false;
        rep(x,N) rep(y,N) rep(z,N) {
            if (equals(dist(p[x], p[y]), tri[i][0]) &&
                equals(dist(p[x], p[z]), tri[i][1]) &&
                equals(dist(p[y], p[z]), tri[i][2])) {
                dfs(mask2);
                found = true;
            }
        }
        if (!found) rep(x,N) rep(y,N) {
            if (equals(dist(p[x], p[y]), tri[i][0])) {
                N++;
                p[N-1] = cr(p[x], tri[i][1], p[y], tri[i][2])[0];
                dfs(mask2);
                p[N-1] = cr(p[x], tri[i][1], p[y], tri[i][2])[1];
                dfs(mask2);
                N--;
            }
            if (equals(dist(p[x], p[y]), tri[i][1])) {
                N++;
                p[N-1] = cr(p[x], tri[i][0], p[y], tri[i][2])[0];
                dfs(mask2);
                p[N-1] = cr(p[x], tri[i][0], p[y], tri[i][2])[1];
                dfs(mask2);
                N--;
            }
            if (equals(dist(p[x], p[y]), tri[i][2])) {
                N++;
                p[N-1] = cr(p[x], tri[i][0], p[y], tri[i][1])[0];
                dfs(mask2);
                p[N-1] = cr(p[x], tri[i][0], p[y], tri[i][1])[1];
                dfs(mask2);
                N--;
            }
        }
    }
}
//检查三条边是否能构成三角形（三角形不等式）
bool tieq(double a, double b, double c) {
    double x[] = {a, b, c};
    sort(x, x + 3);
    return (x[0] + x[1] + eps > x[2]);
}
//计算两个圆的所有交点
vector<point> ac(point o1, double r1, point o2, double r2) {
    vector<point> ans = cr(o1, r1, o2, r2),
    ans2 = cr(o1, r2, o2, r1);
    ans.push_back(ans2[0]); ans.push_back(ans2[1]);
    return ans;
}
//尝试不同的起始配置来构造点集
void init() {
    int a, b, c, i, j, k, x, y, z, mask;
    rep(i,4) {
        N = 3;
        p[0].x = p[0].y = p[1].y = 0.0;
        p[1].x = tri[i][0];
        p[2] = cr(p[0], tri[i][1], p[1], tri[i][2])[0];
        dfs(1<<i);
    }
    rep(a,4) rep(b,a) rep(c,b) rep(i,3) rep(j,3) rep(k,3) {
        if (tieq(tri[a][i], tri[b][j], tri[c][k])) {
            N = 6;
            p[0].x = p[0].y = p[1].y  = 0.0;
            p[1].x = tri[a][i];
            p[2] = cr(p[0], tri[b][j], p[1], tri[c][k])[0];
            vector<point> t3 = ac(p[0], tri[a][(i+1)%3], p[1], tri[a][(i+2)%3]),
            f4 = ac(p[0], tri[b][(j+1)%3], p[2], tri[b][(j+2)%3]),
            f5 = ac(p[1], tri[c][(k+1)%3], p[2], tri[c][(k+2)%3]);
            rep(x,4) rep(y,4) rep(z,4) {
                p[3] = t3[x]; p[4] = f4[y]; p[5] = f5[z];
                dfs((1<<a)|(1<<b)|(1<<c));
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    rep(i,4) read(i);
    rep(i,3) rep(j,3) rep(k,3) rep(l,3) {// 检查是否能直接构成四边形
        if (quad(tri[0][i], tri[1][j],
            tri[2][k], tri[3][l])) ans = 8;
    }
    rep(i,1<<4) a[i] = inf;
    a[0] = 0;
    init();
    rep(i,1<<4) {
        dp[i] = a[i];
        for (j = 1; j < i; ++j) if ((i&j) == j) dp[i] = min(dp[i], dp[j] + a[i^j] - 1);
    }
    ans = min(ans, dp[15]);
    cout << ans << endl;
    return 0;
}