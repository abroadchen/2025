//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
数组大小：N 为点数上限，M 为边数上限（无向边×2）。
head[]：邻接表头指针。
tot：边计数。
nxt[] / to[]：邻接表的下一条边、目标点。
无向加边，head[x] 链式前向星插入 y
v[]：BIT 数组，下标范围到 n+m（因为时间戳最多到 n+m）。
Add(x,k)：在 x 位置加 k，向上传递到 n+m。
ask(x)：前缀和查询（1..x）。
用途：用于维护"每个时间戳对应的子树大小"的前缀和，从而支持"某时间戳区间内有多少个节点"的查询（在 qry 里用来算排名）
val[x]：节点 x 的LCT 值（时间戳 num）‍，用于 BIT 查询。
sz[x]：LCT 的 splay 子树大小。
f[x]：LCT 的父指针（或 splay 父）。
s[x][0/1]：LCT 左右儿子。
cnt：全局计时器（时间戳计数），用于每次换根时新增时间戳。
作用：对树做一次 DFS，以某个固定根为起点（main 里从 dfs(n) 开始，即以 n 为初始根），完成：

val[x]=x、sz[x]=1 初始化。
遍历子树，递归设置父指针 f。
维护重儿子：val[to]>val[x] 时，更新 val[x]、记录 splay 右儿子 s[x][1]（这里把 val 最大的子树作为 splay 的右儿子，相当于建立一个以 val 排序的 splay），并累加 sz。
每个节点结束后 Add(val[x],1)：往 BIT 里插入"该时间戳有 1 个子树节点"。
本质是在 DFS 序上按 val 建 LCT 的初始链，val 相当于 DFS 进入的顺序编号。
判断 rt 是否为splay 的根（不是任何父亲的左右儿子 → 是 LCT 的"虚链顶端"）。
返回 rt 是父节点的左儿子(0)还是右儿子(1)。
重新计算 splay 子树大小
下推懒标记：

若该点有翻转标记 rev：交换左右儿子，把翻转标记下传给两个儿子（异或取反），并清除当前标记。
把 val 下推：将父节点的 val 赋值给左右儿子——这是本题的关键：整个 splay 内的所有节点共享同一个 val（时间戳）‍，用于"区间打上同一个新时间戳"
标准的splay 旋转：

fa=父，anc=祖父，k=rt 在 fa 的位置。
若 fa 不是 splay 根，则先把 rt 接到 anc 对应儿子位。
交换父子关系，转移中间子树，维护父亲指针与大小
把一个点旋转到所在 splay 的根：

先把从根到 rt 的整条路径压栈（st），自上而下依次 push_down，确保所有懒标记在旋转前下推。
再用双旋（zig-zig/zig-zag）处理，直到 rt 成为根
LCT 的核心 access：把 rt 到所在实链根的路径变成一条实链。

循环从 rt 沿虚父（f[rt]）向上。
splay(rt) 让 rt 成为其 splay 根。
断开右儿子（s[rt][1] = 0）：去掉原来 rt 下方的实链，使 rt 成为所在链顶。
BIT 维护：把原来右儿子（旧链）的 sz 从 BIT 里减去（Add(val[rt], -sz[rt])），再把整个链的 sz 加到新时间戳 cnt（Add(cnt, sz[rt])）——这一步把"整条链"对应到新的时间戳区间。
再接上新的右儿子 x，更新 sz。
这样 BIT 里的每个时间戳对应一条"实链"，其区间内包含该链的节点数。
把某个点设为根（本题的 'u' 操作）‍：

cnt++：开一个新时间戳。
access(rt)：把 rt 到原根的路径变成实链。
splay(rt)：rt 成为 splay 根。
rev[rt] ^= 1：打翻转标记（把链翻转，让 rt 变成新链首 → 相当于换根）。
val[rt] = cnt：给根打上新的时间戳（这个 splay 整条链会在 push_down 时共享这个 val）。
结合 push_down 中"整个 splay 共享 val"，换根后整条路径都归属新时间戳 cnt，因此 BIT 中 cnt 区间覆盖了这条链，从而可以查询排名。
查询节点 rt 在当前根下的"深度排名（向上数第几层）"：

splay(rt)：把 rt 转到其 splay 根，push_down 已确保 val[rt] 是最新时间戳。
ask(val[rt])：BIT 中 val[rt] 时间戳的前缀和 → 得到"在该时间戳区间（即 rt 所在的整条链）内，包括从链首到 rt 的所有节点有多少个"。
- sz[s[rt][0]]：减去 rt 上方（左子树，即深度更小的部分）的节点数。结果就是 rt 下方（深度更大一侧）的节点个数，即"rt 到链底的距离 / 排名"。
输出的是"rt 在链中的深度排位"（越大越深/越靠后），题目用它比较两个点谁更深。
读入 n 个点、m 个操作，初始化 cnt=n。
读入 n-1 条边，建无向图。
dfs(n)：以 n 为初始根，跑上面的 DFS 建初始 LCT 链并初始化 BIT。
循环 m 个操作：
u x（ch[0]=='u'）：把点 x 设为根 → reverse(x)。
w x（ch[0]=='w'）：查询点 x 的排名 → qry(x) 并输出。
c x y（第三个分支）：比较 x、y 的排名，输出排名更小（更靠近根，即更浅）的那个点。用 qry(x)<qry(y)?x:y
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+10, M = 4e5+10;

int head[N], tot, nxt[M], to[M];
void add(int x, int y) { to[++tot] = y; nxt[tot] = head[x]; head[x] = tot; }

int n, m, v[M];
void Add(int x, int k) { for (int i = x; i <= n+m; i += i&-i) v[i] += k; }
int ask(int x) {
    int res = 0;
    for (int i = x; i; i -= i&-i) res += v[i];
    return res;
}

int val[N], sz[N], f[N], s[N][2];
void dfs(int x) {
    val[x] = x; sz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        if (to[i] != f[x]) {
            f[to[i]] = x; dfs(to[i]);
            if (val[to[i]] > val[x]) {
                val[x] = val[to[i]]; s[x][1] = to[i];
                sz[x] = sz[to[i]] + 1;
            }
        }
    }
    Add(val[x],1);
}
inline bool isrt(int rt) { return rt != s[f[rt]][0] && rt != s[f[rt]][1]; }
inline bool get(int rt) { return rt == s[f[rt]][1]; }
void push_up(int rt) { sz[rt] = sz[s[rt][0]] + sz[s[rt][1]] + 1; }

int rev[N];
void push_down(int rt) {
    if (rev[rt]) {
        swap(s[rt][0], s[rt][1]);
        rev[s[rt][0]] ^= 1; rev[s[rt][1]] ^= 1; rev[rt] = 0;
    }
    if (s[rt][0]) val[s[rt][0]] = val[rt];
    if (s[rt][1]) val[s[rt][1]] = val[rt];
}
void rotate(int rt) {
    int fa = f[rt], anc = f[fa], k = get(rt);
    if (!isrt(fa)) s[anc][get(fa)] = rt;
    s[fa][k] = s[rt][k^1]; f[s[rt][k^1]] = fa; s[rt][k^1] = fa;
    f[fa] = rt; f[rt] = anc; push_up(fa); push_up(rt);
}

int st[N];
void splay(int rt) {
    int top = 0; st[++top] = rt;
    for (int i = rt; !isrt(i); i = f[i]) st[++top] = f[i];
    for (int i = top; i >= 1; i--) push_down(st[i]);
    for (int fa; !isrt(rt); rotate(rt))
        if (!isrt(fa=f[rt])) rotate(get(fa)==get(rt)?fa:rt);
}

int cnt;
void access(int rt) {
    for (int x = 0; rt; x = rt, rt = f[rt]) {
        splay(rt); s[rt][1] = 0; push_up(rt);
        Add(val[rt], -sz[rt]); Add(cnt,sz[rt]);
        s[rt][1] = x; push_up(rt);
    }
}
void reverse(int rt) { cnt++; access(rt); splay(rt); rev[rt] ^= 1; val[rt] = cnt; }
int qry(int rt) {
    splay(rt);
    return ask(val[rt])-sz[s[rt][0]];
}

char ch[10];
int main() {
    fast;
    cin >> n >> m; cnt = n;
    for (int i = 1, x, y; i < n; i++) { cin >> x >> y; add(x, y); add(y, x); }
    dfs(n);
    for (int i = 1, x, y; i <= m; i++) {
        cin >> ch;
        if (ch[0] == 'u') { cin >> x; reverse(x); }
        else if (ch[0] == 'w') { cin >> x; cout << qry(x) << '\n'; }
        else { cin >> x >> y; cout << (qry(x)<qry(y)?x:y) << '\n'; }
    }
    return 0;
}