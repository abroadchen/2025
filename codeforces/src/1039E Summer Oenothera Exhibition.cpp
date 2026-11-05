//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
ST 表（RMQ）‍：快速查询区间 [l,r] 内"最大值 - 最小值"（即区间极差 = max - min）。
Link-Cut Tree（LCT）‍：用于动态维护"哪些段被合并/拆分"以及统计连通块大小。
分块 + 离线排序：用阈值单调性批量回答所有询问
标准的 LCT 实现，维护森林。这里每个节点代表一个数组元素/段，通过 LCT 的 link/cut 动态维护"段与段之间的连接关系"，用于统计"某个节点往右能延伸多远的连通块"
p = 父指针，l/r = 左右儿子（splay 上的）。
sz = 以该节点为根的虚实辅助树大小。
初始 sz = v（构造时传入 1，表示每个节点初始大小为 1）
判断 x 是否是所在实链(splay)的根：若父节点左右儿子都不是 x，说明 x 是这条辅助树的根。
这是 LCT 中判断"是否可以旋转到顶"的关键
自底向上维护子树大小：左儿子大小 + 右儿子大小 + 自己(1)
标准的 splay zig / zig-zig 旋转。
关键：只有当 p 不为所在实链根时，才把 x 接续到 g 的儿子位置；若 p 是根，则断开与 g 的父子关系（x.p = g 但 g 不认指向——这是 LCT 用虚边连接实链的方式）。
旋转后更新 p 和 x 的大小
标准的 splay 双旋操作，把 x 旋到所在实链（splay）的根。
(x==a[p].l)==(p==a[g].l) 判断是否同为"左左/右右"（zig-zig），是则先转父再转自己；否则 zig-zag 转两次
核心操作：打通 x 到树根的实链路径。
每次把 x 旋到顶，记下它的父（沿虚边向上），把父的右儿子设成 x（即把 x 所在链接续到父链）。
循环直到没有父节点（到达整棵树的根）
返回 x 所在整棵树的根（连通块代表元）。常用于"跳到下一段起点"。
连接 x 到 y 上：把 x 旋到顶，设其父为 y（虚边连接）。注意：经典 LCT 的 link 通常还要 access(y)，这里简化为只设虚父
切断 x 与其左儿子（即它左边的前驱节点）‍的连接：access(x) 后 x.l 就是它在实链上的左邻（前一段），把这对父子关系断开。用于"拆除前一段与当前段的连接"
返回节点 x 所在连通块（segment 链）的大小。用于统计当前段长度
定义 pair 组合运算：取两 pair 的 first 最大、second 最小。
因为 first = 最大值、second = 最小值，合并两个区间就是新区间的 max 和 min
构建标准的 Sparse Table，st[i][j] = 从 j 开始长度 2^i 的区间 [j, j+2^i-1] 的 (max, min)。
lg[] 预处理每个长度对应的 log2（下取整）。
op 是上面定义的"max 与 min"合并
核心功能：O(1) 求区间 [l,r] 的 极差 = 最大值 - 最小值。
用两个长度为 2^s 的重叠区间覆盖 [l,r]，合并得 (max, min)。
给定起点 pos 和阈值 w，二分找出满足 qry(pos, mid) <= w（区间极差不超过 w）的最远右端点，返回第一个极差 > w 的位置 r。
因为有单调性（右端点越远极差越大），可用二分。返回 r 即"下一段的起点"

读 n 个数组值、窗口阈值 w、q 次询问。
每个位置初始在 LCT 中自成一个节点（大小 1）。
输入值其实是"减掉的量"，真实极差阈值 = w - 输入。
pair first = 变换后的阈值，second = 原询问编号
b 是分块块大小，取 sqrt(n) 与 100 的较小者，用于平衡复杂度。
询问按阈值排序 → 离线处理，利用阈值单调性
这一块最关键也最复杂，是"分块离线预处理"：

对每个起点 i，枚举它前方所有可能的"段边界"（最多 b 个，因为 nxt 每次单调右移且限制在 i+b 内）。
dif 记录当前段的极差。
每次把 (i, nxt) 这段"前缀段划分"挂到对应阈值分组 v[pos] 下。
最后默认段 (i, 0)（0 表示"到数组末尾"）也挂上。
作用：把所有"以 i 为起点、长度≤b"的合法段预先分门别类（按它们需要的阈值 dif 分组），供后续每次询问 O(1) 取出
for (auto [fst, snd] : v[i])：取出本阈值 i 需要处理的所有 (fst, snd) 段。
cut(fst)：断开 fst 与左边前驱的连接。
link(fst, snd)：若 snd 非 0，把 fst 连到 snd（右邻）上。这实现了动态维护段的连接关系，随着阈值变化，段被合并/拆分。
while (cur <= n)：从位置 1 开始向右走，累加统计"当前连通块（段）大小"，然后跳到该段终点，再找下一段起点。
cc += LCT::qry(cur)：累加当前段长度。
cur = LCT::getrt(cur)：跳到段终点。
cur = find(cur, c[i].first)：用阈值二分找下一段起点。
ans[c[i].second] = cc-1：按原编号记录答案。cc 是总块数，-1 通常是因为块与块之间有 块数-1 个边界/间隔（即"切的刀数"）
按原询问顺序输出答案。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5;

namespace LCT {
    struct node {
        int p, l, r, sz;
        node(int v=0) { p = l = r = 0, sz = v; }
    } a[N];
    bool isrt(int x) { return a[a[x].p].l != x && a[a[x].p].r != x; }
    void push_up(int x) { a[x].sz = a[a[x].l].sz + a[a[x].r].sz + 1; }
    void rotate(int x) {
        int p = a[x].p, g = a[p].p;
        if (!isrt(p)) (p==a[g].l ? a[g].l : a[g].r) = x;
        a[x].p = g;
        if (x == a[p].l) { a[p].l = a[x].r; a[a[p].l].p = p; a[x].r = p; a[p].p = x; }
        else { a[p].r = a[x].l; a[a[p].r].p = p; a[x].l = p; a[p].p = x; }
        push_up(p); push_up(x);
    }
    void splay(int x) {
        while (1) {
            if (isrt(x)) break;
            if (isrt(a[x].p)) { rotate(x); break; }
            int p = a[x].p, g = a[p].p;
            if ((x == a[p].l) == (p == a[g].l)) rotate(p), rotate(x);
            else rotate(x), rotate(x);
        }
    }
    void access(int x) {
        splay(x); a[x].r = 0; push_up(x);
        while (a[x].p) { splay(a[x].p); a[a[x].p].r = x; push_up(a[x].p); splay(x); }
    }
    int getrt(int x) {
        access(x);
        while (a[x].l) x = a[x].l;
        splay(x);
        return x;
    }
    void link(int x, int y) { splay(x); a[x].p = y; }
    void cut(int x) { access(x); a[x].l = a[a[x].l].p = 0; }
    int qry(int x) { access(x); return a[x].sz; }
}

ii operator+(const ii &x, const ii &y) { return {max(x.first, y.first), min(x.second, y.second)}; }

int pw[20], lg[N], n, a[N];
ii st[20][N];
void init() {
    pw[0] = 1;
    for (int i = 1; i < 20; i++) pw[i] = pw[i-1]*2;
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i>>1]+1;
    for (int i = 1; i <= n; i++) st[0][i] = {a[i], a[i]};
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + pw[i] - 1 <= n; j++)
            st[i][j] = st[i-1][j] + st[i-1][j+pw[i-1]];
}

int qry(int l, int r) {
    int s = lg[r-l+1];
    auto [fst, snd] = st[s][l] + st[s][r-pw[s]+1];
    return fst - snd;
}

int find(int pos, int w) {
    int l = pos, r = n+1;
    while (r - l > 1) {
        int mid = (l+r)>>1;
        if (qry(pos, mid) > w) r = mid; else l = mid;
    }
    return r;
}

int w, q, b, ans[N];
ii c[N];
vector<ii> v[N];
int main() {
    fast;
    cin >> n >> w >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        LCT::a[i] = LCT::node(1);
    }
    init();
    for (int i = 1; i <= q; i++) {
        cin >> c[i].first;
        c[i].first = w - c[i].first, c[i].second = i;
    }
    b = min(100.0, sqrt(n)+0.5);
    sort(c+1, c+q+1);
    for (int i = 1; i <= n; i++) {
        int dif = 0, nxt = find(i, 0);
        while (nxt <= min(n, i+b)) {
            int pos = lower_bound(c+1,c+q+1,make_pair(dif,0)) - c;
            v[pos].emplace_back(i,nxt);
            dif = qry(i, nxt);
            nxt = find(i, dif);
        }
        int pos = lower_bound(c+1,c+q+1,make_pair(dif,0)) - c;
        v[pos].emplace_back(i,0);
    }
    for (int i = 1; i <= q; i++) {
        for (auto [fst, snd] : v[i]) {
            LCT::cut(fst);
            if (snd) LCT::link(fst, snd);
        }
        int cur = 1, cc = 0;
        while (cur <= n) {
            cc += LCT::qry(cur);
            cur = LCT::getrt(cur);
            cur = find(cur, c[i].first);
        }
        ans[c[i].second] = cc-1;
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}