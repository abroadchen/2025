//
// Created by Psy.C on 2026/10/9.
//
/**
ODT 的核心思想：把数组压成若干"值连续相同的区间段"。每个区间 [l, r] 内所有值都是 v。区间按左端点 l 有序地存在 set 里。

mutable ll v 很关键——它允许通过 set::iterator（即使它是 const）直接修改 v，避免频繁 erase/insert
作用：确保 x 成为一个新区间的左端点。如果原来的 [l, r] 含 x，就把它拆成 [l, x-1] 和 [x, r] 两段，返回 [x, r] 的迭代器
先 split 出左右断点，删掉中间所有段，然后塞进一个统一大区间。这就是"区间赋值"，也是 ODT 降低复杂度的关键——数据随机时区间段数大大减少
由于 v 是 mutable，直接对每段 it->v += v 即可，无需重建结构
把所有段拷出来按值排序，累减每段长度定位第 k 小
每段 v^k 用快速幂 ksm 计算，乘以段长后求和取模
伪随机生成器，用来生成操作序列（保证 ODT 的复杂度分析成立——操作排布随机、且有区间赋值推平操作，所以段数期望在 log 级别）
初始时 n 个长度为 1 的小区间
随机生成 m 个操作：

op=1：区间加
op=2：区间赋值（推平，这是 ODT 复杂度核心）
op=3：区间第 k 小
op=4：区间 k 次方和（模 y）

ODT 的复杂度依赖于"区间赋值"操作（assign）‍——它会把连续段合并成一个大区间，使 set 中段数保持很少（理想情况下 O(log n) 级别）。
最坏情况（无推平、纯随机的值）会退化成 O(n) 每操作，因此 ODT 只在数据随机/有推平操作时是可靠的。这也是本题为何用伪随机生成操作的原因。
每题操作复杂度约为 O(段数 × log n)，其中 get_kth 还要排序，为 O(段数 log 段数)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, mod = 1e9+7;

struct node {
    int l, r;
    mutable ll v;
    node(int l, int r=-1, ll v=0): l(l), r(r), v(v) {}
    bool operator<(const node& o) const { return l < o.l; }
};
set<node> s;
auto split(int x) {
    auto it = s.lower_bound(node(x));//找第一个左端点>=x的区间
    if (it != s.end() && it->l == x) return it;//x 已经是某区间左端点
    --it;//否则 x 落在前一个区间里
    if (it->r < x) return s.end();//x 超出范围
    int l = it->l, r = it->r;
    ll v = it->v;
    s.erase(it); s.insert(node{l, x-1, v});
    return s.insert(node{x, r, v}).first;//右边部分 [x, r]，返回其迭代器
}

void assign(int l, int r, int v) {
    auto R = split(r+1);//先把 r+1 作为断点
    auto L = split(l);//再把 l 作为断点
    s.erase(L, R);//删除 [l, r] 范围的所有区间
    s.insert(node{l, r, v});//用一个大区间 [l, r]=v 替代
}

void add(int l, int r, int v) {
    auto R = split(r+1);
    auto L = split(l);
    for (auto it = L; it != R; ++it) it->v += v;
}

ll get_kth(int l, int r, int k) {
    auto R = split(r+1);
    auto L = split(l);
    vector vec(L, R);//取出所有段
    ranges::sort(vec, [](auto a, auto b) {
        return a.v < b.v;//按值排序
    });
    for (auto &[l, r, v] : vec) {
        k -= r - l + 1;//每段贡献长度
        if (k <= 0) return v;//第 k 小落在这段
    }
    return -1;
}

ll ksm(ll a, ll b, ll p) {
    ll res = 1;
    for (ll t = a%p; b; b>>=1, t=t*t%p)
        if (b&1ll) (res*=t) %= p;
    return res;
}

ll get_sum(int l, int r, int k, int p) {
    auto R = split(r+1);
    auto L = split(l);
    ll res = 0;
    for (auto it = L; it != R; ++it) {
        auto [l, r, v] = *it;
        res += (r-l+1)*ksm(v, k, p);
        res %= p;
    }
    return res;
}

ll seed;
ll rnd() {
    ll ret = seed;
    seed = (seed*7+13)%mod;
    return ret;
}

int n, m;
ll mx, a[N];
int main() {
    fast;
    cin >> n >> m >> seed >> mx;
    for (int i = 1; i <= n; ++i) {
        a[i] = rnd()%mx + 1;//初始每个位置随机值
        s.insert(node{i, i, a[i]});//每个位置一个长度为1的区间
    }
    for (int i = 1, op, l, r, x, y; i <= m; ++i) {
        op = rnd()%4+1; l = rnd()%n+1; r = rnd()%n+1;
        if (l > r) swap(l, r);
        if (op == 3) x = rnd()%(r-l+1)+1; //第k小，k在区间长度内
        else x = rnd()%mx+1;//加/赋值 的数值
        if (op == 4) y = rnd()%mx+1;//模数 y
        if (op == 1) add(l, r, x);
        else if (op == 2) assign(l, r, x);
        else if (op == 3) {
            ll ans = get_kth(l, r, x);
            cout << ans << '\n';
        } else {//区间k次方和
            ll ans = get_sum(l, r, x, y);
            cout << ans << '\n';
        }
    }
    return 0;
}