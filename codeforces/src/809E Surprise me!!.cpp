//
// Created by Psy.C on 2026/9/20.
//
/**
线性筛（欧拉筛）：在 O(N) 内同时求出：

phi[i]：欧拉函数 φ(i)（1..i 中与 i 互质的个数）。
mu[i]：莫比乌斯函数 μ(i)（0/±1）。
标准筛法：若 i%pri[j] != 0，则 μ(x)=-μ(i)、φ(x)=(pri[j]-1)·φ(i)；否则 φ(x)=pri[j]·φ(i) 并 break（保证每个合数只被最小质因子筛一次→线性）。
卷积预处理 f（重点）
用倍数枚举实现（O(N log N)）。
μ(j/i) 是莫比乌斯函数，配合整除求和构成"莫比乌斯反演"的容斥系数，常见于"求和式含 gcd、且要按 gcd=d 分类"的问题。f[T] 正是后面 get(T) 里外层乘的系数。
原树的深度、dfn（DFS 序，用于虚树排序）、倍增父表。
lca：标准倍增 LCA。虚树构建会大量调用它

虚树只保留关键点（以及它们的 LCA），用于对特定点集做树上 DP，把 O(k·n) 降到 O(k log n)
S[i] = {id, p}：第 i 个关键点，值为 id，在原树位于节点 p
把关键点按 dfn 排序后依次插入，用单调栈维护"当前虚树的右链"，遇到新点的 LCA 不在栈顶链上时，回退弹出并把边补进虚树。
关键点之间有依赖（链式栈）才能线性建树
D[x] 初始只有关键点带值 φ(id)（在 solve 里预先 D[S.p] += phi[S.id]）。
自底向上：D[x] = Σ 孩子 D（把子树的所有关键点"值"聚合到祖先）。此时 D[x] = 以 x 为根的虚树子树内所有关键点的 φ 之和
把每条虚树边当作一段"路径"，其长度 = dep[x]-dep[fa]（原树上两关键点间的边数）。
每个点的聚合值乘上到父亲的边数，即"距离加权"，累加出"点到祖先的距离·权"类贡献
把"子树到根的距离加权"再做一次自顶向下的前缀和，最终 D[x] 表达"从根到 x 的虚树路径上的某种累计贡献"
若根节点 1 不在关键点集合，则补入 id=0, p=1（0 的 φ(0) 是多少由约定，此处用于锚定虚树根）。
按 dfn 排序 → 建虚树 → 给每个关键点赋初值 φ(id) → 三段 DP。
最后 ret = Σ_{i} φ(S[i].id) * D[S[i].p]，返回虚树上的总贡献。
用 del 递归清零邻接表 + 重置变量，供下一个 T 复用
对每个 T，收集所有 T 的倍数 i = T, 2T, … 作为关键点：S[++m] = {id=i, p=p[i]}。
同时累加：
S1 = Σ φ(i)
S2 = Σ (dep[p[i]] - 1) · φ(i)（带深度）
用某种"两两配对公式"得初值 ret = 2·S1·S2，再减去 2·t（t 是虚树 DP 结果），得到这个 T 的净贡献。
最后乘 f[T]（第 2 步的容斥系数），返回。
背后的数学：Σ_{i|?} 类求和在枚举倍数集合上，缺啥用容斥 f[T] 修正；虚树 t 用于扣除"树内路径被重复计/需单独计"的部分

读入排列 p 和树，做一次全局 DFS（得到 dep/dfn/倍增表，供所有 T 的虚树共用）。
对每个 T 调 get(T) 累加到 ans。
最后 ans × inv(n(n-1)) mod p 输出期望（除以总方案数 n(n-1) 得到平均）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 202020, mod = 1e9+7;

ll ksm(ll x, int y) {
    ll ret = 1;
    for (; y; y>>=1, x=x*x%mod)
        if (y&1) ret=ret*x%mod;
    return ret;
}
ll inv(ll x) { return ksm(x, mod-2); }

int mu[N], phi[N], pri[N], cnt;
bool np[N];
ll f[N];
void init() {
    mu[1] = phi[1] = 1;
#define x i*pri[j]
    for (int i = 2; i <= N-1; ++i) {
        if (!np[i]) pri[++cnt] = i, mu[i] = -1, phi[i] = i-1;
        for (int j = 1; j <= cnt && x < N; ++j) {
            np[x] = 1;
            if (i%pri[j]) mu[x] = -mu[i], phi[x] = (pri[j]-1)*phi[i];
            else { phi[x] = pri[j]*phi[i]; break; }
        }
    }
#undef x
    for (int i = 1; i <= N-1; ++i)
        for (int j = i; j < N; j += i)
            (f[j] += 1ll*i*mu[j/i]*inv(phi[i])%mod) %= mod;
}

struct node { int t, nxt; } e[N<<1];
int head[N], ec;
void add(int fa, int t) {
    e[++ec] = {.t = t, .nxt = head[fa]}, head[fa] = ec;
    e[++ec] = {.t = fa, .nxt = head[t]}, head[t] = ec;
}

int dep[N], dfn[N], c, fa[N][30];
void dfs(int x, int f) {
    dep[x] = dep[fa[x][0]=f] + 1; dfn[x] = ++c;
    for (int i = 1; i <= 20; ++i) fa[x][i] = fa[fa[x][i-1]][i-1];
    for (int i = head[x]; i; i = e[i].nxt)
        if (e[i].t != f) dfs(e[i].t, x);
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 20; i >= 0; --i)
        if (fa[x][i] && dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if (x == y) return x;
    for (int i = 20; i >= 0; --i)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

namespace Ju {
    int m;//关键点个数
    struct node { int id, p; } S[N];//id=值, p=该值所在原树节点
    struct node2 { int t, nxt; } e[N<<1];
    int head[N], ecnt;
    void add(int f, int t) {
        e[++ecnt] = {.t = t, .nxt = head[f]}, head[f] = ecnt;
        e[++ecnt] = {.t = f, .nxt = head[t]}, head[t] = ecnt;
    }

    int st[N], top;
    void insert(int x) {
        if (top <= 1) return void(st[++top] = x);
        int lca = ::lca(x, st[top]);
        if (lca == st[top]) return void(st[++top] = x);
        while (top > 1) {
            int q = st[top-1], &p = st[top];
            if (dfn[q] == dfn[lca]) { add(q, p); --top; break; }
            if (dfn[q] < dfn[lca]) { add(lca, p); p = lca; break; }
            add(p, q), --top;
        }
        st[++top] = x;
    }
    ll D[N];
    void dfs(int x, int fa) {
        for (int i = head[x]; i; i = e[i].nxt)
            if (e[i].t != fa)
                dfs(e[i].t, x), (D[x] += D[e[i].t]) %= mod;
    }
    void dfs2(int x, int fa) {
        for (int i = head[x]; i; i = e[i].nxt)
            if (e[i].t != fa) dfs2(e[i].t, x);
        D[x] = D[x]*(dep[x] - dep[fa]) % mod;
    }
    void dfs3(int x, int fa) {
        (D[x] += D[fa]) %= mod;
        for (int i = head[x]; i; i = e[i].nxt)
            if (e[i].t != fa) dfs3(e[i].t, x);
    }
    void del(int x, int fa) {
        D[x] = 0;
        for (int i = head[x]; i; i = e[i].nxt)
            if (e[i].t != fa) del(e[i].t, x);
        head[x] = 0;
    }
    ll solve() {
        bool flg = 0;
        for (int i = 1; i <= m; ++i) flg |= (S[i].p == 1);
        if (!flg) S[++m] = {.id = 0, .p = 1};
        sort(S+1, S+m+1, [](const node& x, const node& y) {
            return dfn[x.p] < dfn[y.p];
        });
        for (int i = 1; i <= m; ++i) insert(S[i].p);
        while (top > 1) add(st[top], st[top-1]), --top;
        top = 0;
        for (int i = 1; i <= m; ++i) (D[S[i].p] += phi[S[i].id]) %= mod;
        dfs(1, 0); D[1] = 0;
        dfs2(1, 0); dfs3(1, 0);
        ll ret = 0;
        for (int i = 1; i <= m; ++i) (ret += phi[S[i].id]*D[S[i].p]%mod) %= mod;
        for (int i = 1; i <= m; ++i) S[i] = {.id = 0, .p = 0};
        del(1, 0);
        ecnt = m = 0;
        return ret;
    }
}

int n, p[N];
ll get(int T) {
    ll ret, S1 = 0, S2 = 0;
    for (int i = T; i <= n; i += T) {
        Ju::S[++Ju::m] = (Ju::node){.id = i, .p = p[i]};
        (S1 += phi[i]) %= mod;
        (S2 += 1ll*(dep[p[i]]-1)*phi[i]%mod) %= mod;
    }
    ret = S1*S2*2%mod;
    ll t = Ju::solve();
    ret = (ret - 2ll*t+mod+mod)%mod;
    return ret*f[T]%mod;
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
    init(); rd(n);
    int x, y;
    for (int i = 1; i <= n; ++i) rd(x), p[x] = i;
    for (int i = 1; i <= n-1; ++i) rd(x, y), add(x, y);
    dfs(1, 0);
    ll ans = 0;
    for (int T = 1; T <= n; ++T) (ans += get(T)+mod) %= mod;
    cout << ans*inv(1ll*n*(n-1)%mod)%mod;
    return 0;
}