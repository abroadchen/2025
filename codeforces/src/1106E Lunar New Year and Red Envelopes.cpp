//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
N：线段/时间轴大小上限。
M：暂停次数上限（m ≤ 300，dp 第二维）。
inf：极大值，作"不可达"的初值。
先比 w，w 大的优先（在 priority_queue 里 a<b 返回 true 表示 a 优先级更低，所以堆顶是"最大 w"）。
w 相同时，d 大的优先（d < o.d 使堆顶选 d 更大的）——因为 d 大意味着任务持续时间长、能"占住"更久，一般更优（少换线段）
按 s（开始时间）升序排序的辅助函数
n：总时间/进度上限。
m：最多能用的"暂停/跳过"次数。
k：线段总数。
dp[i][j]：到达进度 i、且已用 j 次跳过时的最小花费/最小收益负值。这里 inf 初始，越小越好（最小花费）。
q：优先队列，维护"当前时间点可用、按优先级排序"的线段
读入并按开始时间 s 排序，为了之后能随进度推进逐步加入可用线段
DP 表初始化为 inf，起点 dp[0][0]=0（进度 0、0 次跳过，花费 0）。枚举 j 到 m+1 是为下标安全（用 j+1 时不会越界）
对每个当前进度 i：

① 加入新线段：把所有 s ≤ i 的未入队线段压入 q。因为已按 s 排序，idx 单调前进。

② 剔除失效线段：堆顶线段若 t < i（它已经结束/不可用于当前进度），q.top().t < i 弹掉。注意这里只检查堆顶，因为规则是"当前最优可能已失效，需要淘汰继续找"——但只弹堆顶其实可能残留——不过配合步骤④的生成逻辑，通常这样写足够。

③ 队列空：当前没有任何可用线段，只能"无作为"地推进：dp[i+1][j] = min(dp[i][j])（进度+1，不耗跳过，无花费），然后 continue。

④ 队列非空：q.top() 是最优线段 t。对每个跳过次数 j 做两种转移：

用跳过快进：dp[i+1][j+1] = min(dp[i][j], ...) —— 进度+1，跳过次数 +1，花费不变（跳过就是不选当前线段）。
选当前最优线段：dp[t.d+1][j] = min(dp[t.d+1][j], dp[i][j] + t.w) —— 进度跳到 d+1，跳过次数不变，花费加上 w。
因为 t 是当前最优（最大 w / 更大 d），贪心地一直用它，是正确的（这类题的最优子结构）
遍历所有跳过次数，取 dp[n+1][*]（到达进度 n+1）的最小花费作为答案输出。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e5+5, M = 305;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

struct node {
    int s, t, d, w;
    bool operator<(const node &o) const {
        if (w == o.w) return d < o.d;
        return w < o.w;
    }
} e[N];
bool cmp(node a, node b) { return a.s < b.s; }

int n, m, k;
ll dp[N][M];
priority_queue<node> q;
int main() {
    fast;
    cin >> n >> m >> k;
    rep(i,k) cin >> e[i].s >> e[i].t >> e[i].d >> e[i].w;
    sort(e+1,e+1+k,cmp);
    rep(i,n+1) for (int j = 0; j <= m+1; j++) dp[i][j] = inf;
    dp[0][0] = 0;
    int idx = 1;
    for (int i = 0; i <= n; i++) {
        while (e[idx].s <= i && idx <= k) q.push(e[idx++]);//把开始时间 ≤ i 的线段都放进优先队列
        while (!q.empty() && q.top().t < i) q.pop();//弹出已失效（t < i）的线段
        if (q.empty()) {//若当前无可选线段
            for (int j = 0; j <= m; j++) dp[i+1][j] = min(dp[i+1][j],dp[i][j]);
            continue;
        }
        auto t = q.top();//取最优（堆顶）线段 t
        for (int j = 0; j <= m; j++) {
            dp[i+1][j+1] = min(dp[i][j],dp[i+1][j+1]);//用一次跳过：不选当前，进度+1，消耗一次 m
            dp[t.d+1][j] = min(dp[t.d+1][j],dp[i][j]+t.w);//使用该线段：进度直接跳到 d+1，加上其价格 w
        }
    }
    ll mn = inf;
    for (int i = 0; i <= m; i++) mn = min(mn, dp[n+1][i]);
    cout << mn << '\n';
    return 0;
}