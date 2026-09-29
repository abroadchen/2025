//
// Created by Psy.C on 2026/9/29.
//
/**
N：事件数组容量（1e6）。
M：树状数组大小（1e5）。
node {l, r, t, val, type}：
l, r：区间端点 / 位置信息。
t：时间戳（操作编号）。
val：权重值（对 type=1 是"贡献量"，对 type=2 是"查询编号"）。
type：1 表示"修改/贡献"事件，2 表示"查询"事件。
n（数组长度）、bit T（树状数组，支持区间求和）
标准的树状数组：update(p, val) 在 p 处加 val；query(p) 求前缀和（[1,p]）。
ll ans[N]：存每个查询的答案

"修改点 r 位置的贡献"加到"查询区间 [l,r]"的答案里：

递归地把操作序列按时间对半分。
归并时按 l 排序：
若 cq[p1].l >= cq[p2].l（左半的 l 较大），且是 type=1 → 在 cq[p1].r 处 update 加 val。
否则取右半，若是 type=2（查询）→ 累加 T.query(cq[p2].r)（前缀和，即"所有 r ≤ 查询.r 且 l ≥ 查询.l 的修改贡献"）。
归并结束后，回滚左半所有 type=1 的修改（加负值），恢复到递归前的树状数组状态（保证不互相污染）。
每层归并一次后 cq = t，完成"按 l 排序"的归并排序。
核心契约：一段修改 {l, r, val} 对查询 {l, r} 的贡献是 val，条件是"修改的 l ≥ 查询的 l 且 修改的 r ≤ 查询的 r"。

s[c]：set<int>，记录"颜色 c 出现的位置集合"（有序，从小到大）。
val[i]：位置 i 的当前颜色。
cnt：事件计数器（type=1 和 type=2 都用它编号，保证时间顺序）。
op：查询计数器
读入每个位置的颜色。
插入 s[颜色]，找到位置 i 的前驱位置 *it（同一颜色上一次出现的位置）。
若有前驱，生成一个 type=1 事件：{l = 前驱位置, r = i, val = i - 前驱}。
含义：记录"相邻两个同一颜色的位置对 (前驱, i)，间隔 i-前驱 "。
这个 val = i - 前驱（距离）用于之后统计"区间内不相邻元素距离和"之类的量
修改（a==1，把位置 b 颜色改为 c）：

若没变（val[b]==c）直接跳过。
找 b 在旧颜色 s[val[b]] 里的前驱 pre 和后继 nxt。
删除旧贡献：生成三条（带负权）type=1 事件，把旧的 (pre,b)、(b,nxt)、(pre,nxt) 对对应的 val 取负加入操作序列：
(pre,b)：val=pre-b
(b,nxt)：val=b-nxt
(pre,nxt)：val=nxt-pre
从旧集合删除 b，val[b]=c，插入新集 s[c]。
找新集合里的前驱 pre 和后继 nxt。
重新生成贡献：三条 type=1 事件，val 分别为 b-pre、nxt-b、pre-nxt。
这样借助"删除旧 + 添加新"，s[c] 中所有相邻位置对的距离和始终等于"当前该颜色内部相邻间距的某种带符号总和"。三种情况的 val 符号相反 是为了配合 CDQ 的 l 排序契约，把"撤销"也用事件表达。
查询（else，a==2）：

生成 type=2 事件 {l=b, r=c, val=++op}，即查询区间 [b,c]，答案存入 ans[op]。
对全部事件（1..cnt）做 CDQ 分治，把 type=1 的修改贡献累加到符合条件的 type=2 查询里去。
按查询编号输出每个区间查询的答案。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+5, M = 1e5+5;
struct node { int l, r, t; ll val; int type; } cq[N], t[N];

int n;
struct bit {
    ll t[M];
    static int low_bit(int x) { return x & -x; }
    void update(int p, ll val) {
        while (p <= n) t[p] += val, p += low_bit(p);
    }
    ll query(int p) const {
        ll res = 0;
        while (p > 0) res += t[p], p -= low_bit(p);
        return res;
    }
} T;

ll ans[N];
void dfs(int l, int r) {
    if (l == r) return;
    int mid = (l+r)>>1, p1 = l, p2 = mid+1;
    dfs(l, mid); dfs(mid+1, r);
    for (int i = l; i <= r; ++i) {
        if (p1 <= mid && (p2 > r || cq[p1].l >= cq[p2].l)) {
            if (cq[p1].type == 1) T.update(cq[p1].r, cq[p1].val);
            t[i] = cq[p1++];
        } else {
            if (cq[p2].type == 2) ans[cq[p2].val] += T.query(cq[p2].r);
            t[i] = cq[p2++];
        }
    }
    for (int i = l; i <= mid; ++i)
        if (cq[i].type == 1) T.update(cq[i].r, -cq[i].val);
    for (int i = l; i <= r; ++i) cq[i] = t[i];
}


set<int> s[M];
int m, val[M], cnt, op;
multiset<int>::iterator it;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        s[val[i]].insert(i);
        it = s[val[i]].find(i);
        if (it != s[val[i]].begin()) {
            --it;
            cq[++cnt] = {.l = *it, .r = i, .t = cnt, .val = i-*it, .type = 1};
        }
    }
    for (int i = 1, a, b, c, pre, nxt; i <= m; ++i) {
        cin >> a >> b >> c;
        if (a == 1) {
            if (val[b] == c) continue;
            pre = 0, nxt = 0;
            it = s[val[b]].find(b);
            if (it != s[val[b]].begin()) --it, pre = *it, ++it;
            ++it;
            if (it != s[val[b]].end()) nxt = *it;
            if (pre) cq[++cnt] = {.l = pre, .r = b, .t = cnt, .val = pre-b, .type = 1};
            if (nxt) cq[++cnt] = {.l = b, .r = nxt, .t = cnt, .val = b-nxt, .type = 1};
            if (pre&&nxt) cq[++cnt] = {.l = pre, .r = nxt, .t = cnt, .val = nxt-pre, .type = 1};
            s[val[b]].erase(b);
            val[b] = c;
            s[c].insert(b);
            pre = 0, nxt = 0;
            it = s[c].find(b);
            if (it != s[c].begin()) --it, pre = *it, ++it;
            ++it;
            if (it != s[c].end()) nxt = *it;
            if (pre) cq[++cnt] = {.l = pre, .r = b, .t = cnt, .val = b-pre, .type = 1};
            if (nxt) cq[++cnt] = {.l = b, .r = nxt, .t = cnt, .val = nxt-b, .type = 1};
            if (pre&&nxt) cq[++cnt] = {.l = pre, .r = nxt, .t = cnt, .val = pre-nxt, .type = 1};
        }
        else cq[++cnt] = {.l = b, .r = c, .t = cnt, .val = ++op, .type = 2};
    }
    dfs(1, cnt);
    for (int i = 1; i <= op; ++i) cout << ans[i] << '\n';
    return 0;
}