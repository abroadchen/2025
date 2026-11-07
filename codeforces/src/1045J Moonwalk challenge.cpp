//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
N≈1e5（节点数）、M=5e6（主席树节点上限）、L=205（模式串最大长度 200）
pi：全局变量，但实际上 nxt 也在 main 里定义了，pi 在这里似乎未在 main 用到——可能是残留/冗余声明。真正跑 KMP 用的是 main 里的 nxt[L]。
inl：树剖的入序（DFS 序号）
len：SAM 节点代表的最长串长。
tr：转移边，27 列（0..25 字母 + 可能预留）；
fail：后缀链接（parent）。
val：标记该节点是否对应某个原串的终止位置（值=集合下标）。
ls/rs/s：主席树的左右儿子和区间和（M 足够大）。
rt：每个 SAM 节点维护的主席树根。
vf：vf[i] 存 fail 树中 i 的儿子（用于自底向上合并）
tot = 1：SAM 根节点 1（空串状态）。
pi[1] = 1：根节点的位置映射（此处 pi 指 SAM 内节点号数组，跟全局 pi 趋势一致）。
tot2 = 0：主席树节点计数清零
标准 SAM 增量插入：新建状态 u 代表"整个串的最长后缀"；
沿 fail 补转移；若无 fail 则挂到根；
若 q 需分裂则建 cq，复制转移并更新 fail；
pi[ax]=u：把"第 ax 个元素（树上的某个节点）"记录到当前 SAM 状态，便于后面按 endpos 归位。
val[u]=ax：标记该状态是集合 ax 的终止位置（用于 DFS 时在主席树对应位置置 1）。
可持久化线段树插入位置 x，置为 1，合并左右儿子的和
合并两棵主席树，用于把子节点的 endpos 集合向上归并到父状态（fail 树自底向上）
标准区间查询，求 [L,R] 内 endpos 点个数（无交集或空节点直接返回 0）。
先递归所有 fail 树儿子，把儿子们的主席树合并进当前节点；
若当前状态被标记为某个集合的终止位置（val[x]），则把该集合在树剖inl对应的位置插入主席树。
这样最后 rt[u] 就包含以状态 u 代表的子串为后缀的所有 endpos 位置（按树的 DFS 序存放），便于后续区间统计
把所有节点的 fail 指针对应到父节点，建成 fail 树；从根 1 开始后序遍历构建主席树
邻接表存树，边权 z 是字符编号（0..25）
标准树剖第一遍：求父节点、子树大小、深度、重儿子。
关键：sa.ins(y, pi[x], z)——从节点 x 的 SAM 状态（pi[x]）插入边字符 z，得到 y 的终止状态 pi[y]。这相当于沿着树根到各节点的路径构建 SAM，使 SAM 包含了整棵树上"从上往下"的所有路径子串。
a[y]=z：记录 y 由父边字符
重链优先分配 DFS 序号，inr[序号]=节点（反查），top 记录链顶。
保证同一条重链上的节点编号连续，为区间查询铺路
用 top 跳跃求 LCA，标准模板

给定上界祖先 z 和步数 d，返回 x 向上第 d 个节点；若走得超过 z（含 z 本身）则返回 -1。
利用重链连续编号，在链上直接按偏移 inl[fx] + (d-dep[fx]+dep[z]) 取到节点（inr 反查）。
返回 -1 表示"不够 d 个点够到 z 之前"
将 x→z（z 是 z 的祖先）剖成若干段，对每段 DFS 序连续区间在主席树 p 上区间求和。
统计的是：状态 p 所代表子串在"x 到 z 那一段路径节点上的出现次数"

无向边建邻接表；从 1 做递归，构建 SAM 和树剖。
根节点 1 的 DFS 序、top 初始化为 1。
l1：模式串长度；c：x,y 的 LCA。
fx：从 x 向上走 l1 步到达的节点（够不到回溯返回 -1）；
fy：同理 y 那边。
px：沿着反向模式串走 SAM 转移，得到模式串反向后缀对应的 SAM 状态；
py：沿着正向模式串走，得到模式串的前缀状态
ask(x, fx, rt[px])：统计反向模式串在 x→fx 段路径上的出现次数；
ask(y, fy, rt[py])：统计正向模式串在 y→fy 段路径上的出现次数；
两者相加得第一部分答案。
把 x、y 上升到各自 fx/fy 的父节点，表示把"已统计的 l1 长度段"跳过，剩下中间未覆盖部分交给下面处理。
收集 x 到 c 的字符（自下而上，顺序是 x→c），以及 y 到 c 的字符，反转 tp2 后拼成 从 x 到 y 中间那段（经过 c）的实际字符串 tp。
tp 就是路径 x→...→c→...→y 的字符序列（去除两端已被 SAM 统计的 l1 长度段）
对模式串 z 求 nxt（前缀函数），再在拼接串 tp 上跑标准 KMP，每次完整匹配（j==l1）就 ans++，然后回退 j=nxt[j]。
这补充统计了跨越 LCA（即横跨 x 侧和 y 侧、中间经过 c）‍那部分路径上模式串 z 的出现次数——因为那部分无法用"单一方向路径上的 SAM endpos 连续区间"来覆盖，故用 KMP 兜底。
输出每组查询的答案。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; ++i)
#define per(i,j,k) for (int i=j; i>=k; --i)
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 1e5+10, M = 5e6, L = 205;

int pi[N], inl[N], n;
struct SAM {
    int tot, tot2, len[N*3], tr[N*3][27], fail[N*3], val[N*3], ls[M], rs[M], s[M], rt[N*3];
    vector<int> vf[N*3];
    void prep() { tot = pi[1] = 1; tot2 = 0; }//初始化
    void ins(int ax, int lst, int x) {//SAM 在线插入字符（标准增量构造）
        int u = ++tot, p = lst; len[u] = len[lst] + 1;
        for (; p && !tr[p][x]; p = fail[p]) tr[p][x] = u;
        if (!p) fail[u] = 1;
        else {//“分裂”分支
            int q = tr[p][x];
            if (len[q] == len[p] + 1) fail[u] = q;
            else {
                int cq = ++tot;
                fail[cq] = fail[q]; len[cq] = len[p] + 1;
                fail[u] = fail[q] = cq;
                memcpy(tr[cq], tr[q], sizeof(tr[cq]));
                for (; p && tr[p][x] == q; p = fail[p]) tr[p][x] = cq;
            }
        }
        //记录：集合下标 ax 对应终止状态 u
        pi[ax] = u; val[u] = ax;//标记状态 u 是该集合的终止
    }
    void upd(int &k, int l, int r, int x) {//主席树点更新
        int tk = ++tot2; ls[tk] = ls[k]; rs[tk] = rs[k]; k = tk;
        if (l == r) { s[k] = 1; return; }
        if (x <= mid) upd(ls[k], l, mid, x);
        else upd(rs[k], mid+1, r, x);
        s[k] = s[ls[k]] + s[rs[k]];
    }
    int merge(int x, int y) {//主席树合并（线段树合并）
        if (!x || !y) return x + y;
        int k = ++tot2;
        ls[k] = merge(ls[x], ls[y]); rs[k] = merge(rs[x], rs[y]);
        s[k] = s[ls[k]] + s[rs[k]];
        return k;
    }
    int query(int k, int l, int r, int L, int R) {//主席树区间求和
        if (!k || L > R) return 0;
        if (L <= l && r <= R) return s[k];
        int tp = 0;
        if (L <= mid) tp += query(ls[k], l, mid, L, R);
        if (mid < R) tp += query(rs[k], mid+1, r, L, R);
        return tp;
    }
    void dfs(int x) {//SAM fail 树的后序遍历 + 主席树合并
        int l = vf[x].size(), y;
        rep(i,0,l-1) {
            y = vf[x][i];
            dfs(y);
            rt[x] = merge(rt[x], rt[y]);
        }
        if (val[x]) upd(rt[x], 1, n, inl[val[x]]);
    }
    void build() {//建 fail 树并 DFS
        rep(i,1,tot) vf[fail[i]].push_back(i);
        dfs(1);
    }
} sa;

vector<int> v[N], e[N];
void add(int x, int y, int z) { v[x].push_back(y); e[x].push_back(z); }

int pre[N], sz[N], dep[N], a[N], son[N];
void dfs1(int x, int _fa) {
    pre[x] = _fa; sz[x] = 1; dep[x] = dep[_fa] + 1;
    int l = v[x].size(), y, z;
    rep(i,0,l-1) {
        y = v[x][i]; z = e[x][i];
        if (y == _fa) continue;
        a[y] = z; sa.ins(y, pi[x], z);
        dfs1(y, x);
        sz[x] += sz[y];
        if (sz[son[x]] < sz[y]) son[x] = y;
    }
}

int tot1, inr[N], top[N];
void dfs2(int x) {
    if (son[x]) {
        inl[son[x]] = ++tot1;
        inr[tot1] = son[x]; top[son[x]] = top[x];
        dfs2(son[x]);
    }
    int l = v[x].size(), y;
    rep(i,0,l-1) {
        y = v[x][i];
        if (y == pre[x] || y == son[x]) continue;
        inl[y] = ++tot1;
        inr[tot1] = y; top[y] = y;
        dfs2(y);
    }
}
int lca(int x, int y) {
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (dep[fx] < dep[fy]) swap(x, y), swap(fx, fy);
        x = pre[fx]; fx = top[x];
    }
    return dep[x] < dep[y] ? x : y;
}
int askd(int x, int z, int d) {//向上取"第 d 个祖先"
    if (dep[x] - dep[z] + 1 <= d) return -1;
    int fx = top[x];
    while (fx != top[z]) {
        if (dep[fx] <= d + dep[z]) break;
        x = pre[fx]; fx = top[x];
    }
    return inr[inl[fx] + (d-dep[fx]+dep[z])];
}
int ask(int x, int z, int p) {
    if (z == -1) return 0;
    int fx = top[x], ans = 0;
    while (fx != top[z]) {
        ans += sa.query(p,1,n,inl[fx],inl[x]);
        x = pre[fx]; fx = top[x];
    }
    ans += sa.query(p,1,n,inl[z],inl[x]);
    return ans;
}

int nxt[L];
int main() {
    fast;
    cin >> n;
    int x, y; string z, tp, tp1, tp2;
    rep(i,1,n-1) {
        cin >> x >> y >> z;
        add(x, y, z[0]-'a'); add(y, x, z[0]-'a');
    }
    sa.prep(); dfs1(1, 0);
    inl[1] = inr[1] = top[1] = tot1 = 1;
    dfs2(1); sa.build();
    int q; cin >> q;
    while (q--) {
        cin >> x >> y >> z;
        int ans = 0, l1 = z.length(), c = lca(x, y);
        int fx = askd(x, c, l1), fy = askd(y, c, l1);
        int px = 1, py = 1;
        per(i,l1-1,0) px = sa.tr[px][z[i]-'a'];//从 z 的末尾往前走（反向模式串）→ px
        rep(i,0,l1-1) py = sa.tr[py][z[i]-'a'];//从 z 开头正走 → py
        ans = ask(x, fx, sa.rt[px]) + ask(y, fy, sa.rt[py]);
        x = fx == -1 ? x : pre[fx]; y = fy == -1 ? y : pre[fy];
        tp1 = "", tp2 = "";
        for (; x != c; x = pre[x]) tp1 += (char)(a[x]+'a');//x→c 的自下而上字符
        for (; y != c; y = pre[y]) tp2 += (char)(a[y]+'a');
        int l2 = tp2.length();
        rep(i,1,l2/2) swap(tp2[i-1], tp2[l2-i]);//tp2 反转，得到 c→y 的自上而下
        tp = tp1 + tp2;//拼接成 c 两侧 + 跨越 c 的整段
        int tl = tp.length(); tp = " " + tp; z = " " + z;
        int j = 0;
        rep(i,2,l1) {//KMP 前缀函数：对模式串 z 求 next
            while (j && z[j+1] != z[i]) j = nxt[j];
            if (z[j+1] == z[i]) j++;
            nxt[i] = j;
        }
        j = 0;
        rep(i,1,tl) {//在文本 tp 上跑 KMP 匹配模式串 z
            while (j && z[j+1] != tp[i]) j = nxt[j];
            if (z[j+1] == tp[i]) j++;
            if (j == l1) { ans++; j = nxt[j]; }
        }
        cout << ans << '\n';
    }
    return 0;
}