//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
N=405 点数上限；M=2.5e5 任务数；D 是随机种子；inf 是二分上界
t[i] 存第 i 个任务：起点 s、终点 t、单位成本 c、最大休息次数 r。
key 是给该任务生成的随机键，cmp 按 key 排序 → 用于随机打乱任务顺序（防止针对性的最坏输入卡住算法，比如需要二分的任务都排在前面）
check(now, v)：判断油箱容量 v 是否足以完成单个任务 now（最多休 now.r 次）。
cnt：已用"刷新/补给"次数；y：当前剩余油量，初始为满 v。
遍历 s+1 到 t 的每一段（差分后 p[i] 表示第 i-1 点到第 i 点的距离，见后）：
若单段耗油 c*p[i] 已经超过总容量 v，则必不可能完成 → 返回 0；
若单段耗油大于当前剩余 y：说明必须补给一次（y = v 重置满油，cnt++）；
减去本段耗油。
最后看总补给次数 cnt 是否 ≤ 允许的 r。
这是标准的二分容量 + 贪心补油判断
读入 n 个坐标 p[i]（假定位升序）。
读入 m 个任务，并给每个任务随机生成 key。
关键差分：for (i=n; i>=1; i--) p[i] -= p[i-1] 让 p[i] 变成"第 i-1 点到第 i 点之间的距离"（即差分数组），这样 p[s+1..t] 的累加就是 s 到 t 的路程构成。
注意 p[1] 会变成 p[1]-p[0]，而 p[0] 未初始化（数组默认 0），所以 p[1] 不变，符合"从坐标 0 起始"的情形
随机排序任务后，逐个处理：
保持 ans 为"当前已能满足所有已处理任务的最小容量"（是递增维护的，因为答案只可能随任务变多而增大）。
先试 check(t[i], ans)：若当前 ans 已能满足该任务，直接跳过，不用重新二分；
否则对任务 t[i] 单独二分找所需最小容量，把 ans 提升到那个值。
输出最终的 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
#define ui unsigned int
using namespace std;

constexpr int N = 405, M = 25e4+5, D = 998247;
constexpr ll inf = 1e18;

struct node { int s, t, c, r; ui key; } t[M];
bool cmp(node x, node y) { return x.key < y.key; }

int p[N];
bool check(node now, ll v) {
    int cnt = 0; ll y = v;
    for (int i = now.s+1; i <= now.t; i++) {
        if (1ll*now.c*p[i] > v) return 0;
        if (1ll*now.c*p[i] > y) y = v, cnt++;
        y -= 1ll*now.c*p[i];
    }
    return cnt <= now.r;
}

int n, m;
mt19937 rnd(D);
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> p[i];
    rep(i,m) cin >> t[i].s >> t[i].t >> t[i].c >> t[i].r, t[i].key = rnd();
    for (int i = n; i >= 1; i--) p[i] -= p[i-1];
    sort(t+1,t+m+1,cmp);
    ll ans = 0;
    rep(i,m) {
        if (check(t[i], ans)) continue;
        ll l = ans+1, r = inf;
        while (l <= r) {
            ll mid = (l+r)>>1;
            if (check(t[i], mid)) ans = mid, r = mid-1;
            else l = mid+1;
        }
    }
    cout << ans;
    return 0;
}