//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
tim 存释放时间；cmp 用于按释放时间排序任务 id
p 结构体存 p（某值）和 id，按 p 排序（用于按某种时刻排序任务）
st/len/nd：开始时间、时长、结束时间。
id：任务编号（按 tim 排序后的排列）。
f[state]：完成该 state 子集所需的最小完成时刻（一台机器连续做完这些任务的结束时间）。
g[state]：该子集能否在单台机器上无冲突地按序执行（=1 可行）。
pre：记录 DP 转移前驱（上一时刻 + 新任务编号），用于回溯方案。
gt：输出每个任务所在的机器 (1/2) 和开始时间
计算每个任务结束时间 nd[i]。
id 初始为 0..n-1，按 tim（释放时间）排序 → id[o] 给出释放时间第 o 小的任务。
p 按 st（开始时间）排序
f[0]=1：空集完成时刻为 1（从时刻 1 开始）。
g[0]=1：空集可行
now 是 s 中最低位（lowest set bit）对应的任务索引。
g[s] 先继承去掉 now 后的 g[s^(s&-s)]。
然后检查 s 中其他任务 i 是否与 now 时间区间相交：若 nd[now] >= st[i] 且 st[now] <= nd[i]（即两区间重叠），则不能用一台机器顺序执行，故 g[s]=0。
结果：g[s]=1 表示 s 中所有任务可以按某种顺序在单台机器上一个接一个完成而不冲突。
注意：这个判定较宽松（仅检查与 now 相交），因为 g 只用于判断"能否把该子集作为一个整体放到一条机器时间线上"，实际冲突会由 DP 转移中的时间推进处理

外层枚举当前已处理子集 s
对每个还未加入的任务 c，尝试"追加"到当前时间线末端
lp：指向按 st 排序的任务中，第一个"在 s 内且 start ≥ f[s]"的任务（即可以被空闲机器接上的任务指针）。
ptr / mx：统计在 f[s] 之前 start 的任务的最大结束时间 mx，用于让新任务必须晚于它们。
t 初始 = f[s]，表示当前机器可用的最早时刻。
内层对该子集逐个尝试放任务 c
这是一个"推进指针"过程：不断把开始时刻 t 往后推到能容纳任务 c 为止：
若已安排在 t 之前的任务里有结束更晚的（mx>=t），则 t = max(t, mx+1)。
若某在队任务 p[lp] 的开始 ≤ t+tim[c]，则要等它结束 t = max(t, nd[...]+1)。
移动 lp、ptr 指针同步更新
若任务 c 能安插入（其开始 st[c] 大于推进后的 t+tim[c]），则把 c 加入子集后的完成时刻更新为 t+tim[c]，并记录前驱 (t, c)（该任务开始于 t 之后、完成时释放）
若 m==1：所有任务必须在一台机器上，答案就是 f[up]（全部任务在一台的结束时刻）。
若 m==2：把任务集 up 分成两个互补子集 s 和 up-s 分给两台机器，两台并行工作，总时间 = 两者完成时刻的最大值。枚举所有 s 取最小
若能完成，输出 YES。
通过 pre 前驱数组回溯：从集合 S（机器 1 的任务）逐个还原，记录每任务机器号 1 和开始时刻；T（机器 2）同理记录 2。
逐行输出每任务的 机器号 开始时间（gt[i] = {机器, 开始时刻}）。
若 ans 仍为 inf 表示无法在有限时间内完成所有任务，输出 NO

!((s>>c)&1) 等价于"任务 c 尚未被处理（不在当前子集 s 中）"，是判断是否可以尝试加入 c 的门槛
s | (1<<c)：按位或，把 c 加入当前子集，得到新的状态
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 22, inf = 0x3f3f3f3f;

int tim[N];
bool cmp(int x, int y) { return tim[x] < tim[y]; }
struct node {
    int p, id;
    bool friend operator<(const node &a, const node &b) {
        return a.p < b.p;
    }
} p[N];

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, m, st[N], len[N], nd[N], id[N], f[1<<N], g[1<<N];
ii pre[1<<N], gt[N];
int main() {
    fast;
    read(n), read(m);
    for (int i = 0; i < n; ++i) {
        read(st[i]), read(len[i]), read(tim[i]);
        nd[i] = st[i] + len[i] - 1; id[i] = i; p[i].p = st[i]; p[i].id = i;
    }
    sort(id, id+n, cmp); sort(p, p+n);
    memset(f, 0x3f, sizeof f); f[0] = 1; g[0] = 1;
    for (int s = 1; s < 1<<n; ++s) {
        int now = log2(s&-s); g[s] = g[s^(s&-s)];
        for (int i = 0; i < n; ++i) {
            if (i == now) continue;
            if ((s>>i)&1) {
                if (!(nd[now] < st[i] || st[now] > nd[i])) g[s] = 0;
            }
        }
    }
    for (int s = 0; s < (1<<n)-1; ++s) {
        if (f[s] != inf) {
            int lp = 0, ptr = 0, mx = 0;
            while (lp < n && ((!((s>>p[lp].id)&1)) || p[lp].p < f[s])) ++lp;
            while (ptr < n && p[ptr].p <= f[s]) {
                mx = max(mx, nd[p[ptr].id]);
                ++ptr;
            }
            int t = f[s];
            for (int o = 0; o < n; ++o) {
                int c = id[o];
                if (!((s>>c)&1)) {
                    if (g[s|(1<<c)]) {
                        while ((lp < n && p[lp].p <= t + tim[c]) || mx >= t) {
                            if (mx >= t) t = max(t, mx+1);
                            if (lp < n && p[lp].p <= t + tim[c]) t = max(t, nd[p[lp].id]+1);
                            while (lp < n && ((!((s>>p[lp].id)&1)) || p[lp].p < t)) ++lp;
                            while (ptr < n && p[ptr].p <= t) {
                                mx = max(mx, nd[p[ptr].id]);
                                ++ptr;
                            }
                        }
                        if (st[c] > t + tim[c]) {
                            if (f[s|(1<<c)] > t + tim[c]) {
                                f[s|(1<<c)] = t + tim[c];
                                pre[s|(1<<c)] = {t, c};
                            }
                        }
                    }
                }
            }
        }
    }
    int S = 0, ans = inf, up = (1<<n)-1;
    if (m == 1) ans = f[up], S = up;
    else {
        for (int s = 0; s < 1<<n; ++s) {
            if (ans > max(f[s], f[up-s])) {
                ans = max(f[s], f[up-s]);
                S = s;
            }
        }
    }
    if (ans < inf) {
        cout << "YES\n";
        int T = up - S;
        while (S) {
            gt[pre[S].second] = {1, pre[S].first};
            S -= 1<<pre[S].second;
        }
        while (T) {
            gt[pre[T].second] = {2, pre[T].first};
            T -= 1<<pre[T].second;
        }
        for (int i = 0; i < n; ++i) cout << gt[i].first << ' ' << gt[i].second << '\n';
    } else cout << "NO\n";
    return 0;
}