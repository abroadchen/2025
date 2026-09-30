//
// Created by Psy.C on 2026/9/30.
//
/**
每个查询被拆成 9 个 (x,y) 前缀点（type 1..9），记录 id（属于哪个查询）和 type。
res[i][t]：第 i 个查询、第 t 个前缀矩形内的点数
标准一维 BIT，用于动态维护"y ≤ p 的点数"
每个查询矩形分解成 9 个"左下角为原点"的前缀矩形 (x≤X, y≤Y)：

x 坐标取 {u, d-1, n}（即考虑上边界 u 内 / 下边界 d 之下 / 全范围 n）
y 坐标取 {r, l-1, n}（右边界 r 内 / 左边界 l 之下 / 全范围 n）
9 个点覆盖所有"边界取舍"组合，方便后用容斥
把排列本身的关键点 (i, b[i]) 也放进事件流，id=0 表示这是"更新点"而非查询
离线按 x 升序扫描。每次遇到排列点 (x, b[x]) 就把 y=b[x] 加入 BIT；遇到查询前缀点 (X,Y) 时 ask(Y) 即得到 x≤X 且 y≤Y 的点数。

因为排序保证了处理 (X,Y) 前缀时，所有 x≤X 的排列点都已插入，ask(Y) 正好数出"该前缀矩形内的点数"。
通过容斥从 9 个前缀点还原出矩形内部 9 个子区域的点数 s1..s9（类似把矩形 [l,r]×[d,u] 切成 3×3 的格，s5 是中间内核区域，其余是四周）。例如 s5（最核心的矩形 [l,r内]×[d,u内] 的点数）由 res[5]-res[2]-res[6]+res[3] 容斥得到。
根据各子区域的相对位置关系，把"满足某种单调/配对条件的点对"数量累加成 ans（比如矩形内"x 和 y 都递增的单调点对/可组成多少个子矩形"这类几何计数）
逐查询输出答案


s1 s4 s7
s2 s5 s8
s3 s6 s9
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int n, t[N];
inline void add(int p, int v) { for (; p <= n; p += p&-p) t[p] += v; }
inline int ask(int p) {
    int res = 0;
    for (; p; p -= p&-p) res += t[p];
    return res;
}

struct query { int x, y, id, type; } Q[10*N];
int q, b[N], res[N][10];
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; b[x] = i;
    }
    int cnt = 0;
    for (int i = 1, l, d, r, u; i <= q; ++i) {
        cin >> l >> d >> r >> u;
        Q[++cnt] = {.x = n, .y = l-1, .id = i, .type = 1};
        Q[++cnt] = {.x = u, .y = l-1, .id = i, .type = 2};
        Q[++cnt] = {.x = d-1, .y = l-1, .id = i, .type = 3};
        Q[++cnt] = {.x = n, .y = r, .id = i, .type = 4};
        Q[++cnt] = {.x = u, .y = r, .id = i, .type = 5};
        Q[++cnt] = {.x = d-1, .y = r, .id = i, .type = 6};
        Q[++cnt] = {.x = n, .y = n, .id = i, .type = 7};
        Q[++cnt] = {.x = u, .y = n, .id = i, .type = 8};
        Q[++cnt] = {.x = d-1, .y = n, .id = i, .type = 9};
    }
    for (int i = 1; i <= n; ++i) Q[++cnt] = {.x = i, .y = b[i], .id = 0, .type = 0};
    sort(Q+1, Q+1+cnt, [](query x, query y) {
        return x.x ^ y.x ? x.x < y.x : x.id < y.id;
    });
    for (int i = 1; i <= cnt; ++i) {
        if (!Q[i].id) add(Q[i].y, 1);
        else res[Q[i].id][Q[i].type] = ask(Q[i].y);
    }
    for (int i = 1; i <= q; ++i) {
        int s1 = res[i][1] - res[i][2], s2 = res[i][2] - res[i][3], s3 = res[i][3],
        s4 = res[i][4] - res[i][1] - res[i][5] + res[i][2],
        s5 = res[i][5] - res[i][2] - res[i][6] + res[i][3], s6 = res[i][6] - res[i][3],
        s7 = res[i][7] - res[i][4] - res[i][8] + res[i][5],
        s8 = res[i][8] - res[i][5] - res[i][9] + res[i][6], s9 = res[i][9] - res[i][6];
        ll ans = 0;
        ans += 1ll*s1*(s5+s6+s8+s9);
        ans += 1ll*s2*(s5+s6+s8+s9+s4+s7);
        ans += 1ll*s3*(s4+s5+s7+s8);
        ans += 1ll*s4*(s5+s6+s8+s9);
        ans += 1ll*s5*(s6+s7+s8+s9);
        ans += 1ll*s6*(s7+s8);
        ans += 1ll*s5*(s5-1)/2;
        cout << ans << '\n';
    }
    return 0;
}