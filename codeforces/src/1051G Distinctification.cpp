//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
N：点数上限（4e5）。
M：线段树节点总数上限 = N*30，因为权值线段树每个元素插入会新建约 log(值域) 个节点，值域为 n（1..n），故每个点约 30 层节点
fa 并查集：代表"连续的块"，每个块是一个集合，集合代表（find 后）记录该块信息。
ans：实时答案。
rt[i]：位置 i 所代表块的值域线段树根。
bl[i]：块 i 的标识 id（通常 = 这个块的"左端点"，即块内最小的位置号）
ch[0][x] / ch[1][x]：节点 x 的左 / 右孩子下标。
t[x].siz：这个子树（值域区间）里已插入的元素个数。
t[x].sum：这个子树里已插入元素的值之和
tot：开点总数。
每个节点记录：该值域子区间内元素个数 siz 与值总和 sum
自底向上合并左右孩子的 siz、sum。
动态开点：走进值为 p 的叶子（值域 [1,n]），在该位置把个数置 1、和置 p。
沿路 push_up
递归合并两棵值域线段树 a、b（合并到新树 x）。
若一方为空，直接返回另一方。
叶子合并时若都非空说明值重复（同值出现两次），直接返回新点即可。
关键：在每层合并时，用"跨左右孩子的顺序对"来更新全局答案 ans。
为何在 merge 里维护 ans？想象值域 [1,n] 是一个排序后的序列。合并两个块时，需要统计"跨块且顺序关系"贡献的权值变化。代码在每层即将合并左右孩子时，先减去 a、b 各自的"左×右"贡献（跨孩子逆序贡献），合并后加上新的"左×右"贡献，从而增量维护 ans。这是一种离线/增量计算"值域内逆序/顺序对"的通用技巧，能每次合并 O(logn) 更新答案。
将块 b 并入块 a：
并查集：fa[b]=a（a 做新的代表）。
先把 ans 中 a、b 两个旧块的贡献 sum×id 减去。
线段树合并 a、b 的值域树，新的根仍挂在 rt[a]。合并过程中 ans 会被 merge 内部加减调整。
再加上新块的贡献 sm(rt[a])*a。
bl[a] = bl[b]：把块的标识 id 更新为 b 的标识
y 决定新块到底放在哪里、标识为何：
若 x 位置还没有任何块（rt[x]==0 即该位置无边），则新块取自 y=x。
若 x 已经有块（说明 x 在某已有区间内），则新块的 id 取"该块标识+1"。
ans += 1ll*(y-x)*v：为新块加入一个"初始贡献增量"，数值为 (y-x)*v（推测是表示把元素放到新块位置带来的权值变化，(y-x) 可能是"块 id 与插入位置的距离"类的调整量）
把元素 v 插入到新块 y 的值域线段树
插入后检查 y 左右两侧是否存在块，若存在则把相邻的块合并（link 会调用 find 找到各自代表、合并线段树、更新 ans）。
因为连合并两次可能连锁，但并查集保证每个"代表"只代表一个连续块，代码顺序处理左、右即可
每次操作后输出当前的 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define mid ((l+r)>>1)
#define ll long long
using namespace std;

constexpr int N = 4e5+5, M = N*30;

int fa[N];
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

ll ans;
int rt[N], n, bl[N];
struct sgt {
#define L(x) ch[0][x]
#define R(x) ch[1][x]
#define ls L(x)
#define rs R(x)
#define sz(x) t[x].siz
#define sm(x) t[x].sum
    struct tree { int siz; ll sum; } t[M];
    int ch[2][M], tot;
    void push_up(int x) { sm(x) = sm(ls) + sm(rs), sz(x) = sz(ls) + sz(rs); }
    void upd(int &x, int l, int r, int p) {
        if (!x) x = ++tot;
        if (l == r) { sz(x) = 1, sm(x) = p; return; }
        p <= mid ? upd(ls,l,mid,p) : upd(rs,mid+1,r,p);
        push_up(x);
    }
    int merge(int a, int b, int l, int r) {
        if (!a || !b) return a + b;
        int x = ++tot;
        if (l == r) return x;
        ans -= sm(L(a))*sz(R(a)) + sm(L(b))*sz(R(b));
        ls = merge(L(a), L(b), l, mid), rs = merge(R(a), R(b), mid+1, r);
        ans += sm(ls)*sz(rs);
        push_up(x);
        return x;
    }
    void link(int a, int b) {
        a = find(a), b = find(b), fa[b] = a;
        ans -= sm(rt[a])*a + sm(rt[b])*b;
        rt[a] = merge(rt[a], rt[b], 1, n);
        ans += sm(rt[a])*a, bl[a] = bl[b];
    }
} T;

int main() {
    fast;
    rep(i,N-5) fa[i] = bl[i] = i;
    cin >> n;
    rep(i,n) {
        int x, y, v; cin >> x >> v;
        y = rt[x] ? bl[find(x)]+1 : x;//决定新块 id
        ans += 1ll*(y-x)*v;
        T.upd(rt[y], 1, n, v);//在值域线段树插入值 v
        if (rt[y-1]) T.link(y-1, y);//若左侧有块则合并
        if (rt[y+1]) T.link(y, y+1);//若右侧有块则合并
        cout << ans << '\n';
    }
    return 0;
}