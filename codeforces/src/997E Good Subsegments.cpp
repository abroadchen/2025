//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..

l, r	区间端点
mn	区间最小值（注意这里的"最小值"与题意无关，是辅助性质，见下）
num	区间内等于 mn 的叶子个数
ans	见扫描时的累加语义
lz	区间加标记（加到 mn 上）
lz2	"对当前达到 mn 的点加 ans"的标记
这棵线段树比较"非标准"——它用 mn 作为某种里程碑标记，num 统计最小值数量，用来做"只在达到某条件的点上累加 ans"
addmn：区间整体加 num（更新 mn 和懒标记）。
addans：给当前节点中所有 mn 最小的叶子（共 num 个）‍的 ans 各加 num。lz2 是给这些"达到最小值的点"加的懒标记
区间加 lz 正常下传。
lz2 只能下传给子节点中 mn 仍等于父节点 mn 的那一侧（只有它们才合法收到"最小点加 ans"）
mn 取左右较小，num 统计等于该最小值的叶子数，ans 直接相加
每个叶子 mn = l（下标）, num=1。初始每个位置 i 的 mn = i 是一个关键设定，配合后面 addmn(1,-1)
都是标准线段树区间操作，查询返回区间 ans 之和。注意 ask 里也 push_down
扫描右端点 i，每到一个 i 维护线段树，使位置左端点 x 上的值 = 以 i 为右端点、x 为左端点那段 [x,i] 的 (max−min)。ask(l,r) 即所需之和。分段解释：

1. addmn(1, -1) 与 mn 的作用

初始每个叶子 mn = 下标 i。每次 addmn(1,-1) 使整个数组的 mn 值整体 −1。这样在任意时刻，位置 x 的 mn 恰好等于 (i − x)（因为每多扫一个右端点它减一次）。mn == 0 意味着 x == i（即左端点等于当前右端点），代表"长度为 0/单个点"这一基准。num 统计的就是"当前右端点基准点"的个数——恰为 1 个（位置 i）。这一巧妙设定让 mn 同时承担"距离计数"与"标记当前基准点"双重职责。

2. 单调栈维护 max，区间加差值

右端点增大到 i，新元素 a[i] 可能成为新的最大值。
经典单调栈：弹出栈顶直到栈内 a 递减。mx[tp1] 是某个旧的"最大值控制区段"的右边界。
每次弹出时，对 [mx[tp1-1]+1, mx[tp1]] 这段左端点区间，它们的 max 从 a[mx[tp1]] 升为 a[i]（因为以 i 为右端点的子段 max 更新为更大的新值），所以给这段 + (a[i]-a[mx[tp1]])。
这让"位置 x 上的值"从 (旧max−min) 变成 (新max−min)
3. 单调栈维护 min，区间加差值

同理，弹出使新区间 min 从 a[mn[tp2]] 降到 a[i]，对对应左端点区间加 (a[mn[tp2]]-a[i])。

4. addans(1,1) —— 记录贡献

扫描到右端点 i 后，需要把"以 i 为右端点的所有子段 (x..i) 的值"累加进最终答案。这通过 addans(1,1) 完成：对当前 mn 最小的点（即 x=i 的基准点）‍ans +1。配合 lz2 下传机制，这条"新基准点的 +1"会被正确扩散记录。这里的 mn 最小值点恰好就是刚进来的位置 i（因为它最"新"，mn 最小），所以每次 addans 就是把第 i 个点的贡献计入。

严格来说，本题中 addans(1,1) 配合"只有达到全局最小 mn 的点才收到"这一规则，把每条子段的贡献积累到 ans 中，而 ask 把区间内所有这样的累加值求和。
5. 回答询问

把询问按 r 排序，当扫描到 i == 询问.r 时，直接 ask(l, r) 取区间 ans 之和作为答案
每个元素进出单调栈各一次（均摊 O(n)），每次 change 是 O(log n)。
每次右端点一次 addmn、一次 addans，每次询问一次 ask。
总复杂度 O((n + m) log n)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5;

struct tree { int l, r, mn, num, lz, lz2, ans; } t[N<<2];
struct node { int l, r, id; } q[N];
bool cmp(node a, node b) { return a.r < b.r; }

void addmn(int now, int num) { t[now].mn += num; t[now].lz += num; }
void addans(int now, int num) { t[now].ans += t[now].num*num; t[now].lz2 += num; }

void push_down(int now) {
    if (t[now].lz) {
        addmn(now<<1, t[now].lz); addmn(now<<1|1, t[now].lz);
        t[now].lz = 0;
    }
    if (t[now].lz2) {
        if (t[now<<1].mn == t[now].mn) addans(now<<1, t[now].lz2);
        if (t[now<<1|1].mn == t[now].mn) addans(now<<1|1, t[now].lz2);
        t[now].lz2 = 0;
    }
}
void push_up(int now) {
    t[now].mn = min(t[now<<1].mn, t[now<<1|1].mn);
    t[now].num = 0;
    if (t[now<<1].mn == t[now].mn) t[now].num += t[now<<1].num;
    if (t[now<<1|1].mn == t[now].mn) t[now].num += t[now<<1|1].num;
    t[now].ans = t[now<<1].ans + t[now<<1|1].ans;
}
void build(int now, int l, int r) {
    t[now].l = l; t[now].r = r; t[now].mn = l; t[now].num = 1;
    if (l == r) return;
    int mid = (l+r) >> 1;
    build(now<<1, l, mid); build(now<<1|1, mid+1, r);
}
void change(int now, int l, int r, int val) {
    if (l <= t[now].l && t[now].r <= r) { addmn(now, val); return; }
    push_down(now);
    int mid = (t[now].l + t[now].r) >> 1;
    if (l <= mid) change(now<<1, l, r, val);
    if (r > mid) change(now<<1|1, l, r, val);
    push_up(now);
}
int ask(int now, int l, int r) {
    if (l <= t[now].l && t[now].r <= r) return t[now].ans;
    push_down(now);
    int mid = (t[now].l + t[now].r) >> 1;
    int ans = 0;
    if (l <= mid) ans += ask(now<<1, l, r);
    if (r > mid) ans += ask(now<<1|1, l, r);
    return ans;
}

int n, a[N], m, tp1, tp2, mx[N], mn[N], ans[N];
signed main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    cin >> m;
    rep(i,m) cin >> q[i].l >> q[i].r, q[i].id = i;
    sort(q+1, q+1+m, cmp);
    build(1,1,n);
    for (int i = 1, j = 1; i <= n; i++) {
        addmn(1, -1);
        while (tp1 && a[mx[tp1]] < a[i]) {
            change(1,mx[tp1-1]+1, mx[tp1], a[i]-a[mx[tp1]]);
            tp1--;
        }
        mx[++tp1] = i;
        while (tp2 && a[i] < a[mn[tp2]]) {
            change(1,mn[tp2-1]+1,mn[tp2],a[mn[tp2]]-a[i]);
            --tp2;
        }
        mn[++tp2] = i;
        addans(1,1);
        while (q[j].r == i && j <= m) ans[q[j].id] = ask(1,q[j].l,q[j].r), j++;
    }
    rep(i,m) cout << ans[i] << '\n';
    return 0;
}