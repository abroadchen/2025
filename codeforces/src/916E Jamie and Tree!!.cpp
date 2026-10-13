//
// Created by Psy.C on 2026/10/13.
//
/**
字段	含义
fa, ch[0/1], rev	LCT 标准字段：父指针、左右儿子、懒标记（翻转）
sz	该 splay 中"整棵 access 子树"大小（含虚子树）
szc	该 splay 中实儿子的节点数（含自己）= splay 子树真实节点数
szt	splay 中"虚儿子贡献"的节点数（不含自己）
w	节点本身的点权
sl	该点"虚儿子"的权值和（不含实儿子）
sum	该 splay 子树（含虚）的总权值和
dlt	给"虚子树"打的加法标记（累计）
dtag / stag	懒标记：虚子树加 / 整棵 splay 子树加

sz：实儿子 + 自己(1) + 虚儿子数(szl)，代表整棵 access 子树大小。
szc：splay 内真实节点数（实儿子 + 1）。
szt：实儿子贡献 + 自己的虚儿子数 szl。
sum：实儿子的和 + 自己的权 w + 虚儿子贡献 sl + 虚儿子上累计的加标记 szl*dlt（因为有效权值 = 自身权 + 父级虚加标记）
adds：给所有实儿子节点加权，标记 stag，累加到 sum（乘 szc）。
addd：只给虚儿子加权（自己不加），dlt 累计，累加乘以 szt（虚儿子处节点数）。
push_down 依次下传 rev、stag、dtag 三个懒标记
标准 LCT splay 旋转与伸展，get/nr 判断左右儿子/是否非根。splay 先压栈下传所有懒标记再旋转
ins/del 管理节点 x 的虚儿子集合 y：加入/移除时更新 szl（虚儿子节点数）和 sl（虚儿子权值和）。关键技巧：在把 y 变成虚儿子/实儿子时，用 adds/addd 把 x 积压的 dlt（虚加标记）"交接"给 y，保证正确性
access 把 x 到根路径变成一条实链，并把途中的虚实切换用 ins/del 处理好。返回的 y 是 access 全程最后一次的节点（用于求 LCA）
build = makeroot：把 x 变为根。
split(x,y)：抽出 x→y 的偏爱路径到 y 一棵 splay 上，供查询/修改整条路径
连接 x、y（建树时使用）——先把两者都变为根，再把 x 挂到 y 的右实儿子下
对"以 x 为根的子树"整体加 v：split(rt, x) 后 x 的 splay 内就是 x 的整棵子树，用 dlt（虚）与 w（本身）、并把虚儿子数+1 的贡献计入 sum
查询子树和 = 自身权 + 虚儿子和 + 虚儿子上累计标记的贡献
换根：把动态根 rt 改为 v。
路径加：将 u 到 v 路径上所有点加 x——先 makeroot(rt)，再分别 access(u)、access(v) 求出 LCA，再对以 LCA 为根的子树整体加 x（因为该子树恰好覆盖 u→v 路径，且沿根方向唯一）。
子树查询：查询以 v 为根的子树的点权和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;

int st[N], tp;
struct lct {
    struct spy {
        int fa, ch[2], rev, sz, szl, szc, szt;
        ll w, sl, sum, dlt, dtag, stag;
    } tr[N];
#define ls(x) (tr[x].ch[0])
#define rs(x) (tr[x].ch[1])
#define Fa(x) (tr[x].fa)
    void push_up(int x) {
        //整棵 access 子树大小 = 左实子 + 右实子 + 虚儿子 + 自己(1)
        tr[x].sz = tr[ls(x)].sz + tr[rs(x)].sz + tr[x].szl + 1;
        //splay 真实节点数 = 左右实子 + 自己
        tr[x].szc = tr[ls(x)].szc + tr[rs(x)].szc + 1;
        //虚贡献节点数 = 左右实子的虚贡献 + 自己的虚儿子数
        tr[x].szt = tr[ls(x)].szt + tr[rs(x)].szt + tr[x].szl;
        //总权值和 = 左右实子和 + 自身权 + 虚子和 + 虚子上累计的加标记贡献
        tr[x].sum = tr[ls(x)].sum + tr[rs(x)].sum + tr[x].w + tr[x].sl + tr[x].szl*tr[x].dlt;
    }
    void reverse(int x) {
        if (!x) return;//空节点不处理
        swap(ls(x), rs(x));
        tr[x].rev ^= 1;//记录翻转标记
    }
    void adds(int x, ll v) {
        if (!x) return;
        tr[x].stag += v;//记录加标记（整棵子树）
        tr[x].w += v;//当前节点自身权 +v
        tr[x].sum += v*tr[x].szc;//子树和 累计 +v * 真实节点数
    }
    void addd(int x, ll v) {
        if (!x) return;
        tr[x].dtag += v;//虚加懒标记
        tr[x].dlt += v;//虚加累计值
        tr[x].sum += v*tr[x].szt;//子树和 累计 +v * 虚贡献节点数
    }
    void push_down(int x) {
        //下传翻转
        if (tr[x].rev) { reverse(ls(x)); reverse(rs(x)); tr[x].rev = 0; }
        //下传整棵加
        if (tr[x].stag) { adds(ls(x), tr[x].stag); adds(rs(x), tr[x].stag); tr[x].stag = 0; }
        //下传虚加
        if (tr[x].dtag) { addd(ls(x), tr[x].dtag); addd(rs(x), tr[x].dtag); tr[x].dtag = 0; }
    }
    int get(int x) { return rs(Fa(x)) == x; }//若 x 是父的右儿子则返回 1，否则 0
    int nr(int x) { return rs(Fa(x)) == x || ls(Fa(x)) == x; }//x 是否不是所在 splay 的根（即还有父节点在 splay 内）
    void rotate(int x) {
        //f=父, gf=祖父, d=x 相对 f 的方向, dd=f 相对 gf 的方向
        int f = Fa(x), gf = Fa(f), d = get(x), dd = get(f);
        if (nr(f)) tr[gf].ch[dd] = x;//若 f 不是整棵 splay 根，则用 x 顶替 f 的位置
        tr[f].ch[d] = tr[x].ch[d^1]; Fa(tr[x].ch[d^1]) = f;//x 的"另一侧"儿子过继给 f
        tr[x].ch[d^1] = f; Fa(f) = x; Fa(x) = gf;//f 变成 x 的儿子，重接父指针
        push_up(f); push_up(x);//更新被改动的两个节点
    }
    void splay(int x) {
        int y = st[tp=1] = x;//栈顶先放 x 自己
        while (nr(y)) st[++tp] = y = Fa(y);//沿父一路向上把路径节点入栈
        while (tp) push_down(st[tp--]);//从栈顶往下逐个下传懒标记（先处理祖先）
        for (; nr(x); rotate(x))//双旋 / 单旋，一直转到根
            if (nr(Fa(x))) rotate(get(x) == get(Fa(x)) ? Fa(x) : x);
        push_up(x);
    }
    void ins(int x, int y) {//把 y 作为 x 的虚儿子加入
        if (!y) return;
        adds(y, -tr[x].dlt); addd(y, -tr[x].dlt);//抵消传递的虚加标记
        tr[x].szl += tr[y].sz; tr[x].sl += tr[y].sum;
    }
    void del(int x, int y) {//从 x 的虚儿子中移除 y
        if (!y) return;
        tr[x].szl -= tr[y].sz; tr[x].sl -= tr[y].sum;
        adds(y, tr[x].dlt); addd(y, tr[x].dlt);//把累积的虚加标记传下去
    }
    int access(int x) {
        int y = 0;//y 记录"上一个右儿子"（新实儿子）
        while (x) {//一路向上到根
            splay(x);//先把 x 转到 splay 根
            ins(x, rs(x)); //原右儿子（实）变成虚儿子
            del(x, y);//把 y（上一个"新右儿子"）从虚儿子变成实儿子
            rs(x) = y; push_up(x);//接上 y，更新 x
            x = Fa(y=x);//上移到父（且 y 记录本轮 x）
        }
        return y;//返回最后 access 的根（用于求 LCA）
    }
    void build(int x) { access(x); splay(x); reverse(x); }//打通再翻转，使 x 成为树根
    void split(int x, int y) { build(x); access(y); splay(y); }//x 变根后 access(y)，y 成为路径 splay 根
    void link(int x, int y) {
        build(x); build(y);//两端都变根
        access(y);//打通 y
        Fa(x) = y; rs(y) = x;//x 挂到 y 的右实儿子
        push_up(y);//更新 y
    }
    void add(int rt, int x, ll v) {
        split(rt, x); //抽出 rt→x 路径，x 成为子树根
        tr[x].dlt += v; tr[x].w += v;//x 自身以及它的虚子树加 v
        tr[x].sum += (tr[x].szl + 1)*v;//子树和 增加 (虚儿子数+1)*v
    }
    ll ask(int rt, int x) {//抽出路径后
        return split(rt, x), tr[x].w+tr[x].sl+tr[x].szl*tr[x].dlt;//自身权 + 虚子和 + 虚子树累计标记贡献
    }
#undef ls
#undef rs
#undef Fa
} lct;


int n, q, rt(1);
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> lct.tr[i].w, lct.push_up(i);//单独节点先合并一次信息
    for (int i = 1, x, y; i < n; ++i) cin >> x >> y, lct.link(x, y);//连边建树
    for (int i = 1, op, u, v, x, lca; i <= q; ++i) {
        cin >> op;
        switch (op) {
            case 1://换根
                cin >> v; rt = v; break;//新根设为 v（仅改记录）
            case 2://路径加：把 u 到 v 路径上所有点 +x
                cin >> u >> v >> x; lct.build(rt);//先把树根变成 rt
                lca = (lct.access(u), lct.access(v)); lct.add(rt, lca, x);//对以 LCA 为根的子树的整棵子树加 x（该子树正好覆盖 u→v 路径）
                break;
            case 3://查询：v 的子树点权和
                cin >> v;
                cout << lct.ask(rt, v) << '\n';
        }
    }
    return 0;
}