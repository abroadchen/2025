//
// Created by Psy.C on 2026/9/25.
//
/**
N=3e5+5：区间数上限约 3e5。
M=6e5+5：坐标点数量上限（每区间 2 个端点 → 2n ≈ 6e5）。
K=12e5+5：线段树数组大小（4 倍 M 量级安全开）。
inf=2e9：用作哨兵（右端边界外的坐标）。
mx[]：线段树节点，存"该区间内某个量的最大值"
这是线段树的单点更新（名字叫 dfs，作用是把第 k 个叶子加上 x）。
递归到叶子 mx[u] += x；回溯时向上取左右儿子最大值 mx[u] = max(...)。
语义：叶子 id 存"区间 id 相关的某个量"，更新后父节点维护区间最大值
标准区间查询最大值：[L,R] 完全覆盖则返回 mx[u]，否则下探左右区间取 max。
注意叶子下标范围是 [1, n]（区间编号 1..n
这是封装好的查询：求"[1, r] 中 排除掉叶子 x 后"的最大值。
分成两段：[1, min(x-1, r)] 和 [x+1, r]，跳过 x 本身。
用途：查询时排除区间 x 自身，看其他区间的量

a[]：每个输入区间 {l, r, c}（左端、右端、颜色）。
c：颜色上限（题目限制"选中的区间颜色和 ≤ c"）。
b[]：离散化坐标数组。
m：离散化后坐标个数。
cc[]：按颜色排序后每个区间的颜色（后面 `` 查询用）。
ans[]：答案 DP 数组（前缀规划）。
no[]：每个区间"单独（唯一）覆盖的长度"。
mxn[]：与某区间配对时能达到的最大共同覆盖长度。
g[]：扫描线事件表，g[pos] 存该项坐标处的插入/删除事件。
st：set，维护当前扫描位置被哪些区间覆盖（按区间 id）。
mp：unordered_map，键 (d1*n+d2) 编码"两个区间对的组合"，值 = 两区间共同覆盖的累计长度

读入 n、颜色上限 c；读每个区间，并把左右端坐标放进 b[]（去重前的离散化池）
在 b[] 加一个 0（作为最左边界哨兵），排序。
把区间 a[] 按颜色 c 升序排序——为了后面二分"颜色和 ≤ c" 前缀可用（cc[] 单调）。
坐标去重得到离散化后坐标数 m
记录每个区间排序后的颜色到 cc[i]（为后续 `` 颜色前缀二分做准备，因为 cc 单调不减）。
把左右端离散化成下标。
扫描线建事件：g[l] 加 (1, id) 表示在该坐标插入区间 id；g[r] 加 (0, id) 表示删除。
b[m+1]=inf：加一个最右哨兵坐标，供"右端点之后的一段"长度计算用
s 累积"完全没被任何区间覆盖"的空段总长（长度单位是离散坐标差 b[i+1]-b[i]）。
对坐标 i，先处理所有插入（t.first==1）和删除（t.first==0）事件，维护当前覆盖集合 st（插入区间 id；删除区间 id）。
ans[i] = ans[i-1]：先继承前缀答案（DP)
分支 1：当前段没有任何区间覆盖
若 st 为空，则覆盖数为 0，这一段 [b[i], b[i+1]) 的坐标差全归入"空段"：
s 累加空段长度；
ans[i] = ans[i-1] + (b[i+1]-b[i])：把这段也加进当前答案（表示"不选任何区间时也能覆盖的空白"被计入）。
分支 2：当前段恰好被 1 个区间覆盖
当前段恰好被区间 id 唯一覆盖：
若该区间颜色不超过上限 c：
no[id] += len：把这段长度累加给 id 的"唯一覆盖"。
dfs(1,1,n,id,len)：把 id 的线段树叶子增加 len（维护某前缀 max）。
x = 在按颜色排好序的 cc 里二分找"颜色 ≤ c − a[id].c"的区间个数前缀位置——即能和 id 配对且颜色和 ≤ c 的最大前缀区间数。
更新 ans[i] 取三者 max：
前缀答案 ans[i-1]；
mxn[id] + no[id] + s：id 的配对最长共同覆盖 + 唯一覆盖 + 空段；
query(id, x) + no[id] + s：线段树里排除 id 后颜色前缀 ≤ x 的最大值 + 唯一覆盖 + 空段。
分支 3：当前段恰好被 2 个区间覆盖
当前段恰好被两个区间 d1、d2 覆盖：
若两者颜色和 > 上限 c，则这对不能选，跳过。
保证 a[d1].r <= a[d2].r（把右端点小的放 d1），便于配对键稳定。
mp[d1*n+d2] 维护"这一对区间共同覆盖的累计长度"：第一次出现初值 = no[d1]+len，之后持续累加 len。
mxn[d2] = max(mxn[d2], 该共同长度)：记录 d2 作为后区间时，与某个更小右端区间配对能达到的最大共同覆盖长度。
ans[i] = max(ans[i-1], 共同长度 + no[d2] + s)：用"这对的共同覆盖 + 后区间的唯一覆盖 + 空段"尝试更新答案。
扫描无量，把 ans 中变化点压缩：idx 记录变化点数量，ans[idx] 存该点的答案值，cc[idx] 存对应的坐标下标。
目的：ans 是阶梯形/单调递增的值，压缩后可按值二分回答询问（ans 单调，键为值、值为坐标）
读询问次数 n；对每个询问值 x：
d = upper_bound(...)：在压缩后的 ans[1..idx] 中二分最后一个 ≤ x 的下标。
若 ans[d] == x：直接输出该值对应的"右端点坐标" b[cc[d]+1]（因为达到刚好 x，右界取该段末）。
否则（x 落在两台阶之间）：输出 b[cc[d+1]+1] - (ans[d+1]-x)——即取下一个台阶右端点坐标，往左回退 (ans[d+1]−x) 长度，得到恰好凑够长度 x 的坐标位置。
这就是"在长度(覆盖量)与坐标间做反演"：询问"能覆盖长度 ≥ 目标值的最小坐标"之类的。
 */
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
constexpr int N = 3e5+5, M = 6e5+5, K = 12e5+5, inf = 2e9;

int mx[K];
inline void dfs(int u, int l, int r, int k, int x) {
    if (l == r) { mx[u] += x; return; }
    int mid = (l+r)>>1;
    if (k <= mid) dfs(u<<1, l, mid, k, x);
    else dfs(u<<1|1, mid+1, r, k, x);
    mx[u] = max(mx[u<<1], mx[u<<1|1]);
}

inline int query(int u, int l, int r, int L, int R) {
    if (L > R) return 0;
    if (L <= l && r <= R) return mx[u];
    int mid = (l+r)>>1, mxx = 0;
    if (L <= mid) mxx = max(mxx, query(u<<1, l, mid, L, R));
    if (R > mid) mxx = max(mxx, query(u<<1|1, mid+1, r, L, R));
    return mxx;
}

int n;
inline int query(int x, int r) {
    int mxx = 0;
    if (r < 1) return 0;
    if (x > 1) mxx = query(1, 1, n, 1, min(x-1, r));
    if (x < r) mxx = max(mxx, query(1, 1, n, x+1, r));
    return mxx;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

struct node { int l, r, c; } a[N];
int c, b[M], m, cc[N], ans[M], no[N], mxn[N];
vector<ii> g[M];
set<int> st;
unordered_map<long long, int> mp;
int main() {
    read(n); read(c);
    for (int i = 1; i <= n; ++i) {
        read(a[i].l), read(a[i].r), read(a[i].c);
        b[++m] = a[i].l, b[++m] = a[i].r;
    }
    b[++m] = 0;
    sort(b+1, b+m+1);
    sort(a+1, a+1+n, [](node p, node q) {
        return p.c < q.c;
    });
    m = unique(b+1, b+m+1) - b - 1;
    for (int i = 1; i <= n; ++i) {
        cc[i] = a[i].c;
        a[i].l = lower_bound(b+1, b+m+1, a[i].l) - b;
        a[i].r = lower_bound(b+1, b+m+1, a[i].r) - b;
        g[a[i].l].emplace_back(1, i);
        g[a[i].r].emplace_back(0, i);
    }
    b[m+1] = inf;
    int s = 0;
    for (int i = 1; i <= m; ++i) {
        for (auto [fst, snd] : g[i]) {
            if (fst) st.insert(snd);
            else st.erase(snd);
        }
        ans[i] = ans[i-1];
        if (st.empty()) {
            ans[i] = ans[i-1] + (b[i+1] - b[i]);
            s += b[i+1] - b[i];
        }
        if (st.size() == 1) {
            int id = *(st.begin());
            if (a[id].c <= c) {
                no[id] += b[i+1] - b[i];
                dfs(1, 1, n, id, b[i+1] - b[i]);
                int x = upper_bound(cc+1, cc+1+n, c-a[id].c) - cc - 1;
                ans[i] = max({ans[i-1], mxn[id]+no[id]+s, query(id, x)+no[id]+s});
            }
        }
        if (st.size() == 2) {
            auto it = st.begin();
            int d1, d2; d1 = *it; ++it; d2 = *it;
            if (a[d1].c + a[d2].c > c) continue;
            if (a[d1].r > a[d2].r) swap(d1, d2);
            if (!mp.contains(1ll*d1*n+d2))
                mp[1ll*d1*n+d2] = no[d1] + b[i+1] - b[i];
            else mp[1ll*d1*n+d2] += b[i+1] - b[i];
            mxn[d2] = max(mxn[d2], mp[1ll*d1*n+d2]);
            ans[i] = max(ans[i-1], mp[1ll*d1*n+d2]+no[d2]+s);
        }
    }
    int idx = 0;
    for (int i = 1; i <= m; ++i)
        if (ans[i] != ans[i-1])
            idx++, ans[idx] = ans[i], cc[idx] = i;
    read(n);
    while (n--) {
        int x, d; read(x);
        d = upper_bound(ans+1, ans+1+idx, x) - ans - 1;
        if (ans[d] == x) printf("%d\n", b[cc[d]+1]);
        else printf("%d\n", b[cc[d+1]+1]-(ans[d+1]-x));
    }
    return 0;
}