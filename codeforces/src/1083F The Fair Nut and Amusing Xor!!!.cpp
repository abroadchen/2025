//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
c[i]=a[i]^b[i]：当且仅当 a[i]==b[i] 时 c[i]==0。
d[i%k]：把下标按模 k 分成 k 条独立链，每条链内相邻 c 的异或。链之间互不影响，所以可独立判断
p 数组：把 k 条链的前缀异或结果顺序拼接成的一维数组（全局编号 1..tot）。
ans：所有链中 p[j]==0 的位置总数。
m = n-k+1：每个"模 k 完全覆盖"能真正对齐的有效下界。z > m 的位置属于无法被完整覆盖的尾部，用 lim[i] 标记该链第一个越界位置。
cnt：越界段（尾部 lim..R）中 p==0 的个数。cnt 是"可行性"的判据——out() 里 cnt != k-1 就输出 -1
M=388 为块长，把 p 数组（长度约 n）分成约 n/388 块。
w[i][v]：第 i 块中"值恰为 v"的元素个数（值域 1<<14 的量级）。
这是分块（分块 sqrt）+ 懒标记 tag + 值域计数桶，用于支持"区间整体异或一个值"和"统计区间内等于某值的个数"两类操作，均摊 O(√n)
典型的分块区间异或。p[i] 真实值 = p[i] ^ tag[pos[i]]
因为在 add 中整块只改了 tag，所以块内"真实值仍等于某值 v"的个数就是 w[i][v ^ tag]…… 这里实现是统计 p[i]==tag[i]，即当前被整体异或后恰好变回 0 的位置数（因为"等于 tag 值"意味着 ^tag 后为 0）。这正是为统计归零（可行）位置服务的
修改 a_x（或 b_x）的异或值 y，会影响 c[x]（即 c[x]^=y），进而影响 c[x]^c[x-1]（链内差分）。由于链内是前缀异或关系，d[t][pos] 从某个下标起全部受影响，表现为对该链后缀区间 s..R[t] 整体异或 y
修改 a_x=Y 等价于 a[x]^= (a[x]^Y)，即对 c[x]=a[x]^b[x] 异或 old_a[x]^Y，同时 c[x+1] 也受影响，所以调用 modify(x, ...) 和 modify(x+1, ...) 两处
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

constexpr int N = 2e5+5, M = 388;

int cnt, k, n, ans;
void out() {
    if (cnt != k-1) { cout << "-1\n"; return; }
    write(n - ans), putchar('\n');
}

int q, m, a[N], b[N], c[N], tot, L[N], R[N], p[N], lim[N];
vector<int> d[N];
void init() {
    n = rd(), k = rd(), q = rd(); m = n - k + 1;
    rep(i,n) a[i] = rd();
    rep(i,n) b[i] = rd();
    rep(i,n) c[i] = a[i]^b[i];
    rep(i,n) d[i%k].push_back(c[i]^c[i-1]);
    ans = cnt = tot = 0;
    for (int i = 0; i <= k-1; i++) {
        L[i] = tot + 1;//该链在全局 p 数组中的起始位置
        for (int j = 0; j < d[i].size(); j++) {
            int z = j*k + (!i ? k : i);
            if (j) d[i][j] ^= d[i][j-1];//链内做前缀异或
            p[++tot] = d[i][j]; ans += !p[tot];//ans = p 中等于 0 的元素个数
        }
        R[i] = tot; lim[i] = tot + 1;
        for (int j = L[i]; j <= R[i]; j++) {
            int z = (j-L[i])*k + (!i ? k : i);//该 p 下标对应的原数组下标位置映射
            if (z > m) { lim[i] = j; break; }//lim: 首个"越界(无效)"位置
        }
        for (int j = lim[i]; j <= R[i]; j++) if (!p[j]) cnt++;//cnt = 链尾段(越界段) 中 p==0 的个数
    }
}

int sz, ls[N], rs[N], w[N/M+5][1<<14], pos[N];
void pre() {
    sz = n/M + (n%M > 0);
    rep(i,sz) {//对每个块 ls[i]..rs[i]，w[i][p[j]]++ 记录块内各值出现次数
        ls[i] = rs[i-1] + 1;
        rs[i] = min(ls[i]+M, n);
        for (int j = ls[i]; j <= rs[i]; j++)
            w[i][p[j]]++, pos[j] = i;//记录每个全局位置属于哪个块
    }
}

int tag[N];
void add(int l, int r, int val) {
    int u = pos[l], v = pos[r];
    if (u == v) {//同块：块内每个 p[i]^=val，更新 w
        for (int i = l; i <= r; i++) w[v][p[i]]--, p[i] ^= val, w[v][p[i]]++;
        return;
    }
    for (int i = u+1; i <= v-1; i++) tag[i] ^= val;// 整块 (u+1..v-1)：只打 tag[i]^=val（懒标记，不逐个改 p）
    // 两端散块：逐个 p[i]^=val 并更新 w
    for (int i = l; i <= rs[u]; i++) w[u][p[i]]--, p[i] ^= val, w[u][p[i]]++;
    for (int i = ls[v]; i <= r; i++) w[v][p[i]]--, p[i] ^= val, w[v][p[i]]++;
}

int calc(int l, int r) {
    if (l > r) return 0;
    int u = pos[l], v = pos[r], ret = 0;
    if (u == v) {//同块：遍历统计 p[i]==tag[v]
        for (int i = l; i <= r; i++) ret += p[i] == tag[v];
        return ret;
    }
    for (int i = u+1; i <= v-1; i++) ret += w[i][tag[i]];//块内等于懒标记值的个数
    for (int i = l; i <= rs[u]; i++) ret += p[i] == tag[u];//散块：统计 p[i]==tag[u]  / p[i]==tag[v]
    for (int i = ls[v]; i <= r; i++) ret += p[i] == tag[v];
    return ret;
}
void modify(int x, int y) {
    if (x > n) return;
    //定位到哪条链
    int t = x%k, s = (x-1)/k + L[t];//链内相对位置 + 链起点 = 全局 p 下标
    //先把旧贡献减掉
    cnt -= calc(lim[t], R[t]); ans -= calc(L[t], R[t]);
    add(s, R[t], y);//从该位置到链尾整体异或 y
    ans += calc(L[t], R[t]); cnt += calc(lim[t], R[t]);//重新统计
}

char op[5];
void solve() {
    out();
    for (; q; q--) {
        cin >> op;
        int x = rd(), y = rd();
        if (op[0] == 'a') modify(x,a[x]^y), modify(x+1,a[x]^y), a[x] = y;
        if (op[0] == 'b') modify(x,b[x]^y), modify(x+1,b[x]^y), b[x] = y;
        out();
    }
}

int main() {
    init(); pre(); solve();
    return 0;
}