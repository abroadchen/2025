//
// Created by Psy.C on 2026/9/25.
//
/**
给 pair<int,int> 重载 +。
first 分量做乘法取模（视为"权值乘积"），second 分量做普通相加（视为"计数/次数"）。
含义：这个 pair 代表 (某路径/集合的权值乘积 模 mod, 里面对应元素的个数)。合并两个集合=权值相乘 + 个数相加。
这是后面树状数组 query 里累积的关键语义
邻接表存边：to 目标点、nxt 下一条边、w 边权、c 边颜色（0/1 标记）。
N<<1：无向边存两次，所以容量开 2 倍
描述点分治中从重心 anc 出发的某条链的信息：
A = (#红色边) − 2·(#蓝色边) （这是 s1 这类）
B = 2·(#蓝边) − (#红边) （待会儿 A 与 B 搭配做偏序）
C = (#蓝边) − 2·(#红边)
D = 2·(#红边) − (#蓝边)
E = anc：这条链所属的重心/子分支编号（用于分治后去重）
val = 这条链上所有边权的乘积（模 mod）
具体红蓝定义取决于该题：e[i].c 决定这条边算 red(ca) 还是 blue(cb)。后面 dfs 里构造这些值
查询/修改点结构（CDQ 处理的元素）：
x = 一条链的 E（anc，作为第一维，用于按分支分组排序）。
y、z = 第 2、3 维（来自 node 的 A/B/C/D，搭配成偏序比较）。
val = 链的权值乘积。
type：1=修改(M), 0=查询(Q)
cmp：全局排序。（1）先按 x；同 x 时 type 小的（修改）在前；仍相同按 y、再 z。
cmp2：CDQ 内部归并排序用，只按 (y, z) 排序
树状数组，元素是 ii（权值乘积, 个数）。
加偏移 2*n：因为 z（第三维）可能是负数（来自 A/B/C/D 的正负偏差），统一加偏移转成非负下标。
init()：把每个位置初始为 {1, 0}（权值乘积 1、个数 0，即中性元素）。
modify(x, v)：在位置 x 插入一个权值 v 的元素（叠加一位：个数 +1、权值乘上 v）。
clear(x)：把位置 x 清空回 {1,0}（回滚，用于点分治每层结束清理）。
query(x)：查询前缀 [0..x] 的累积 (总权值乘积, 总个数)。
lower_bound 区间查询（前缀）返回组合结果
快速幂实现 xn mod mod；inv 用费马小定理求模逆元（mod 是素数）。
用于：树上两条链合并时，要把 query 得到的权值乘积乘进 Ans；与 val 的关系需要乘方/取逆。这里主要用 ksm(q[i].val, z.second) 求 val 的（个数次）幂
add：前向星加边（无向边调两次）。
chkmax：把 x 更新为 max(x,y)
calc(u, fa)：DFS 计算以 u 为根的子树大小 su，并求"去掉 u 后剩下的最大连通块大小" mx。
若 mx <= sz/2，说明 u 是当前分治块的重心，记录到全局 C
返回子树大小
计算整个分治块大小 sz，再跑一次 calc 得到重心 C 并返回
从重心某子树的根出发 DFS，收集 从重心到各点的链 的信息存入 a。
参数：
A,B,C,D：四种带符号的"红蓝计数组合"（沿用上面 node 定义：A=#红−2·#蓝 等）。每走一条边，根据该边颜色 e[i].c（ca=红?1:0, cb=另一色）更新这四个累积值。
mul：整条链的边权乘积（模 mod），过一条边乘 e[i].w。
anc：记录这条链是从哪个子分支（重心下方直接孩子，即第一层）发出去的，用于跨分支计数/去重。
每到一个节点，把这整条链打包成一个 node 塞进 a
经典 CDQ 分治：统计"修改(i) 的第三维 ≤ 查询(j) 的第三维、且 y 有序"的配对贡献。
分治到区间、左右各自按 cmp2（y 排序），双指针：左半的修改按 y 顺序加入树状数组（第三维 z 处插入 val），右半的查询统计 ≤ z 的前缀累积。
对每个查询：query(z) 得到前缀 (权值积, 个数)，然后 Ans *= val^个数 * 权值积。
即：把满足偏序条件的前缀里所有链的权值相乘，并乘上"查询链权值 的（个数）次幂"，计入总答案。
结束清空本轮树状数组（clear）以复用
对当前点分治层的所有链 a：
每个 node 产生两个 CDQ 元素：
修改 {E, A, C, val, 1}
查询 {E, B, D, val, 0}
用 cmp 按 (E 先，type 次，y，z) 全局排序。
跑 CDQ dfs2 统计，返回 Ans。
语义：把"第 1 维按 E（分支）分组"，跨分支的链做三维 (A vs B, C vs D) 偏序统计，累乘得到这部分方案贡献
点分治主流程：
从重心 u 的每个未访问子分支做 dfs，收集"以 u 为端点的所有链"（A/B/C/D 从子分支出发带初始红蓝贡献，mul = e[i].w，anc = v）。
加入一条"零链" node(0,...,val=1)（代表重心 u 本身到重心，空路径，权值积 1）——用于统计含重心单点或只含一侧链的情形。
标记 vis[u]=1（删除重心）。
ans = ans * run()：用 CDQ 统计穿过当前重心 u 的、满足条件的路径/结构组合，乘进总答案。
清空 a。
对重心的每个未访问子分支，递归点分治 solve(find(v,u))
读入 n；t.init() 初始化树状数组。
读入 n−1 条无向边（u,v,w,c），建邻接表。
从节点 1 开始找重心并启动点分治 solve。
输出总答案 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+10, mod = 1e9+7;

ii operator+(const ii& f, const ii& g) {
    return {1ll*f.first*g.first%mod, f.second+g.second};
}

struct edge { int to, nxt, w, c; } e[N<<1];
struct node {
    int A, B, C, D, E, val;
    node(int A=0, int B=0, int C=0, int D=0, int E=0, int val=0) : A(A), B(B), C(C), D(D), E(E), val(val) {}
};
struct Q {
    int x, y, z, val, type;
    Q(int x=0, int y=0, int z=0, int val=0, int type=0) : x(x), y(y), z(z), val(val), type(type) {}
} q[N<<1];
bool cmp(Q s, Q t) {
    if (s.x == t.x) {
        if (s.type == t.type) return s.y < t.y || (s.y == t.y && s.z < t.z);
        return s.type < t.type;
    }
    return s.x < t.x;
}
bool cmp2(Q s, Q t) { return s.y < t.y || (s.y == t.y && s.z < t.z); }

int n;
struct BIT {
    ii c[N<<2];
    int low_bit(int x) { return x & -x; }
    void init() {
        for (int i = 0; i <= 4*n; ++i) c[i] = {1, 0};
    }
    void modify(int x, int v) {
        x += 2*n;
        for (; x <= 4*n; x += low_bit(x))
            c[x] = c[x] + make_pair(v, 1);
    }
    void clear(int x) {
        x += 2*n;
        for (; x <= 4*n; x += low_bit(x)) c[x] = {1, 0};
    }
    ii query(int x) {
        ii res = {1, 0}; x += 2*n;
        for (; x; x -= low_bit(x)) res = res + c[x];
        return res;
    }
} t;

int ksm(int x, int k) {
    int res = 1;
    for (; k; k >>= 1) {
        if (k&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
    }
    return res;
}
int inv(int x) { return ksm(x, mod-2); }

int tot, head[N];
void add(int u, int v, int w, int c) {
    e[++tot] = {.to = v, .nxt = head[u], .w = w, .c = c}, head[u] = tot;
}
void chkmax(int& x, int y) { x = x > y ? x : y; }

int vis[N], sz, C;
int calc(int u, int fa) {
    int su = 1, mx = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (vis[v] || v == fa) continue;
        int z = calc(v, u);
        chkmax(mx, z);
        su += z;
    }
    chkmax(mx, sz-su);
    if (mx <= sz/2) C = u;
    return su;
}
int find(int u, int fa) {
    sz = calc(u, fa); calc(u, fa);
    return C;
}
vector<node> a;
void dfs(int u, int fa, int A, int B, int C, int D, int mul, int anc) {
    a.emplace_back(A, B, C, D, anc, mul);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (vis[v] || v == fa) continue;
        int ca = 0, cb = 0;
        e[i].c ? ca++ : cb++;
        dfs(v, u, A+ca-2*cb, B+2*cb-ca, C+cb-2*ca, D+2*ca-cb, 1ll*mul*e[i].w%mod, anc);
    }
}

ll Ans;
void dfs2(int l, int r) {
    if (l >= r) return;
    int mid = (l+r)>>1;
    dfs2(l, mid); dfs2(mid+1, r);
    sort(q+l, q+1+mid, cmp2);
    sort(q+mid+1, q+1+r, cmp2);
    int j = l;
    for (int i = mid+1; i <= r; ++i) {
        while (j <= mid && q[j].y <= q[i].y) {
            if (q[j].type) t.modify(q[j].z, q[j].val);
            j++;
        }
        if (!q[i].type) {
            ii z = t.query(q[i].z);
            Ans = 1ll*Ans*ksm(q[i].val, z.second)%mod*z.first%mod;
        }
    }
    for (int i = l; i < j; ++i) t.clear(q[i].z);
}

ll run() {
    tot = 0; Ans = 1;
    for (auto v : a) {
        q[++tot] = {v.E, v.A, v.C, v.val, 1};
        q[++tot] = {v.E, v.B, v.D, v.val, 0};
    }
    sort(q+1, q+1+tot, cmp);
    dfs2(1, tot);
    return Ans;
}

ll ans(1);
void solve(int u) {
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (vis[v]) continue;
        int ca = 0, cb = 0;
        e[i].c ? ca++ : cb++;
        dfs(v, u, ca-2*cb, 2*cb-ca, cb-2*ca, 2*ca-cb, e[i].w, v);
    }
    a.emplace_back(0, 0, 0, 0, 0, 1);
    vis[u] = 1;
    ans = ans*run()%mod; a.clear();
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (vis[v]) continue;
        solve(find(v, u));
    }
}


int main() {
    fast;
    cin >> n; t.init();
    for (int i = 1, u, v, w, c; i <= n-1; ++i) {
        cin >> u >> v >> w >> c;
        add(u, v, w, c); add(v, u, w, c);
    }
    solve(find(1, 0));
    cout << ans;
    return 0;
}