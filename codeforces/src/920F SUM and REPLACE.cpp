//
// Created by Psy.C on 2026/10/14.
//
/**
用倍数法（调和级数 O(N log N)）‍预处理 1-1e6 的每个数的正因子个数 d[j]。
对每个 i，把所有 i 的倍数 j 的计数加 1，即 j 的因子个数自增
tr[rt]：节点对应区间的和。
mx[rt]：节点对应区间的最大值
上拉：和 = 左右和之和；最大值 = 左右最大值的较大者
建树：叶子节点把和与最大值都设为 a[l]，内部节点由 push_up 汇总
剪枝条件 if (mx[rt] <= 2) return;：若整个区间最大值都不超过 2，说明区间里所有数都已经是 1 或 2，而 d(1)=1, d(2)=2，这些数永远不会再变化，所以整个区间无需再更新（直接回溯）。这是本题能把复杂度降到线性级别（每个叶子最多被改几次）的根本优化。
当到达叶子且 mx[rt] > 2 时，把 a[l] 替换为 d[a[l]]（即 d[tr[rt]]）。
注：这里调用参数传 x,y 是更新区间，实际递归时通过判断 x<=mid / y>mid 来下钻，但注意它没有像常规那样先判完全包含再剪枝，而是每层先检查 mx，再决定是否下钻到涉及区间——因为 mx 剪枝已经排除"整段无需改"的情况；对叶子直接改。这种写法在"每次改动一定发生（因为 mx>2 意味着区间里至少有一个 >2 的数会被改）"的前提下能保证正确性，不过它对部分与更新区间无关的子树也会先判断 mx 再回溯，逻辑上仍成立
标准的区间求和查询，完全包含就直接返回节点和，否则向两边递归累加
先预处理因子数表 d，读入数组建树，然后逐个处理 m 个操作：
op==1：区间更新（替换为因子个数）；
op==2：区间求和并输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

int d[N];
void init() {
    memset(d, 0, sizeof(d));
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i) d[j]++;
}

ll tr[N<<2];
int mx[N<<2];
void push_up(int rt) {
    tr[rt] = tr[rt<<1] + tr[rt<<1|1];
    mx[rt] = max(mx[rt<<1], mx[rt<<1|1]);
}

int a[N];
void build(int l, int r, int rt) {
    if (l == r) { tr[rt] = mx[rt] = a[l]; return; }
    int mid = (l + r) >> 1;
    build(l, mid, rt<<1), build(mid+1, r, rt<<1|1);
    push_up(rt);
}

void update(int x, int y, int l, int r, int rt) {
    if (mx[rt] <= 2) return;
    if (l == r) { tr[rt] = mx[rt] = d[tr[rt]]; return; }
    int mid = (l + r) >> 1;
    if (x <= mid) update(x, y, l, mid, rt<<1);
    if (y > mid) update(x, y, mid+1, r, rt<<1|1);
    push_up(rt);
}

ll query(int x, int y, int l, int r, int rt) {
    if (x <= l && r <= y) return tr[rt];
    int mid = (l + r) >> 1;
    ll ans = 0;
    if (x <= mid) ans += query(x, y, l, mid, rt<<1);
    if (y > mid) ans += query(x, y, mid+1, r, rt<<1|1);
    return ans;
}

int n, m;
int main() {
    fast;
    init(); cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, n, 1);
    for (int i = 1, op, l, r; i <= m; ++i) {
        cin >> op >> l >> r;
        if (op == 1) update(l, r, 1, n, 1);
        else cout << query(l, r, 1, n, 1) << '\n';
    }
    return 0;
}