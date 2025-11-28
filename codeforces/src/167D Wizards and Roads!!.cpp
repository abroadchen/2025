//
// Created by Psy.C on 2025/11/28.
//
/*
 *n(总数), k(初始数), a/b/c/d(生成参数), cnt(计数器), rt(根节点), m(查询数)
 *p[N]：存储点对的数组
*l, r：左右子节点索引
siz：子树大小
key：节点键值
f, g：用于计算树的某些属性
 *
 *更新节点t的子树大小
 *如果是叶子节点，f和g都为0
 *如果只有右子树或只有左子树，按相应规则更新
 *如果有两个子树，按复杂规则更新f和g值
 *
 *找到区间内second值最大的点作为根
 *设置节点键值，递归构建左右子树，更新节点信息
 *
 *DFS分割函数：按大小y分割树
 *根据y与左子树大小的关系决定如何分割
 *合并两棵树的函数：按key值合并
 *
 *读入n和k，读入前k个点对
 *读入生成参数，生成剩余的点对
 *按first值排序，构建笛卡尔树
*处理m次查询：
找到区间[l,r]对应的树节点
分割树得到区间子树
输出结果
重新合并树
 *
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
constexpr int N = 2e5+50, mod = 1e9+9;
int n, k, a, b, c, d, cnt, rt, m;
ii p[N];

struct node { int l, r, siz, key, f, g; } tr[N];

#define L tr[tr[t].l]
#define R tr[tr[t].r]
int update(const int t) {
    tr[t].siz = L.siz + R.siz + 1;
    if (!tr[t].l && !tr[t].r) { tr[t].f = tr[t].g = 0; return t; }
    if (!tr[t].l) { tr[t].f = R.g; tr[t].g = R.f + 1; return t; }
    if (!tr[t].r) { tr[t].f = L.g; tr[t].g = L.f + 1; return t; }
    tr[t].f = L.g + R.g; tr[t].g = max(L.f + R.g, L.g + R.f) + 1;
    return t;
}


void build(const int l, const int r, int& t) {
    if (l > r) return;
    int cur(-1), mid = 0;
    for (int i = l; i <= r; ++i)
        p[i].second > cur ? cur = p[i].second, mid = i : 0;
    tr[(t = ++cnt)].key = p[mid].second;
    build(l, mid - 1, tr[t].l);
    build(mid + 1, r, tr[t].r);
    update(t);
}

//辅助函数：将pair的两个值分别赋给两个变量 直接修改调用时传入的变量
//成员函数不会修改类的成员变量 常量成员函数
void f(int& a1, int& a2, const ii& x) { a1 = x.first, a2 = x.second; }
ii dfs(int t, const int y) {
    int x;
    if (!y) return {0, t};
    if (y == tr[t].siz) return {t, 0};
    return L.siz + 1 <= y ?
        (f(tr[t].r, x, dfs(tr[t].r, y - L.siz - 1)),
            update(t), make_pair(t, x)) :
        (f(x, tr[t].l, dfs(tr[t].l, y)),
            update(t), make_pair(x, t));
}

int dfs2(const int x, const int y) {
    if (!x || !y) return x + y;
    return tr[x].key > tr[y].key ?
        (tr[x].r = dfs2(tr[x].r, y), update(x)) :
        (tr[y].l = dfs2(x, tr[y].l), update(y));
}

int main() {
    fast;
    cin >> n >> k;
    rep(i,k) cin >> p[i].first >> p[i].second;
    cin >> a >> b >> c >> d;
    for (int i = k + 1; i <= n; ++i) p[i] = {
        (1ll * p[i - 1].first * a + b) % mod,
        (1ll * p[i - 1].second * c + d) % mod
    };
    sort(p + 1, p + n + 1);
    build(1, n, rt);
    cin >> m;
    while (m--) {
        int l, r, r1, r2; ii t;
        cin >> l >> r;
        t.first = l, t.second = 0;
        l = static_cast<int>((lower_bound(p + 1, p + n + 1, t) - p) - 1);
        f(r1, rt, dfs(rt, l));
        t.first = r + 1, t.second = 0;
        r = static_cast<int>((lower_bound(p + 1, p + n + 1, t) - p - 1) - l);
        f(rt, r2, dfs(rt, r));
        cout << max(tr[rt].f, tr[rt].g) << '\n';
        rt = dfs2(r1, rt);
        rt = dfs2(rt, r2);
    }
    return 0;
}