//
// Created by Psy.C on 2026/10/16.
//
/***
给 n 个圆（圆心 (x,y)、半径 r），求这些圆把平面划分成多少个区域。

答案用平面图欧拉公式：

V - E + F = 1 + C
其中 V 是交点/折点数，E 是边数，F 是区域数，C 是连通分量数
eps = 1e-10，用容差判断浮点数符号，避免浮点误差
定义了带容差的三路比较（按 x，再按 y），用于后面去重交点。注意：operator<=> 返回 int（这里是自定义的、非标准的简化写法），== 复用其比较结果
用并查集记录哪些圆相交/相连，最后统计连通块数 C
读入 n 个圆，并查集初始化
计算圆心距平方 d2。
若 d2 > (r_i+r_j)²（相离）或 d2 < (r_i-r_j)²（内含），没有交点，跳过。
否则两圆相交或相切，做 fa[find(i)]=find(j) 合并连通块，并求出交点
这是标准的两圆交点公式：

t：圆心 i→j 连线的方向角（atan2）。
a：交点相对于连线方向的偏角，由余弦定理 cos(a) = (r_i² - r_j² + d²) / (2 r_i d) 得到。
圆心 i 出发、沿方向角 t±a、距离 r_i 的点即为两个交点。
!sgn(a) 表示两圆相切（夹角为 0），只有一个交点，直接 continue 不再添加第二个
对交点按带容差的比较排序、去重，得到平面上的不同交点总数 V（vt.size()）
ans = 1 - vt.size()：起始为 1 - V。
rep(i,1,n) ans += i == find(i)：统计根节点个数，即连通块数 C，加入答案。→ 此时 ans = 1 - V + C。
对每个交点 (X,Y)，检查它落在哪些圆上（距离平方等于半径平方，用 sgn==0 容差判断）。每落在一个圆上，ans++——这是因为每个交点会在所在圆上形成一条边的端点，每增加一个"圆上的交点归属"，边的贡献 +1。
最终 ans 即平面被这些圆划分的区域数 F
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define eps 1e-10
#define db double
using namespace std;

constexpr int N = 5;

struct node { db x, y; };

int sgn(db x) {
    if (x > eps) return 1;
    if (x < -eps) return -1;
    return 0;
}

int operator<=>(node a, node b) {
    return sgn(a.x - b.x) == 0 ? sgn(a.y - b.y) : sgn(a.x - b.x);
}
bool operator==(node a, node b) { return (a <=> b) == 0; }

int fa[N];
int find(int i) { return i == fa[i] ? i : fa[i] = find(fa[i]); }

template<typename T>
T sq(T x) { return x * x; }

int n, x[N], y[N], r[N], ans;
vector<node> vt;
int main() {
    fast;
    cin >> n;
    rep(i,1,n) cin >> x[i] >> y[i] >> r[i], fa[i] = i;
    rep(i,1,n) rep(j,i+1,n) {
        int dx = x[j] - x[i], dy = y[j] - y[i];
        int d2 = sq(dx) + sq(dy);
        if (d2 > sq(r[i]+r[j]) || d2 < sq(r[i]-r[j])) continue;
        fa[find(i)] = find(j);
        db t = atan2(dy, dx);//连线方向角
        db a = acos((sq(r[i])-sq(r[j])+d2)/(2.*r[i]*sqrt(d2)));//交点相对连线方向的夹角
        db X = x[i]+r[i]*cos(t+a), Y = y[i]+r[i]*sin(t+a);//交点 1
        if (vt.emplace_back(X, Y); !sgn(a)) continue;//若相切(夹角=0)，只有一个交点，跳过第二个
        X = x[i]+r[i]*cos(t-a), Y = y[i]+r[i]*sin(t-a), vt.emplace_back(X, Y);//交点 2
    }
    ranges::sort(vt), vt.resize(ranges::unique(vt).begin() - vt.begin());
    ans = 1 - vt.size();
    rep(i,1,n) ans += i == find(i);
    for (auto [X, Y] : vt) rep(i,1,n) {
        if (sgn(sq(X-x[i])+sq(Y-y[i])-sq(r[i])) == 0) ans++;
    }
    cout << ans << '\n';
    return 0;
}