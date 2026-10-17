//
// Created by Psy.C on 2026/10/17.
//
/**
N=1e5+5：数组长度上限；N<<2 即 4*N，线段树的经典 4 倍空间。
inf=1e18：作为"无穷大"用于最小值查询的初始值。
get(v) = max(v,-v)：绝对值函数（|v|）。
sum[N<<2]：线段树节点存储"区间内所有 a[i] 绝对值之和"。
mn[N<<2]：线段树节点存储"区间内某个特殊最小值"
rt：当前线段树节点编号；rt<<1 是左孩子，rt<<1|1 是右孩子。
sum[rt] = 左孩子sum + 右孩子sum：区间绝对值之和可由左右子树合并得到。
mn[rt] = min(左孩子mn, 右孩子mn)：区间最小值可由左右子树取 min 得到。
这是标准线段树的两个合并操作
叶子节点 l==r：
sum[rt] = |a[l]|：把该位置 a 值的绝对值存入 sum。
若 l-1 非 0（即左边还有元素，l>=2 才成立）：mn[rt] = max(0, a[l-1]) + max(0, -a[l])。
max(0, a[l-1])：当 a[l-1]>0 时取 a[l-1]，否则取 0 → 即 a[l-1] 的正部。
max(0, -a[l])：当 a[l]<0 时取 -a[l]，否则取 0 → 即 -a[l] 的正部 = a[l] 的负部绝对值。
两者相加：若 a[l-1] 为正且 a[l] 为负，则等于 a[l-1] + (-a[l])；否则较小。这是在计算相邻两项"符号相反"时对绝对值的影响量（细节见 main 的公式）。
叶子 l==1（没有 l-1）时不设置 mn[rt]（保持默认 0），因为第一位前面没有邻居。
否则二分递归建左右子树，push_up 合并。
mn 的语义：mn[rt] 存的是区间内所有位置 i 的 max(0,a[i-1]) + max(0,-a[i]) 的最小值。这个值在后面的查询公式里作为"减掉的最小括号量"被用到
递归定位到位置 p，把 a[p] += v。
然后在叶子重新计算 sum = |a[p]| 和（若有前驱）mn = max(0,a[p-1]) + max(0,-a[p])。
向上 push_up 刷新所有祖先节点。
它是单点加值的操作，复杂度 O(log n)
若当前节点区间 [l,r] 被查询区间 [L,R] 完全覆盖，直接返回 mn[rt]。
否则向左右递归：若左半与查询区间有交集（mid>=L），先取左半结果作初值；若右半有交集（mid<R），与右半结果取 min。
返回区间 [L,R] 内 mn 的最小值。
这是标准的区间最小值查询，O(log n)

读入 n 和 n 个数到 a[1..n]。
关键变换：a[i-1] -= a[i]，也就是差分数组：
a[i-1] 变成 a[i-1](原来的新输入) - a[i](当前读入的数)
即最终 a[i] = 原a[i] - 原a[i+1]（差分数列，表示相邻元素的变化量）。
这暗示原数组代表的是某种"累积/差分"结构，真正的原始数组是 a[] 的前缀和。后面所有操作都作用在这个差分数组上
因为差分数组的有效长度是 n-1（a[1..n-1]），在线段树的 [1, n-1] 上建树
读入 q 个操作。每个操作形如 op l r x：op 决定是"查询"还是"区间更新"（op-2 即 op≠2 为查询；op==2 为更新，见下面 if (op-2) → 为真表示 op==1 查询）
查询分支（op == 1）
情况 A：单点（l == r）‍——在位置 l 上加 x 后，总绝对值和的变化公式：
sum[1]-|a[l-1]|+|a[l-1]-x| - |a[l]| + |a[l]+x|
即：先把旧的 |a[l-1]| 和 |a[l]| 去掉，再按新的值 |a[l-1]-x|、|a[l]+x| 加回来。因为给差分数组位置 l 所在的前缀加了 x（对差分来说会同时影响 a[l-1] 和 a[l] 对绝对值总和的贡献）。这是 O(1) 的公式解。
情况 B：区间（l < r）‍——用公式：

sum[1] + max(0, 2*x - 2*query(1,n-1,1,l,r))
query(1,n-1,1,l,r) 查到区间 [l,r] 内 mn 的最小值。
对整个区间 [l,r] 统一加 x 后，总绝对值和增加的量 = max(0, 2x - 2*mn_min)。
其中 2x 是"理想最多能增加的量"（每段两端都朝外），2*mn_min 是要减掉的"受相邻符号影响/已饱和"的量（因为某处当前已经是这两项的最小结合，无法再满额增加）。
取 max(0, ...) 保证增量非负。
这依赖前面定义好的 mn（max(0,a[i-1])+max(0,-a[i]) 的最小值）正是这一段能"扣减"的最大量。
这一步不是逐段模拟，而是利用线段树区间最小值一次性算出整个区间统一加 x 对总绝对值的影响，O(log n)。
更新分支（op == 2）
op==2 是区间加值：对原数组的区间 [l,r] 每个元素加上 x。由于线段树建在差分数组上，区间加在差分上对应"左端点减 x、右端点后一位加 x"：
update(..., l-1, -x)：差分位置 l-1 减 x（区间加会让区间首端差分变化 -x）。
update(..., r, x)：差分位置 r 加 x（区间末尾之后差分变化 +x）。
随后两个 if 做边界修正：当 l+1 < n（说明差分还有元素可影响）和 r+1 < n，分别对差分位置 l、r+1 再 update 一个 0（相当于"刷新/占位"，确保线段树叶子相应位置被正确处理——因为上面的 -x/+x 可能改变了成交错位置，这里是恢复或规范化，保证 mn/sum 的语义成立）。
也就是把"原数组区间加 x"正确翻译成"差分数组上的两个单点改 + 两个占位刷新"，复杂度 O(log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr ll N = 1e5+5, inf = 1e18;

ll get(ll v) { return max(v, -v); }
ll sum[N<<2], mn[N<<2];
void push_up(int rt) {
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    mn[rt] = min(mn[rt<<1], mn[rt<<1|1]);
}

ll a[N];
void build(int l, int r, int rt) {
    if (l == r) {
        sum[rt] = get(a[l]);
        if (l-1) mn[rt] = max(0ll, a[l-1]) + max(0ll, -a[l]);
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, rt<<1); build(mid+1, r, rt<<1|1);
    push_up(rt);
}

void update(int l, int r, int rt, int p, ll v) {
    if (l == r) {
        a[l] += v;
        sum[rt] = get(a[l]);
        if (p-1) mn[rt] = max(0ll, a[l-1]) + max(0ll, -a[l]);
        return;
    }
    int mid = (l+r)>>1;
    if (mid >= p) update(l, mid, rt<<1, p, v);
    else update(mid+1, r, rt<<1|1, p, v);
    push_up(rt);
}

ll query(int l, int r, int rt, int L, int R) {
    if (l >= L && r <= R) return mn[rt];
    ll ans = inf;
    int mid = (l+r)>>1;
    if (mid >= L) ans = query(l, mid, rt<<1, L, R);
    if (mid < R) ans = min(ans, query(mid+1, r, rt<<1|1, L, R));
    return ans;
}


int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], a[i-1] -= a[i];
    build(1, n-1, 1);
    int q; cin >> q;
    while (q--) {
        int op, l, r; ll x; cin >> op >> l >> r >> x;
        if (op-2) {
            if (l == r) cout << sum[1]-get(a[l-1])+get(a[l-1]-x)-get(a[l])+get(a[l]+x) << '\n';
            else cout << sum[1]+max(0ll, 2*x-2*query(1,n-1,1,l,r)) << '\n';
        } else {
            update(1, n-1, 1, l-1, -x), update(1, n-1, 1, r, x);
            if (l + 1 < n) update(1, n-1, 1, l, 0);
            if (r + 1 < n) update(1, n-1, 1, r+1, 0);
        }
    }
    return 0;
}