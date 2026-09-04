//
// Created by Psy.C on 2026/9/4.
//
/**
mod = 1<<30：答案对大模数 2^30 取模（强制在线时用于压缩 lastans）。
P[]：排列。树相关 head/fa/dfn/top 用于树剖
dis[p]：1→p 的带权距离（路径边权和），后续 dist 公式的基础。
Edis[to]：to 连接到父节点的那条边的权。
计算 siz 并挑选重儿子 son[p]（子树最大的儿子），为树剖做准备
优先剖重儿子（沿用链头 topf），轻儿子各自作为新链头。dfn 给每个点一个连续编号，使得每条重链上的点在 dfn 序号上连续，这样"某个点到根路径"就能拆成
O
(
log
⁡
n
)
O(logn) 段连续区间，供线段树/主席树查询。fdfn[i] 是 dfn 序号的反查

用数组开了一大块内存（
37
×
10
6
37×10
6
 ）作为主席树的全部节点。tl/tr 左右孩子，tag 加法标记（区间加），val 维护"按 dfn 顺序排列的边权前缀和区间和"

这是可持久化区间加、区间求和线段树。Lim 记录"当前这棵组树插入前已有的节点数"，只复制新建路径上的节点（p <= Lim 表示 p 还是上一棵版本的旧节点，需要复制一份），实现持久化。
完全覆盖时：tag[p]++，并把整段都加上这段的边权前缀和 pre[r]-pre[l-1]（pre 是按 dfn 顺序排列的边权前缀和，见后）。
部分覆盖时递归子段，最后 val[p] 由两个孩子的 val 加上本节点 tag 对应的整段贡献

因为主席树不做下推（持久化不能随意改孩子），所以查询时把祖先的 tag 累加到 times 参数里带下去。叶子/空节点用 times * (边权前缀和段) 直接补全，完成带标记的区间求和

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5, mod = 1<<30;
int P[N], n, Q;
int head[N], fa[N], dfn[N], top[N];
struct Edge { int to, next, w; } edg[N<<1];
int cnt(1);
void add(int u,int v,int w) {
    edg[++cnt] = {.to = v, .next = head[u], .w = w}, head[u] = cnt;
}
int son[N], siz[N], fdfn[N], dfntot(0);
ll pre[N], sum[N], dis[N], Edis[N];
void dfs(int p,int pre) {
    fa[p] = pre, siz[p] = 1;
    for(int i = head[p];i;i = edg[i].next) {
        int to = edg[i].to;
        if(to == pre) continue;
        dis[to] = edg[i].w + dis[p];//到根带权和
        Edis[to] = edg[i].w;//该点到父边的边权
        dfs(to, p);
        siz[p] += siz[to];
        if(siz[son[p]] < siz[to]) son[p] = to;
    }
}

void dfs1(int p,int pre,int topf) {
    top[p] = topf, dfn[p] = ++ dfntot, fdfn[dfntot] = p;
    if(!son[p]) return ;
    dfs1(son[p], p, topf);//重儿子继承 top
    //轻儿子开新链
    for(int i = head[p];i;i = edg[i].next) {
        int to = edg[i].to;
        if(to == son[p] || to == pre) continue;
        dfs1(to, p, to);
    }
}

int tot(0), Lim;
const int maxT = 37e6;

int tl[maxT], tr[maxT], tag[maxT];

ll val[maxT];
#define ls tl[p]
#define rs tr[p]
#define mid ((l + r) >> 1)
void Insert(int &p,int l,int r,int L,int R) {
    if(p <= Lim) {//只有当前版本新分配的节点才复制
        ++tot;
        tl[tot] = tl[p], tr[tot] = tr[p], tag[tot] = tag[p], val[tot] = val[p];
        p = tot;
    }
    if(L <= l && r <= R) return ++ tag[p], val[p] += pre[r] - pre[l - 1], void();
    if(L <= mid) Insert(ls, l, mid, L, R);
    if(mid < R) Insert(rs, mid + 1, r, L, R);
    val[p] = val[ls] + val[rs] + (pre[r] - pre[l - 1]) * tag[p];
}
ll Ask(int p,int l,int r,int L,int R,int times) {
    if(!p) return times * (pre[min(R, r)] - pre[max(l - 1, L - 1)]);
    if(L <= l && r <= R) return times * (pre[r] - pre[l - 1]) + val[p];
    times += tag[p];
    long long res(0);
    if(L <= mid) res += Ask(ls, l, mid, L, R, times);
    if(mid < R) res += Ask(rs, mid + 1, r, L, R, times);
    return res;
}
#undef ls
#undef rs
#undef mid

int rt[N];

//把 v 到根路径的每段重链区间插入到版本 l
void Insert(int l,int v) {
    Lim = tot;
    while(v) {
        Insert(rt[l], 1, n, dfn[top[v]], dfn[v]);
        v = fa[top[v]];
    }
}

//查询 v 到根路径在版本 l 上的带权累和
ll Ask(int l,int v) {
    ll ans = sum[l] + dis[v] * l;
    while(v) {
        ans -= Ask(rt[l], 1, n, dfn[top[v]], dfn[v], 0) * 2;
        v = fa[top[v]];
    }
    return ans;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

int main() {
    fast;
    ll lastans(0);
    int i;
    rd(n, Q);
    for(i = 1; i <= n; ++ i) rd(P[i]);
    for(i = 1; i < n; ++ i) {
        int u, v, w;
        rd(u, v, w), add(u, v, w), add(v, u, w);
    }
    dfs(1, 0);
    dfs1(1, 0, 1);

    for(i = 1; i <= n; ++ i) pre[i] = pre[i - 1] + Edis[fdfn[i]];//dfn 序下的边权前缀和
    for(i = 1; i <= n; ++ i) sum[i] = sum[i - 1] + dis[P[i]];//P[1..i] 到根距离和
    for(i = 1; i <= n; ++ i) rt[i] = rt[i - 1], Insert(i, P[i]);//建立可持久化版本 rt[i]

    int Ts(0);

    while(Q --) {
        int opt, l, r, x;
        rd(opt);
        if(opt == 1) {
            rd(l, r, x);
            l = lastans ^ l; r = lastans ^ r; x = lastans ^ x;//强制在线
            lastans = Ask(r, x) - Ask(l - 1, x);
            printf("%lld\n", lastans);
            lastans %= mod;
        }
        else {
            rd(x);
            x = lastans ^ x;
            //交换排列中相邻两项 更新前缀和
            swap(P[x], P[x + 1]), sum[x] = sum[x - 1] + dis[P[x]];
            if(++Ts == 150000) {//定期重建整棵主席树（防内存爆炸）
                Ts = 0; tot = 0;//清空节点池
                for(i = 1; i <= n; ++ i) rt[i] = rt[i - 1], Insert(i, P[i]);//全量重建
            }
            else rt[x] = rt[x - 1], Insert(x, P[x]);//只更新受影响版本
        }
    }
    return 0;
}