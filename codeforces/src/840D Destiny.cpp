//
// Created by Psy.C on 2026/9/26.
//
/**
namespace Ju：线段树，每个节点保存最多 K=4 个"多数候选值及其表决计数"（node）。
namespace cntr：每个数值的出现位置 pos[x] 向量，用于精确计数（二分）。
ask(l,r,k)：查询区间，返回"出现次数 > (r-l+1)/k 的最小值"，若无则 -1。
N：数组大小上限。
inf：用极大值表示"找不到"。
a[]：原数组（值域较大，用值直接当索引会内存越界风险，所以下面用 vector 存位置）
node 保存 K 个候选值 val[] 和对应"表决计数" cnt[]。cnt[i] <= 0 表示该槽位空（可用）。
add(x, v) —— 把值 x 以票数 v 加入候选：

若 x 已在候选里：累加票数。cnt[i] < 0 ? v : cnt[i]+v —— 若该槽计数已是负/失效状态则直接设为 v，否则累加。
若有空槽 (cnt[i] <= 0)：放入新候选。
都没有：用投票抵消——找到所有候选中最小的票数 mn，把 v 减掉 mn 并让所有候选都减 mn（相当于"新来的一批 v 票与现有最小票候选相互抵消"）。若抵消后还剩 v>0，放入空槽。
这正是 Boyer–Moore 多数投票的 K 值推广：真实众数（超过 len/k 的数）在反复抵消后必然存活在候选里。
operator+(b) —— 合并两个区间的候选（节点合并）：把 b 中所有有票候选依次 add 到本节点。
T[N<<2]：数组实现的线段树。
init：递归建树，叶子把 a[l] 加入候选（1 票），内点通过 + 合并两子候选。
ask：标准区间查询，返回区间对应的 node（合并 O(log n) 个节点的候选）。
pos[x]：值 x 出现的所有下标（升序）。
count(l,r,x)：用两次二分（lower_bound 找 ≥ l，upper_bound 找 ≤ r）得到 [l,r] 内 x 的出现次数
建线段树 + 建位置向量
取区间候选 val。
遍历 K 个候选，对其真实出现次数 count(l,r,x) 与阈值 (r-l+1)/k 比较；严格大于
(
r
−
l
+
1
)
/
k
(r−l+1)/k（即"超过 k 分之一"，当 k=2 时即超过一半 = 严格众数）则作为候选答案，取最小的。
若没找到真正的候选（都 ≤ 阈值），返回 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 3e5+10, inf = 0x3f3f3f3f;

int a[N];
namespace Ju {
#define K 4
    struct node {
        int val[K], cnt[K];
        void add(int x, int v) {
            for (int i = 0; i < K; ++i)
                if (val[i] == x) {
                    cnt[i] = cnt[i] < 0 ? v : cnt[i] + v;
                    return;
                }
            for (int i = 0; i < K; ++i)
                if (cnt[i] <= 0) {
                    val[i] = x; cnt[i] = v; return;
                }
            int mn = v;
            for (int i : cnt)
                if (i < mn) mn = i;
            v -= mn;
            for (int& i : cnt) i -= mn;
            if (v) {
                for (int i = 0; i < K; ++i)
                    if (cnt[i] <= 0) {
                        val[i] = x; cnt[i] = v; return;
                    }
            }
        }
        node operator+(node b) const {
            node ans = *this;
            for (int i = 0; i < K; ++i)
                if (b.cnt[i] > 0)
                    ans.add(b.val[i], b.cnt[i]);
            return ans;
        }
    };
    struct seg { int l, r; node v; } T[N<<2];
    void init(int l, int r, int o) {
        T[o].l = l, T[o].r = r;
        if (l == r) { T[o].v.add(a[l], 1); return; }
        int mid = (l + r) >> 1;
        init(l, mid, o<<1), init(mid+1, r, o<<1|1);
        T[o].v = T[o<<1].v + T[o<<1|1].v;
    }
    node ask(int l, int r, int o) {
        if (T[o].l == l && T[o].r == r) return T[o].v;
        int mid = (T[o].l + T[o].r) >> 1;
        if (r <= mid) return ask(l, r, o<<1);
        if (l > mid) return ask(l, r, o<<1|1);
        return ask(l, mid, o<<1) + ask(mid+1, r, o<<1|1);
    }
}

int n;
namespace cntr {
    vector<int> pos[N];
    void init() {
        for (int i = 1; i <= n; ++i) pos[a[i]].push_back(i);
    }
    int count(int l, int r, int x) {
        return upper_bound(pos[x].begin(), pos[x].end(), r) -
            lower_bound(pos[x].begin(), pos[x].end(), l);
    }
}

void init() {
    Ju::init(1, n, 1);
    cntr::init();
}
int ask(int l, int r, int k) {
    Ju::node val = Ju::ask(l, r, 1);
    int ans = inf;
    for (int i = 0; i < K; ++i)
        if (val.cnt[i] > 0) {
            if (cntr::count(l, r, val.val[i]) > (r-l+1)/k &&
                val.val[i] < ans) ans = val.val[i];
        }
    return ans == inf ? -1 : ans;
}

int m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i]; init();
    while (m--) {
        int l, r, k; cin >> l >> r >> k;
        cout << ask(l, r, k) << '\n';
    }
    return 0;
}