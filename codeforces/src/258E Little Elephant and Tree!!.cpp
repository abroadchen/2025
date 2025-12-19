//
// Created by Psy.C on 2025/12/19.
//
/*
 *l,r: 区间左右端点
 *mn: 区间最小值
 *mnc: 最小值的出现次数
 *lz: 懒惰标记
 *to: 边的终点
 *nxt: 下一条边的索引
 *hd: 每个节点的第一条边
 *cnt: 边的计数器
 *st:进入时间, ed:退出时间, tim:时间戳计数器
 *
 *复杂度为O((n+m)log n)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100000
using namespace std;

struct node { int l, r, mn, mnc, lz; } s[(N<<2)+5];
void build(const int k, const int l, const int r) {
    s[k].l = l; s[k].r = r; s[k].mnc = r - l + 1;//初始时所有位置都是0，最小值0的个数为区间长度
    if (l == r) return;
    const int mid = (l + r) >> 1;
    build(k<<1, l, mid);
    build(k<<1|1, mid + 1, r);
}

int to[(N<<1)+5], nxt[(N<<1)+5], hd[N+5], cnt;
void add(const int u, const int v) {
    to[++cnt] = v; nxt[cnt] = hd[u]; hd[u] = cnt;//添加新边 链接前一条边 更新头指针
}

int st[N+5], ed[N+5], tim;
void dfs(const int x, const int f) {//记录每个节点的进入和退出时间（欧拉序）
    st[x] = ++tim;
    for (int i = hd[x]; i; i = nxt[i]) {
        const int u = to[i];
        if (u == f) continue;
        dfs(u, x);// 递归遍历子节点
    }
    ed[x] = tim;
}

void pushdown(const int k) {//下传懒惰标记
    if (s[k].lz) {//如果有懒惰标记
        s[k<<1].mn += s[k].lz;
        s[k<<1].lz += s[k].lz;
        s[k<<1|1].mn += s[k].lz;
        s[k<<1|1].lz += s[k].lz;
        s[k].lz = 0;//清除当前节点标记
    }
}

void push_up(const int k) {//向上传递信息
    s[k].mn = min(s[k<<1].mn, s[k<<1|1].mn);//区间最小值
    s[k].mnc = 0;//最小值的出现次数
    if (s[k].mn == s[k<<1].mn) s[k].mnc += s[k<<1].mnc;
    if (s[k].mn == s[k<<1|1].mn) s[k].mnc += s[k<<1|1].mnc;
}

void modify(const int k, const int l, const int r, const int x) {//在区间[l,r]上增加x
    if (l <= s[k].l && s[k].r <= r) {
        s[k].mn += x;//直接修改
        s[k].lz += x;//打上懒惰标记
        return;
    }
    pushdown(k);
    const int mid = (s[k].l + s[k].r) >> 1;
    if (r <= mid) modify(k<<1, l, r, x);//递归修改子区间
    else if (l > mid) modify(k<<1|1, l, r, x);
    else modify(k<<1, l, mid, x), modify(k<<1|1, mid + 1, r, x);
    push_up(k);
}


vector<int> g[N+5];//存储边的关系
int ans[N+5], n;
void dfs2(const int x, const int f) {
    for (int i = 0; i < static_cast<int>(g[x].size()); ++i) {//处理与当前节点相关的所有边
        const int u = g[x][i];
        modify(1, st[x], ed[x], 1);//当前节点子树加1
        modify(1, st[u], ed[u], 1);//相邻节点子树加1
    }
    if (s[1].mn > 0) ans[x] = n; else ans[x] = n - s[1].mnc;//所有位置都被覆盖  否则减去未覆盖位置数
    if (ans[x]) ans[x]--;//排除自身节点的贡献
    for (int i = hd[x]; i; i = nxt[i]) {//递归处理子节点
        const int u = to[i];
        if (u == f) continue;
        dfs2(u, x);
    }
    for (int i = 0; i < static_cast<int>(g[x].size()); ++i) {//回溯时撤销修改
        const int u = g[x][i];
        modify(1, st[x], ed[x], -1);
        modify(1, st[u], ed[u], -1);
    }
}

int main() {
    fast;
    int m; cin >> n >> m; build(1, 1, n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs(1, 0);//第一次DFS获取时间戳
    for (int i = 1, u, v; i <= m; ++i) {//读取需要处理的边
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs2(1, 0);//第二次DFS计算答案
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}