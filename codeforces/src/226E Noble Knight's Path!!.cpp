//
// Created by Psy.C on 2025/12/9.
//
/*
*B: 倍增数组大小(20足以处理10^6规模)
node: 链式前向星的边结构
add: 添加无向边函数
 *
*cnt: 节点计数器
node3: 线段树节点结构(左右子节点指针和区间和)
tr: 线段树节点数组
 *构建空的线段树
 *在主席树中插入位置p，创建新版本
 *查询版本y相对版本x在区间[l,r]中增加的元素个数
 *
*s: 子树大小
f: 父节点
d: 深度
p: 倍增数组(用于LCA)
son: 重儿子
*树链剖分第二遍DFS：
dfn: DFS序
low: DFS序对应的节点
top: 所在重链的顶端节点
 *
 *更新操作：在位置x插入元素，创建版本t
 *树链剖分求LCA
 *根据flag选择使用栈或队列的数据结构适配器
*find: 在一段路径上找第k大元素
func: 单向路径查询
query: 双向路径查询
 *
 */
#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000005
#define M 5000005
using namespace std;

constexpr int inf = 1e9, B = 20;
struct node { int q, w, nxt; } a[N];//起点q、终点w、下一条边的索引nxt
int cnt, head[N];//每个节点的第一条边
void add(const int q, const int w) {
    a[++cnt].q = q; a[cnt].w = w; a[cnt].nxt = head[q]; head[q] = cnt;
}

struct node2 {//可持久化线段树
    int cnt = 0;//已创建节点数量
    struct node3 {//线段树节点
        int l, r, sum;
#define l(x) tr[x].l
#define r(x) tr[x].r
#define sum(x) tr[x].sum
    } tr[M]{};
    int build(const int l, const int r) {
        const int root = ++cnt;
        if (l == r) return root;//叶子节点
        const int mid = (l + r) >> 1;
        l(root) = build(l, mid);
        r(root) = build(mid + 1, r);
        return root;//根节点编号
    }
    int update(const int x, const int l, const int r, const int p) {//版本x的基础上更新位置p
        int root = ++cnt;
        tr[root] = tr[x];//复制原节点信息
        if (l == r) return sum(root) = 1, root;
        const int mid = (l + r) >> 1;
        if (p <= mid) l(root) = update(l(root), l, mid, p);
        else r(root) = update(r(root), mid + 1, r, p);
        sum(root) = sum(l(root)) + sum(r(root));
        return root;//新版本的根节点
    }
    int query(const int x, const int y, const int L, const int R, const int l, const int r) {
        if (l <= L && R <= r) return sum(y) - sum(x);
        const int mid = (L + R) >> 1; int ans = 0;
        if (l <= mid) ans += query(l(x), l(y), L, mid, l, r);
        if (mid < r) ans += query(r(x), r(y), mid + 1, R, l, r);
        return ans;
    }
} t1;


int s[N], f[N], d[N], p[N][B+5], son[N];
void dfs(const int x, const int fa) {
    s[x] = 1; f[x] = fa; d[x] = d[fa] + 1; p[x][0] = fa;
    for (int i = 1; i <= B; ++i) p[x][i] = p[p[x][i-1]][i-1];
    int id = 0;
    for (int i = head[x]; i; i = a[i].nxt) {
        if (fa ^ a[i].w) {
            dfs(a[i].w, x);
            s[x] += a[i].w;
            if (s[id] < s[a[i].w]) id = a[i].w;
        }
    }
    son[x] = id;
}

int dfn[N], low[N], top[N];
void dfs2(const int x, const int tp) {
    dfn[x] = ++cnt; low[cnt] = x; top[x] = tp;
    if (!son[x]) return;
    dfs2(son[x], tp);//优先遍历重儿子，保持重链连续
    for (int i = head[x]; i; i = a[i].nxt) {
        if (f[x] != a[i].w && a[i].w != son[x])
            dfs2(a[i].w, a[i].w);//每条轻边新开一条链
    }
}

int c[N], root[N], n;
void update(const int x, const int t) {//在前一个版本基础上更新节点x的DFS序号，得到新版本
    c[x] = 1;
    root[t] = t1.update(root[t-1], 1, n, dfn[x]);
}

int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]]) swap(x, y);
        x = f[top[x]];//当两点不在同一条重链上时，让深度较浅的链顶端向上跳
    }
    if (d[x] < d[y]) swap(x, y);
    return y;//返回深度较浅的节点
}

#define ii pair<int, int>
stack<ii> st;
queue<ii> qu;
bool flag;
void clear() {
    while (!st.empty()) st.pop();
    while (!qu.empty()) qu.pop();
}
void push(const ii& t) { if (flag) qu.push(t); else st.push(t); }
bool empty() {
    if (flag) return qu.empty();
    return st.empty();
}
ii front() {
    if (flag) return qu.front();
    return st.top();
}
void pop() { if (flag) qu.pop(); else st.pop(); }

int tot;//查找第k个满足条件的节点
int find(const int L, const int R, const int k, const int t) {
    const int o = L - 1; int l = L - o, r = R - o, ans = 0;
    while (l <= r) {
        const int mid = (l + r) >> 1; int u;
        if (flag) u = d[low[R]] - d[low[mid+o]] + 1 -
            t1.query(root[t], root[tot], 1, n, mid+o, R);
        else u = d[low[mid+o]] - d[low[L]] + 1 -
            t1.query(root[t], root[tot], 1, n, L, mid+o);
        if (u >= k) {
            if (flag) l = mid + 1; else r = mid - 1;
            ans = mid + o;
        } else flag ? r = mid - 1 : l = mid + 1;
    }
    return low[ans];//返回找到的节点编号
}

int func(int x, int y, const int t, int k) {
    if (k > 0) flag = true; else flag = false, k = -k;
    clear();
    if (!y) y = 1;
    else {
        int Y = x;
        for (int i = B; i >= 0; --i) if (d[p[Y][i]] > d[y]) {
            Y = p[Y][i];
        }
        y = Y;
    }
    x = f[x];
    if (d[x] < d[y]) return -inf;
    int num = 0;
    while (top[x] != top[y]) {
        if (d[x] < d[y]) swap(x, y);
        num += d[x] - d[top[x]] + 1 -
            t1.query(root[t], root[tot], 1, n, dfn[top[x]], dfn[x]);
        push({dfn[top[x]], dfn[x]});
        x = f[top[x]];
    }
    if (d[x] < d[y]) swap(x, y);
    num += d[x] - d[y] + 1 - t1.query(root[t], root[tot], 1, n, dfn[y], dfn[x]);
    push({dfn[y], dfn[x]});
    if (num < abs(k)) return -num;
    while (!empty()) {
        const ii u = front(); pop();
        const int o = d[low[u.second]] - d[low[u.first]] + 1 -
            t1.query(root[t], root[tot], 1, n, u.first, u.second);
        if (o >= k) return find(u.first, u.second, k, t);
        k -= o;
    }
    return -inf;
}

int query(int x, int y, const int t, int k) {
    int o = 1;
    if (d[x] < d[y]) swap(x, y), o = -1;
    const int lca = LCA(x, y);
    if (lca == y) return func(x, y, t, k * o);
    int u = func(o + 1 ? x : y, f[lca], t, k);//将路径分为两段分别查询
    if (u > 0) return u;
    k += u;
    u = func(o + 1 ? y : x, lca, t, -k);
    return u;
}

int q;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> q;
        if (q) add(i, q), add(q, i);
    }
    cnt = 0; root[0] = t1.build(1, n);
    dfs(1, 0); dfs2(1, 1);
    cin >> q;
    while (q--) {
        int op, x; cin >> op;
        if (op == 1) {
            cin >> x;
            update(x, ++tot);
        } else {
            int y, k, t;
            root[tot + 1] = root[tot];
            tot++;
            cin >> x >> y >> k >> t;
            const int ans = query(x, y, t, k);
            cout << (ans <= 0 ? -1 : ans) << '\n';
        }
    }
    return 0;
}