//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
l, r：区间左右界。mx：区间最大值。mn：区间最小值。
ans：区间内"最大 (max - min)"（即最大差值）
合并：区间 T = ls, rs。
T.mx = 两子区间 mx 的较大者；T.mn = 两子区间 mn 的较小者。
T.ans：
rs.mx - ls.mn：跨两子区间时，左边的"较小值"配右边的"较大值"产生的最大差值；
ls.ans、rs.ans：各自内部的差值；
三者取最大。
这是经典的"区间内最大差值（max – min，且右边的 max 减左边的 min 也算）"合并模板。它要求最优的 mx 出现在 mn 之后（跨左右子区间）
递归建树，节点 p 负责区间 [l,r]。
叶子：mx = mn = a[l]，ans = -inf（单个元素不存在"差值"，给极小值负无穷）。
非叶子：分左右递归建树后 push_up 合并
标准线段树区间查询：
若当前节点区间被 [l,r] 完整包含，直接返回该节点信息。
否则判断 [l,r] 落在左半或右半：
l > mid：完全在右子树 → 递归右子。
mid >= r：完全在左子树 → 递归左子。
两侧都有 → 分别查询 ls, rs，用一个临时 ans{} 做 push_up 合并后返回。
返回的 node 里包含该区间上的 mx, mn, ans
cin >> n >> m。

对 i = 1..n：

读入 d[i] 和 a[i]（此时 a[i] 是原始输入值）。
s[i] = s[i-1] + a[i]：把原始 a[i] 累加成前缀和 s。
重写 a[i] = i*m - s[i]：把 a 数组改为一个"线性减前缀"的序列。
if (i > 1) d[i-1] = d[i] - d[i-1]：把 d 做成差分序列（后减前），存在 d[1..n-1]。注意这里原地覆盖，d[1..n-1] 变成差分值，而 d[n] 保持原值不用了。
build(0, n, 1)：对重写后的 a[0..n] 建线段树。（注意用了 a[0]，下标 0 也有有效值，因为 DB 数组 a[0] 默认 0。）
维护一个单调递减栈（栈内 d 值严格递减）。
对每个 i（1..n-1）：
弹出所有 d[栈顶] <= d[i] 的元素（保持严格递减）。
若栈空 → l[i] = 0（没有更左的更小值，左边界是 0）；否则 l[i] = 栈顶（左边第一个 d 比 d[i] 小/等于的位置的右边一个——即 d 在此之后开始递减）——实际是"以 d[i] 为底的递减区域左端点"。
st.push(i)。
结束后清空栈。
作用：对每个差分位置 i，找到它左边第一个 d ≤ d[i]（即让它"不再是严格递减"的位置），从而确定一段以 d[i] 为最高的严格递减区间左边界
反向（从右往左）用同样的单调递减栈，得到右边第一个 d ≤ d[i] 的左边一个位置，即右边界 r[i]；若栈空则右边界到 n。
rep(i,n) ans = max(ans, a[i]-a[i-1])：先考虑所有相邻差（a[i]-a[i-1]）作为候选最大值。
rep(i,n-1) ans = max(ans, qry(l[i], r[i], 1).ans - d[i]*d[i])：
对每个 i（1..n-1），在区间 [l[i], r[i]] 上做线段树查询，取返回节点的 .ans（区间内 mx - mn 的最大差值），然后减去 d[i]*d[i]，作为一个候选答案，与全局 ans 比较取 max。
d[i] 此时是差分值，d[i]^2 作为惩罚项。
输出 ans。
l[i]、r[i] 定义在 1..n-1，但 l[i]=0 可能为 0，因此 qry(0,...) 会用到 a[0]（build 里建了 [0,n]）。r[i]=n 时查询到 n，也合法
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 1e6+10, inf = 1e16;

struct node { int l, r, mx, mn, ans; } t[N<<1];

void push_up(node &T, node ls, node rs) {
    T.mx = max(ls.mx,rs.mx), T.mn = min(ls.mn, rs.mn);
    T.ans = max(rs.mx-ls.mn,max(ls.ans,rs.ans));
}

int a[N];
void build(int l, int r, int p) {
    t[p].l = l, t[p].r = r;
    if (l == r) { t[p].mx = t[p].mn = a[l], t[p].ans = -inf; return; }
    int mid = (l+r)>>1;
    build(l,mid,p<<1); build(mid+1,r,p<<1|1);
    push_up(t[p], t[p<<1], t[p<<1|1]);
}
node qry(int l, int r, int p) {
    if (l <= t[p].l && t[p].r <= r) return t[p];
    int mid = (t[p].l + t[p].r)>>1;
    if (l > mid) return qry(l,r,p<<1|1);
    if (mid >= r) return qry(l,r,p<<1);
    node ls = qry(l,r,p<<1), rs = qry(l,r,p<<1|1), ans{};
    push_up(ans,ls,rs);
    return ans;
}

int n, m, d[N], s[N], l[N], r[N], ans;
stack<int> st;
signed main() {
    fast;
    cin >> n >> m;
    rep(i,n) {
        cin >> d[i] >> a[i]; s[i] = s[i-1] + a[i], a[i] = i*m - s[i];
        if (i > 1) d[i-1] = d[i] - d[i-1];
    }
    build(0,n,1);
    rep(i,n-1) {
        while (!st.empty() && d[st.top()] <= d[i]) st.pop();
        if (st.empty()) l[i] = 0; else l[i] = st.top();
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = n-1; i >= 1; i--) {
        while (!st.empty() && d[st.top()] <= d[i]) st.pop();
        if (st.empty()) r[i] = n; else r[i] = st.top();
        st.push(i);
    }
    rep(i,n) ans = max(ans, a[i]-a[i-1]);
    rep(i,n-1) ans = max(ans, qry(l[i],r[i],1).ans-d[i]*d[i]);
    cout << ans;
    return 0;
}