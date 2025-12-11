//
// Created by Psy.C on 2025/12/11.
//
/*
*c[N][N]: 网格字符数组('.'表示可通过，'#'表示障碍)
ans[M]: 答案数组
n, m: 网格行数和列数
q: 查询数量
cnt[N]: 前缀计数数组
 *
*y1: 起点列坐标
x2: 终点行坐标
y2: 终点列坐标
id: 查询编号
*位集数组用于动态规划：
f[i][j]: 从位置(i,j)向右下方能到达的列集合
g[i][j]: 从位置(i,j)向左上方能到达的列集合
 *
 *时间复杂度约为O(n×m×log n + q×log n)，空间复杂度O(n×m + q)
 */
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 505, M = 6e5+5;
char c[N][N]; int ans[M], n, m, q, cnt[N];
struct node {
    int y1, x2, y2, id;
    node() = default;
    node(const int id, const int y1, const int x2, const int y2) :
        y1(y1), x2(x2), y2(y2), id(id) {}
    bool operator==(const node& o) const {
        return id == o.id && y1 == o.y1 && x2 == o.x2 && y2 == o.y2;
    }
};
vector<node> v[N];//每行的查询向量数组
bitset<N> f[N][N], g[N][N];

int main() {
    fast;
    memset(ans, -1, sizeof(ans));
    cin >> n >> m;
    rep(i,n) rep(j,m) cin >> c[i][j];
    cin >> q;
    rep(i,q) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        v[x1].emplace_back(i, y1, x2, y2);//将查询添加到起始行x1的向量中
        if (x2 >= x1 && y2 >= y1) continue;//终点在起点左上方
        ans[i] = 0;
    }
    rep(i,n) sort(v[i].begin(), v[i].end(), [&](const auto& x, const auto& y) {
        return x.x2 < y.x2;//按终点行坐标x2排序
    });
    auto dfs = [&](auto self, int l, int r) {
        if (l == r) {
            rep(i,m) cnt[i] = cnt[i-1] + (c[l][i] == '#');//该行障碍物的前缀和
            //终点行坐标≥l的查询起始位置
            auto i1 = upper_bound(v[l].begin(), v[l].end(), node(0, 0, l-1, 0), [&](const auto& x, const auto& y) {
                return x.x2 < y.x2;
            });
            for (; i1 != v[l].end(); ++i1) {//处理该行内的查询
                if ((*i1).x2 != l) return;//终点行不是当前行
                if ((*i1).y2 < (*i1).y1) continue;//终点在起点左边
                const int id = (*i1).id;
                ans[id] = !(cnt[(*i1).y2] - cnt[(*i1).y1 - 1]);//起点到终点之间是否有障碍物
            }
            return;
        }
        int mid = (l + r) >> 1;
        self(self, l, mid); self(self, mid + 1, r);
        for (int j = m + 1; j >= 0; --j) for (int i = mid + 1; i >= l - 1; --i) {
            f[i][j].reset();//重置f数组（右下半部分）
        }
        for (int j = m; j >= 1; --j) for (int i = mid; i >= l; --i) {
            f[i][j].reset();
            if (i == mid) {
                if (c[i][j] == '.') {
                    f[i][j][j] = 1;
                    f[i][j] |= f[i][j+1];//到达当前位置且向右可达
                }
                continue;
            }
            if (c[i][j] == '.') f[i][j] = f[i][j+1] | f[i+1][j];//向右或向下到达
        }
        for (int i = mid; i <= r + 1; ++i) for (int j = 0; j <= m + 1; ++j) g[i][j].reset();//重置g数组（左上半部分）
        rep(j,m) for (int i = mid + 1; i <= r; ++i) {
            if (i == mid + 1) {
                if (c[i][j] == '.') {//检查与中间行的连接
                    if (c[mid][j] == '.') g[i][j][j] = 1;
                    g[i][j] |= g[i][j-1];
                }
                continue;
            }
            if (c[i][j] == '.') g[i][j] = g[i-1][j] | g[i][j-1];//从上方或左方到达
        }
        //对于左半部分的每行，找到终点行>mid的查询
        for (int i = l; i <= mid; ++i) {
            auto it = upper_bound(v[i].begin(), v[i].end(), node(0, 0, mid, 0), [&](const auto& x, const auto& y) {
                return x.x2 < y.x2;
            });
            for (; it != v[i].end(); ++it) {//处理跨越中线的查询
                const node p = *it;
                if (p.x2 <= mid || p.x2 > r) break;//不在[mid+1,r]范围内
                if (~ans[p.id]) continue;//答案已确定
                ans[p.id] = static_cast<int>((f[i][p.y1] & g[p.x2][p.y2]).count());//通过位运算检查是否存在路径：f(起点)与g(终点)的交集非空
            }
        }
    };
    dfs(dfs, 1, n);
    rep(i,q) cout << (ans[i] ? "Yes\n" : "No\n");
    return 0;
}