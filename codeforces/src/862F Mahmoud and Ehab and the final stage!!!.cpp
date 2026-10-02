//
// Created by Psy.C on 2026/10/2.
//
/**
N = 2^17：线段树的底层大小（数组大小）。
M = 1e5：字符串/位置最大数量。
K = 50：阈值分块的分界值——LCP（最长公共前缀）长度 > 50 的单独处理，≤50 的用多重线段树处理
node 有 4 个字段：
l：从左边起连续某种元素（长度 v 满足 ≥i 的连续段）的长度；
r：从右边起连续段长度；
u：整段是否"全部为 u 元素"（全通标记，1/0 或乘积）；
mx：段内最长连续段的长度。
合并 a+b：
l = a.l + a.u * b.l：如果左段全部可通，则左起连续段能延续到 b 的 l；
r = b.r + b.u * a.r：对称；
u = a.u * b.u：只有两端全通才全通；
mx = max(a.mx, b.mx, a.r + b.l)：跨中间拼接。
这是区间合并维护最长连续段的标准线段树节点（类似"最长连续 1 段"问题）
底为 N 的迭代式（非递归）线段树，维护 max。
change(k,x)：把叶子 k 更新为 x，向上取 max。
query(l,r)：区间 [l,r] 的 max，经典左开右开迭代查询写法
K+1 棵 node 线段树 T[0..K]，每棵用 node 合并。
change：单点更新叶子为 node，向上用 + 合并。
Query：区间查询，分别累积左边 L 与右边 R（左集合升序、右集合降序合并后再拼），返回合并后的 node
v[i] 记录第 i 个串与第 i+1 个串的最长公共前缀 LCP。
st 存那些 LCP 长度 > K 的位置（这些没法用 ≤K 的多重线段树直接表示，需单独用单调栈处理）
读入第 x 个串，更新两个线段树。
Node 线段树的语义：对阈值 i，T[i] 的第 k 个叶子表示"位置 k 的 v（LCP 长度）是否 ≥ i"——≥i 记作 b(全1)，<i 记作 a(空)。于是对区间查询 T[i] 的 mx 就是该区间内 LCP ≥ i 的最长连续段长度。
核心思想（重要）‍：把问题拆成"对每个长度阈值 i，看有多少连续位置满足 LCP ≥ i"。这是处理"最长公共前缀 ≥ i 的连续块"的标准技巧
L[x]、R[x]：对 st 中按 v 建立的笛卡尔树（大根堆，v 为键值）的左右儿子。
dfs(x)：后序遍历求子树大小 S[x]，并用 v[x]*(S[x]+1) 更新 ans。
语义：对 v 值 > K 的位置，枚举"以某位置为最小 LCP 的矩形面积"，类似直方图最大矩形，把 LCP 长度 × 连续块大小 这种乘积送入答案统计
读入 n、m。
init(i) 初始化所有位置。
操作 1（查询 [l,r]）：
ans = query(l,r)：区间内单个字符串的最大长度；
枚举阈值 i=1..K，用 node 线段树查询 [l+1,r] 的最长连续"LCP≥i"段长 z，ans = max(ans, i*(z+1))——区间内能构成的最长重复结构长度；
对 st（大 LCP 边界）在 [l,r] 内的连续段，建笛卡尔树跑 dfs 更新 ans（处理 LCP > K 的情况）；
输出 ans。
操作 2：init(read()) 修改某个位置。
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 131072, M = 1e5, K = 50;

struct node { int l, r, u, mx; } T[K+5][N*2+5];
node operator+(const node& a, const node& b) {
    return {.l = a.l+a.u*b.l, .r = b.r+b.u*a.r, .u = a.u*b.u, .mx = max(max(a.mx, b.mx), a.r+b.l)};
}

int t[N*2+5];
void change(int k, int x) {
    for (t[k+=N]=x; k>>=1;)
        t[k] = max(t[k<<1], t[k<<1|1]);
}

int query(int l, int r) {
    int res = 0;
    for (l+=N-1, r+=N+1; l^r^1; l>>=1, r>>=1) {
        if (~l&1) res = max(res, t[l+1]);
        if (r&1) res = max(res, t[r-1]);
    }
    return res;
}

void change(node* t, int k, node x) {
    for (t[k+=N]=x; k>>=1;)
        t[k] = t[k<<1] + t[k<<1|1];
}

node Query(node* t, int l, int r) {
    node L{}, R{}; int ul = 0, ur = 0;
    for (l+=N-1, r+=N+1; l^r^1; l>>=1, r>>=1) {
        if (~l&1) L = ul ? L+t[l+1] : (ul=1, t[l+1]);
        if (r&1) R = ur ? t[r-1]+R : (ur=1, t[r-1]);
    }
    return ul ? ur ? L+R : L : R;
}

string s[M+5];
int v[M+5];
set<int> st;
void init(int x) {
    //读串，更新普通线段树叶子为串长
    cin >> s[x]; change(x, s[x].size());
    if (v[x] > K) st.erase(x);//移除旧的大LCP标记
    if (v[x+1] > K) st.erase(x+1);
    //重算 v[x] = LCP(s[x], s[x-1])
    for (v[x]=0; v[x] < s[x].size() && v[x] < s[x-1].size() &&
        s[x][v[x]] == s[x-1][v[x]];) ++v[x];
    for (v[x+1]=0; v[x+1] < s[x].size() && v[x+1] < s[x+1].size() &&
        s[x][v[x+1]] == s[x+1][v[x+1]]; ) ++v[x+1];
    if (v[x] > K) st.insert(x);//新的大LCP加入 st
    if (v[x+1] > K) st.insert(x+1);
    //对每个阈值 i(1..K) 更新 node 线段树 "不足"(v<i) 的节点：空 "足够"(v>=i) 的节点：单1
    node a = {.l = 0, .r = 0, .u = 0, .mx = 0}, b = {.l = 1, .r = 1, .u = 1, .mx = 1};
    for (int i = 1; i <= K; ++i)
        change(T[i], x, v[x] < i ? a : b), change(T[i], x+1, v[x+1] < i ? a : b);
}

int S[M+5], L[M+5], R[M+5], ans;
void dfs(int x) {
    S[x] = 1;
    if (L[x]) dfs(L[x]), S[x] += S[L[x]];
    if (R[x]) dfs(R[x]), S[x] += S[R[x]];
    ans = max(ans, v[x]*(S[x]+1));
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int p(const set<int>::iterator& it) {
    return it != st.end() ? *it : M + 1;
}

int a[M+5], cnt, zn, Z[M+5];
int main() {
    int n = read(), m = read(), i, l, r, z;
    for (i = 1; i <= n; ++i) init(i);
    while (m--) {
        if (read() == 1) {
            l = read(), r = read(); ans = query(l, r);//先用普通线段树：单点串长最大
            if (l < r)
                for (i = 1; i <= K; ++i)//枚举阈值，取 node 树 mx
                    z = Query(T[i], l+1, r).mx, ans = max(ans, i*(z?z+1:0));
            //处理大 LCP 的笛卡尔树
            auto it = st.upper_bound(l);
            for (z=p(it); z <= r;) {
                for (a[cnt=1]=z; (z=p(++it)) <= r && z == a[cnt]+1; ) a[++cnt] = z;
                for (i = 1, zn = 0; i <= cnt; ++i) {//在连续块 a[1..cnt] 上建笛卡尔树
                    L[a[i]] = R[a[i]] = 0;
                    while (zn && v[a[i]] < v[a[Z[zn]]])
                        L[a[i]] = a[Z[zn--]];
                    R[a[Z[zn]]] = a[i];
                    Z[++zn] = i;
                }
                dfs(a[Z[1]]);
            }
            printf("%d\n", ans);
        }
        else init(read());//更新操作：读入位置并重新 init
    }
    return 0;
}