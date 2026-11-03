//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
定义查询函数，入参是元素列表 vec。
取大小 sz；若 sz ≤ 1 直接返回 0（一个元素不构成边/不成对）。
向判题系统发起交互式查询：输出 ? sz，然后输出 sz 个元素（空格分隔）。读取返回的 x 并返回
用途：这是一个"询问集合中是否有边/异类关系"的查询，返回 0（无）或非 0（有，通常是 1）
在左集合 l 与右集合 r 之间寻找一条边。cr = qry(r) 先询问整个右集合 r 的"内部结构值"，作为参照值
res：初始等于整个右集合 r（用于逐步扩大查询集合）。
tmp：暂时存放每次新增的元素，便于回退
二分查找（双指针向中间收缩）。mid 是 l 的中间下标。
把左集合 l 的 [L..mid] 段元素临时加进 res（同时记录到 tmp 以便删除）
查询两个值：

tot = qry(res)：查询"右集合 r + l 中 [L..mid] 段"的总体返回值；
cl = qry(tmp)：查询"l 中 [L..mid] 段"单独的值。
查询完立刻把刚才加入的元素 pop 掉，恢复 res 原状
cl + cr 表示 l 段 + r 集合"各自独立"的值之和。
如果 tot == cl + cr，说明 l 段与 r 之间没有产生新的关联边（值等于相加），则该段不含答案，收缩到右半边：L = mid+1。
否则说明要找的边落在 [L..mid] 内，收缩：R = mid。
循环结束时 L == R，即找到了 l 中那个关键元素 cr = l[L]
现在已锁定 l 中元素 cr = l[L]。接着在右集合 r 里定位与之成边的元素：

把 res 重置为只含 cr。
二分范围改为 r 的 [0, size-1]。
在 r 中二分找与 cr 成边的元素。这里 res 最初只含 cr。查询 tot = qry(res)（此时 res = {cr} + r 的 [L..mid] 段）与 cl = qry(tmp)（tmp 是 r 的 [L..mid] 段）
因为 res 固定含 cr，若 tot == cl 表示 cr 与 r 段无关联，该段不含答案 → L = mid+1；
否则含答案 → R = mid。
循环结束锁定 r[L]，返回 {cr, r[L]}——即 l 与 r 之间找到的一条边（两端点 0-based idx 已在全局位置确定后由调用方处理）。
add 总结：在两个候选集合 l、r 之间，通过两次二分，各定位到一个端点，找到一条"跨集合"的边
对集合 vc 递归寻找内部某条边。若集合恰好 2 个元素，直接返回这一对。
把 vc 按中点拆成两半，前半 vl。
查询左半 vl：若左半内部已有边（返回值非 0），递归 find(vl)。
构造右半 vr，查询；若右半内部有边，递归 find(vr)。
两半内部各自无边的边，唯一可能在两半之间，调用 add(vl, vr) 找跨半的边。

find 总结：分治地在一组节点中定位一条存在的边。
nxt：记录每个节点指向"通向目标"的下一跳。
g[N]：邻接表（建好的树）。
dfs(u, f, rt)：从 u（父 f）出发，寻找是否有到 rt 的路径。若 u == rt，返回 true
遍历 u 的邻接点 v（跳过父节点 f）：

若子树 v 中能到达 rt（递归返回 true），则整条路径会经过 u → v，置 flg=true 并记录 nxt[u] = v。
累加 cc += flg：cc 统计路径上的节点数。
返回 flg 表示"本子树能否到达 rt"。
dfs 总结：在树中从起点沿 nxt 一步步走到目标 rt，cc 记录路径上经过的节点个数。

读入节点总数 n。S（已并入的节点集合）、lc/rc（按颜色分组的白/黑集合）、T（待并入节点）
初始把节点 1 放入 S 和 lc（设左侧/0色），其余 2..n 放入待处理集合 T。
循环直到所有节点都并入 S。每次调用 add(S, T)，在已并入集合 S 与剩余集合 T 之间找一条边，得到端点 fst（属于 S）、snd（属于 T）
把 snd 从 T 移到 S（T 删除，S 加入）。
在邻接表 g 中连接 fst 与 snd（形成树边）
给新节点 snd 染色：col[snd] = col[fst]^1，即与 fst颜色相反（0/1 交替）。按颜色分别放入 rc（1色）或 lc（0色）。

结论：这里通过染色把节点分成两组（二分图的两部），此时建出的图是树（每次都连接一条新边，保证无环）
分别查询 0 色组 lc 和 1 色组 rc 的内部是否有"边/冲突关系"（即组内是否出现异常连接）。
若两组内部都没有冲突（!cl && !cr），说明染色合法（图是二分图），输出 "Y"、一组节点个数及 0 色组节点，结束。
若左边没冲突而右边有冲突，交换 lc 与 rc，把"有冲突"的组放到 lc 继续处理。
在冲突组 lc 内用 find 找到一条存在冲突的边 (fst, snd)。
在已建好的树 g 上，从 fst 出发 DFS 到 snd，走遍路径，同时记录 nxt 和路径节点数 cc。因为这条边连接了同色（冲突）的两点，DFS 可找到一条由树边构成的路径
输出 "N" 和路径长度（cc 是 dfs 里经过的中间节点数，加 1 计起点？注意这里语义）
沿 nxt 一路输出从 fst 到 snd 的路径节点（最后输出 snd），即一条"奇数环"（奇环/冲突证据）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define vi vector<int>
#define ii pair<int, int>
using namespace std;

constexpr int N = 605;

int qry(vi vec) {
    int sz = (int) vec.size();
    if (sz <= 1) return 0;
    cout << "? " << sz << endl;
    for (int i = 0; i < sz; i++) cout << vec[i] << ' ';
    cout << endl;
    int x; cin >> x;
    return x;
}

ii add(vi l, vi r) {
    int L = 0, R = (int)l.size()-1, cr = qry(r);
    vi res = r, tmp;
    while (L != R) {
        int mid = (L+R)>>1;
        for (int i = L; i <= mid; i++) res.push_back(l[i]), tmp.push_back(l[i]);
        int tot = qry(res), cl = qry(tmp);
        for (int i = L; i <= mid; i++) res.pop_back(), tmp.pop_back();
        if (tot == cl + cr) L = mid + 1; else R = mid;
    }
    cr = l[L], L = 0, R = (int)r.size()-1, res = {cr};
    while (L != R) {
        int mid = (L+R)>>1;
        for (int i = L; i <= mid; i++) res.push_back(r[i]), tmp.push_back(r[i]);
        int tot = qry(res), cl = qry(tmp);
        for (int i = L; i <= mid; i++) res.pop_back(), tmp.pop_back();
        if (tot == cl) L = mid + 1; else R = mid;
    }
    return {cr, r[L]};
}

ii find(vi vc) {
    if (vc.size() == 2) return {vc[0], vc[1]};
    int mid = ((int)vc.size()-1)>>1;
    vi vl, vr;
    for (int i = 0; i <= mid; i++) vl.push_back(vc[i]);
    if (qry(vl)) return find(vl);
    for (int i = mid+1; i < (int)vc.size(); i++) vr.push_back(vc[i]);
    if (qry(vr)) return find(vr);
    return add(vl, vr);
}

int nxt[N], cc;
vi g[N];
bool dfs(int u, int f, int rt) {
    if (u == rt) return true;
    bool flg = false;
    for (int v : g[u]) if (v != f) {
        if (dfs(v, u, rt))
            flg = true, nxt[u] = v;
    }
    cc += flg;
    return flg;
}

int n, col[N];
vi S, lc, T, rc;
int main() {
    fast;
    cin >> n; S.push_back(1), lc.push_back(1);
    for (int i = 2; i <= n; i++) T.push_back(i);
    while ((int)S.size() != n) {
        auto [fst, snd] = add(S,T);
        T.erase(ranges::find(T, snd)), S.push_back(snd);
        g[fst].push_back(snd), g[snd].push_back(fst);
        col[snd] = col[fst]^1;
        if (col[snd]) rc.push_back(snd);
        else lc.push_back(snd);
    }
    int cl = qry(lc), cr = qry(rc);
    if (!cl && !cr) {
        cout << "Y " << lc.size() << '\n';
        for (int i : lc) cout << i << ' ';
        return cout << '\n', 0;
    }
    if (!cl) swap(lc, rc);
    auto [fst, snd] = find(lc);
    dfs(fst, 0, snd);
    cout << "N " << cc+1 << '\n';
    for (int i = fst; i != snd; i = nxt[i]) cout << i << ' ';
    return cout << snd << '\n', 0;
}