//
// Created by Psy.C on 2026/9/14.
//
/**
标准树状数组，用于统计逆序对 / 每个元素前/后有多少个更大/更小的元素
这是一个上三角 3×3 矩阵（a[i][j]，j>=i）的"段合并"。merge(x,y) 把两个段的统计合并成一个段：

对角线上：z.a[i][i] += x.a[i][i] + y.a[i][i]（把两段的对角统计相加）。
上三角：z.a[i][k] += x.a[i][j] * y.a[j+1][k]，即跨越左段和右段的组合相乘（类似线段树合并 / 区间 DP 转移）。
init(x,y,z) 构造一个对角矩阵节点：a[0][0]=x, a[1][1]=y, a[2][2]=z。这通常表示单个位置携带的三个值（如：在这个值左侧的计数、自身、右侧的计数）。

这个 merge 本质是 「区间 DP 合并 + 乘加组合」，常用于统计满足 A < B < C 关系的三元组数量
标准线段树，f[i] 存节点矩阵，merge 合并左右儿子。用于对某个值的出现位置列表维护"三元计数"
离散化 a[i] 到 1..m。
vc[a[i]] 存该值所有出现的位置
pcnt[i]：a[i] 前面有多少个小于等于/小于 a[i] 的数（逆序对语义）。
scnt[i]：a[i] 后面有多少个小于 a[i] 的数。
经典左右计数，分别是"左边≤自己"和"右边<自己"
对每个不同的值 i，在其所有出现位置 vc[i] 上建线段树。
每个位置 v：init(pcnt[v], 1, scnt[v]) — 即 a[0][0]=pcnt[v]（左边计数），a[1][1]=1，a[2][2]=scnt[v]（右边计数）。
通过 merge 组合，tr.f[rt[i]].a[0][2] 统计该值内部满足某种关系的三元组数量，累加到 ans。
含义：ans 是所有满足 A<i<B 且位置左右关系 的三元结构总数
每次操作先减去该值整棵线段树旧贡献，再更新单点（置空 init(0,0,0) 或恢复 init(pcnt,1,scnt)），再加回新贡献。
opt==1 删除/禁用位置，opt==2 恢复。
每次输出更新后的 ans。
这就是动态维护全局 ans 的经典套路：单点更新 × 线段树合并
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define low_bit(i) (i&(-i))
using namespace std;

constexpr int N = 1e5, M = (N<<2)+5, mod = 1e9+7;

struct bit {
    int f[N+5];
    void add(int i) {
        while (i <= N) { f[i]++; i += low_bit(i); }
    }
    int query(int i) {
        int ans = 0;
        while (i) { ans += f[i]; i -= low_bit(i); }
        return ans;
    }
} bt;

struct node { int a[3][3]; } ept;
node merge(node x, node y) {
    node z = ept;
    for (int i = 0; i < 3; ++i) {
        for (int j = i; j < 3; ++j) {
            (z.a[i][j] += x.a[i][j] + y.a[i][j]) %= mod;
            for (int k = j+1; k < 3; ++k)
                (z.a[i][k] += x.a[i][j]*y.a[j+1][k]) %= mod;
        }
    }
    return z;
}
node init(int x, int y, int z) {
    node ans = ept;
    ans.a[0][0] = x, ans.a[1][1] = y, ans.a[2][2] = z;
    return ans;
}

#define mid ((l+r)>>1)
struct sgt {
    node f[M];
    int tl[M], tr[M], cnt;
    int build(int i, int l, int r) {
        if (!i) i = ++cnt;
        if (l == r) return i;
        tl[i] = build(0, l, mid);
        tr[i] = build(0, mid+1, r);
        return i;
    }
    void update(int i, int l, int r, int pos, node x) {
        if (l == r) { f[i] = x; return; }
        if (pos <= mid) update(tl[i], l, mid, pos, x);
        else update(tr[i], mid+1, r, pos, x);
        f[i] = merge(f[tl[i]], f[tr[i]]);
    }
} tr;

int a[N+5], lsh[N+5], pcnt[N+5], scnt[N+5], rt[N+5], pos[N+5];
vector<int> vc[N+5];
signed main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], lsh[i] = a[i];
    sort(lsh+1, lsh+n+1);
    int m = unique(lsh+1, lsh+n+1) - lsh - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(lsh+1, lsh+m+1, a[i]) - lsh;
        vc[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        pcnt[i] = bt.query(a[i]);
        bt.add(a[i]);
    }
    memset(bt.f, 0, sizeof bt.f);
    for (int i = n; i >= 1; --i) {
        scnt[i] = bt.query(a[i]);
        bt.add(a[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vc[i].empty()) {
            rt[i] = tr.build(0, 1, vc[i].size());
            int it = 0;
            for (auto v : vc[i]) {
                it++;
                pos[v] = it;
                tr.update(rt[i], 1, vc[i].size(), it, init(pcnt[v], 1, scnt[v]));
            }
            (ans += tr.f[rt[i]].a[0][2]) %= mod;
        }
    }
    int q; cin >> q;
    for (int i = 1, opt, x; i <= q; ++i) {
        cin >> opt >> x;
        if (opt == 1) {
            (ans += mod - tr.f[rt[a[x]]].a[0][2]) %= mod;
            tr.update(rt[a[x]], 1, vc[a[x]].size(), pos[x], init(0, 0, 0));
            (ans += tr.f[rt[a[x]]].a[0][2]) %= mod;
        }
        if (opt == 2) {
            (ans += mod - tr.f[rt[a[x]]].a[0][2]) %= mod;
            tr.update(rt[a[x]], 1, vc[a[x]].size(), pos[x], init(pcnt[x], 1, scnt[x]));
            (ans += tr.f[rt[a[x]]].a[0][2]) %= mod;
        }
        cout << ans << '\n';
    }
    return 0;
}