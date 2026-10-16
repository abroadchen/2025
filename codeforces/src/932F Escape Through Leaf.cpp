//
// Created by Psy.C on 2026/10/16.
//
/**
line 代表形如 y = m·x + c 的直线。
node 是李超线段树节点：管辖值域区间 [tl, tr]，保存该区间里"最有希望/最优"直线 val，并有左右孩子。
tr[N] 是一个指针数组——每个节点都拥有一棵李超线段树（DSU on tree 的核心
标准李超树插入：把新直线 u 与当前节点直线 val 比较中点值，把较差者下放到仍可能更优的子区间
沿查询点 x 所在分支下行，处处取最小值。返回 min
每个节点把自己表示成一条直线 y = b[x]·z + dp[x]，向上传给父节点；父亲查询所有儿子的直线在自己的 a[x] 处取最小。

vc[x]：节点 x 记账了所有（其子树传上来的）直线。
tr[x]：对应这些直线的李超树。
启发式合并：每次把小子树（vc[zc]）的直线全部插进大子树（vc[x]）的李超树，保证总复杂度 O(n log² n)。
叶子节点 dp=0
读入 n、每个节点的 a、b，建边，从根（1）DFS，最后输出所有节点的 dp[i]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e5+5, M = 2e5+5;
constexpr ll inf = 1e18;

struct line {
    ll m, c;
    line() { m = 0; c = inf; }
    line(ll k, ll b) { m = k; c = b; }
    ll vl(ll x) const { return m*x + c; }
};

struct node {
    ll tl, tr, tm;
    line val;
    node *l, *r;
    node(ll x, ll y) {
        tl = x, tr = y, tm = tl + (tr-tl)/2;
        l = r = nullptr;
    }
    void add(line u) {
        //保证当前节点存的直线在中点更优
        if (u.vl(tm) < val.vl(tm)) swap(u, val);
        if (u.vl(tl) < val.vl(tl)) {//左端点更优 → 递归左子树
            if (l == nullptr) l = new node(tl, tm);
            l->add(u);
        }
        if (u.vl(tr) < val.vl(tr)) {
            if (r == nullptr) r = new node(tm+1, tr);
            r->add(u);
        }
    }
    ll query(ll x) const {
        ll ans = val.vl(x);
        if (x <= tm) {
            if (l != nullptr) ans = min(ans, l->query(x));
        } else if (r != nullptr) ans = min(ans, r->query(x));
        return ans;
    }
} *tr[N];
vector<line> vc[N];
vector<ll> s[N];

ll dp[N], a[N], b[N];
void dfs(ll x, ll fa) {
    ll zc, pd = 1;
    tr[x] = new node(-M, M);
    for (ll i = 0; i < s[x].size(); ++i) {
        zc = s[x][i];
        if (zc == fa) continue;
        pd = 0;
        dfs(zc, x);
        if (vc[zc].size() > vc[x].size()) {//小集合合并进大集合
            swap(vc[x], vc[zc]);
            swap(tr[x], tr[zc]);
        }
        for (ll p = 0; p < vc[zc].size(); ++p) {
            tr[x]->add(vc[zc][p]);
            vc[x].push_back(vc[zc][p]);
        }
    }
    if (pd) dp[x] = 0;
    else dp[x] = tr[x]->query(a[x]);//非叶子：在所有儿子的直线里，在 x=a[x] 取最小
    line cur = {b[x], dp[x]};//把当前节点转成一条直线 y = b[x]*z + dp[x]
    vc[x].push_back(cur);
    tr[x]->add(cur);
}

ll n, x, y;
int main() {
    fast;
    cin >> n;
    rep(i,1,n) cin >> a[i];
    rep(i,1,n) cin >> b[i];
    rep(i,1,n-1) {
        cin >> x >> y;
        s[x].push_back(y); s[y].push_back(x);
    }
    dfs(1, 0);
    rep(i,1,n) {
        if (i > 1) cout << ' ';
        cout << dp[i];
    }
    cout << '\n';
    return 0;
}