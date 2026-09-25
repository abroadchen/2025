//
// Created by Psy.C on 2026/9/24.
//
/**
邻接表 g：每个元素 (L, R, 另一端节点)。
cur[x]：记录节点 x 在邻接表中已经扫描到哪条边（配合有序性做一次扫描的 Dijkstra 优化）。
add(x, y, l, r)：在 x 和 y 之间建立一条带区间 [l, r] 的双向边。
对 x 方向存 [l+(l&1), r-(r&1)]：即将 l 调整为偶数、r 调整为偶数（l&1 取最低位奇偶：若 l 是奇数则 +1 变偶数，若 r 是奇数则 -1 变偶数）。
对 y 方向存 [l+!(l&1), r-!(r&1)]：即调整为奇数（l 若是偶数 +1 变奇数）。
这样把一条区间边拆成奇偶性不同的两个半区，分别挂在两端——这是经典"奇偶分层图"技巧。
l <= r 保证区间非空才建边
读 n、m，图大小 2n。
每条输入的区间边：x 到 y+n、y 到 x+n 各建一条带区间 [l, r-1] 的边（后一半节点 n+1..2n 作为"区间端"虚拟节点）
对每个节点的邻接表按 (L, R, 目标) 字典序排序（tuple 默认比较），并把 cur[i] 指到表头，用于后续扫描式松弛
dis 初始 inf，起点 dis[1]=0。
优先队列元素：(L, R, 节点x)——即"当到达 x 时的区间/进度"。
特殊处理起点 1：若 1 的第一条边 L==0（起点距离 0 落在区间内），则松弛入队（R 取 get<1>+1），并前进 cur[1]
取出队首 (l, r, x)：
dis[真实节点] = min(dis, l)：用当前区间下界 l 更新 x 对应的真实节点距离（(x-1)%n+1 把虚拟节点映射回 1..n）。
从 cur[x] 开始扫描 x 的邻接边：
只扫到 get<0>(*i) <= r（边的左端 ≤ 当前 r，有交集）为止。
若 get<1>(*i) >= l（边的右端 ≥ 当前 l，区间相交），则生成新状态 (max(l, 左端)+1, 右端+1, 目标节点) 入队——即"在当前区间与边区间相交的部分取交接点继续走"。
由于每个 (x) 的 cur 一经扫描只前进，总扫描量是 O(边数)，配合优先队列保证高效
输出到达节点 n 的最短距离；不可达输出 -1
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5+5, inf = 0x3f3f3f3f;
typedef tuple<int, int, int> iii;

vector<vector<iii>> g;
vector<vector<iii>::iterator> cur;
void add(int x, int y, int l, int r) {
    return l <= r && (g[x].emplace_back(l+(l&1), r-(r&1), y),
        g[y].emplace_back(l+!(l&1), r-!(r&1), x), 1), void();
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int dis[N];
int main() {
    int T = 1;
    while (T--) {
        int n = read(), m = read();
        g.resize(2*n+1), cur.resize(2*n+1);
        for (int i = 1; i<= m; ++i) {
            int x = read(), y = read(), l = read(), r = read()-1;
            add(x, y+n, l, r), add(y, x+n, l, r);
        }
        for (int i = 1; i <= 2*n; ++i)
            sort(cur[i]=g[i].begin(), g[i].end());
        memset(dis, 0x3f, sizeof dis); dis[1] = 0;
        static priority_queue<iii, vector<iii>, greater<>> q;
        while (!q.empty()) q.pop();
        while (cur[1] != g[1].end() && get<0>(*cur[1]) == 0)
            q.emplace(1, get<1>(*cur[1])+1, get<2>(*cur[1])), ++cur[1];
        while (!q.empty()) {
            auto [l, r, x] = q.top(); q.pop();
            dis[(x-1)%n+1] = min(dis[(x-1)%n+1], l);
            for (auto& i = cur[x]; i != g[x].end() && get<0>(*i) <= r; ++i)
                if (get<1>(*i) >= l)
                    q.emplace(max(l, get<0>(*i))+1, get<1>(*i)+1, get<2>(*i));
        }
        write(dis[n] == inf ? -1 : dis[n]), putchar('\n');
    }
    return 0;
}