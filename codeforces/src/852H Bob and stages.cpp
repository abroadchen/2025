//
// Created by Psy.C on 2026/9/29.
//
/**
a[] 存平面上的 n 个点。
operator-：求两个点的差向量。
cross(p,q)：二维叉积 p.x*q.y - p.y*q.x，其绝对值等于两向量围成的平行四边形面积（2 倍三角形面积）‍，符号表示旋转方向（>0 逆时针）
按极角（角度）排序的比较器。
sa/sb：判断向量是否位于"下半平面/负 x 轴"（即左半），用来把角度分成两段，保证按逆时针整圈排序正确（不然 atan2 风格会出错）。
cross(lhs,rhs)>0：两向量同在半平面时，按叉积正负判断谁的角度更小（逆时针次序）。
作用：后面将所有"以某点出发到其他点"的方向向量按极角排好，配合 DP 构造凸多边形/不相交三角形

外层 for (int i = 0; i < n; ++i) 枚举凸多边形的起点/最下面一个点，对每个 i 计算以它为底的 DP
b[] 是起点 i 之外的所有点（下标 i+1..n-1），按相对 i 的极角从小到大排序
dp[j][c]：以 i 为起点、"链"走到点 j、共选了 c 个三角形/边的最大面积和。初始化为 LLONG_MIN（负无穷），起点 dp[i][0]=0。
ok[x][y]：标记点对 (x,y) 是否"可行/可以连边"（用于保证不交叉）
ok[i][j]=true：起点 i 可与所有点连。
对每个 b[j]，向后扫描，用叉积判断 b[l] 是否在当前"凸包前缘"的逆时针方向；是则可连边并更新前缘 lx。
效果：ok[x][y]=true 表示连边 (x,y) 不会使多边形凹/自交，保证形成的是一些不相交的三角形（凸的三角剖分边集）
op 是在 main 开头预处理的"所有点对的有向向量"：op.emplace_back(a[i]-a[j], j, i)，并按之前的极角比较器 ranges::sort(op) 排好。
遍历每条可行且有向边 (x→y)：adv = |cross(a[x]-a[i], a[y]-a[i])| 是三角形 ixy 面积的 2 倍（绝对值取正，保证非负）。
转移：dp[y][c+1] = max(dp[y][c+1], dp[x][c] + adv)，即"再取一个以 i 为顶点、x→y 为底边的三角形"。
遍历顺序（按极角增序）保证 dp 拓扑序正确、三角形不重叠
以 i 为起点、恰好取 k 个三角形时的最大值更新全局答案
DP 中存的是面积的 2 倍（叉积绝对值），所以最后除以 2 得到真实面积，保留 2 位小数输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 200, M = 50;

struct node {
    int x, y;
    node operator-(const node &o) const {
        return {x - o.x, y - o.y};
    }
} a[N];

ll cross(const node &p, const node &q) { return 1ll*p.x*q.y - 1ll*p.y*q.x; }
bool operator<(const node &lhs, const node &rhs) {
    bool sa = (lhs.y < 0 || (lhs.y == 0 && lhs.x < 0)),
    sb = (rhs.y < 0 || (rhs.y == 0 && rhs.x < 0));
    if (sa != sb) return sa > sb;
    return cross(lhs, rhs) > 0;
}
inline void chkmax(ll& _a, ll _b) { if (_a < _b) _a = _b; }

vector<tuple<node, int, int>> op;
int b[N];
ll dp[N][M+1];
bool ok[N][N];
int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y;
    sort(a, a+n, [](auto& x, auto& y) {
        return x.y == y.y ? x.x > y.x : x.y > y.y;
    });
    op.reserve(n*(n-1));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j) op.emplace_back(a[i]-a[j], j, i);
    ranges::sort(op);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        iota(b, b+n-1-i, i+1);
        sort(b, b+n-1-i, [&](auto& p, auto& q) {
            return a[p] - a[i] < a[q] - a[i];//按(相对i的)极角升序
        });
        for (int j = 0; j < n; ++j) {
            fill(dp[j], dp[j]+k+1, LLONG_MIN);
            fill_n(ok[j], n, false);
        }
        dp[i][0] = 0;
        for (int j = i+1; j < n; ++j) ok[i][j] = ok[j][i] = true;
        for (int j = 0; j < n-2-i; ++j) {
            ok[b[j]][b[j+1]] = ok[b[j+1]][b[j]] = true;//相邻点连边
            int lx = b[j+1];
            for (int l = j+2; l < n-1-i; ++l) {
                if (cross(a[lx]-a[b[j]], a[b[l]]-a[b[j]]) > 0) {
                    ok[b[j]][b[l]] = ok[b[l]][b[j]] = true;//保持逆时针时才连
                    lx = b[l];
                }
            }
        }
        for (auto [_, x, y] : op) {
            if (ok[x][y] && x >= i && y >= i) {
                ll adv = abs(cross(a[x]-a[i], a[y]-a[i]));
                for (int j = 0; j < k; ++j)
                    chkmax(dp[y][j+1], dp[x][j]+adv);
            }
        }
        chkmax(ans, dp[i][k]);
    }
    cout << fixed << setprecision(2) << ans/2.0 << '\n';
    return 0;
}