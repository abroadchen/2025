//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
int tag;                      // 整体延迟偏移量
map<int,int> a, b;            // 两组差分值
priority_queue<ad> q;         // 合并用的堆
map<int,int> 里键是一个坐标（某种位置/距离），值是一个整数贡献（可正可负）。
a 与 b 相互"反向"，tag 是一个惰性偏移：每次 move(x) 实际是把所有坐标整体平移 x，但用 tag += x 延迟实现，避免真的遍历 map。
真实坐标与存储坐标的关系：
a 存的是 真实值 - tag
b 存的是 真实值 + tag
这其实是一个维护"带配对/碰撞抵消"的多集数据结构的技巧——a 与 b 分别代表"某种资源在左侧/右侧的盈余"，每当 a 和 b 中对应位置同时存在时，可以相互抵消并产生新的配对。常用于流/匹配在数轴上的贪心合并
在某坐标 x 放置 y 个"从左往右的资源"，若右侧反向资源正好能吞掉/抵消，则用堆记录配对信息。等同于在数轴上做区间匹配的贪心合并
与 add 完全镜像：优先处理 b 中的存量，否则处理 a，在 a 盈余不足时翻转到 b 中去
堆 q 里存的是"寄存器": {dis, l}，表示在 b[l] 与 a[l+dis] 之间存在一对可抵消的资源。当平移量超过某阈值 2*tag 时，说明该配对该"结算"了，于是在循环里真正把它们从 a/b 中删除并生成新的邻居配对。

这是延迟维护配对、防止每次 move 都全量扫描的关键优化
query(x)：查询某坐标上的净贡献（b 处加，a 中 x+tag+1 处取 max），用于子树合并时查询。
get()：把 a、b 全部还原成真实坐标，排序后做一次前缀和取 max，得到当前集合能"覆盖/分配"的最大价值（即最终答案）
经典 on-tree：总是把元素较少的集合并入较大的，保证总复杂度 O(n log n)。
合并时要把 b 的所有元素还原成真实坐标，再逐个 add/sub 进 a
f[u] 表示"以 u 为根的子树中，所有沿路径向上运输好（可被父侧资源利用）的需求/资源的集合"。

每条边权 w[i]：子节点资源向上到达父节点时，位置会平移（消耗方向相反），用 move(w[i]-1) 处理。
子树合并：把子节点 f[v] 并入 f[u]。
点 u 上的请求 fh[u]：每个请求 {d, ff} 先查 query(d)（看现有可覆盖资源），扣掉可覆盖部分；剩余盈余再 add(d, ff), sub(d+1, ff) 进容器（对后续祖先可见）
所有距离（边权、请求 d）乘 2，把"半整"变成整数，避免浮点。
从根 1 开始 DFS，最终通过 f[1].get() 得到全局最优覆盖价值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5;

int cnt, head[N], to[N<<1], nxt[N<<1], w[N<<1];
inline void add(int u, int v, int c) {
    to[++cnt] = v, w[cnt] = c, nxt[cnt] = head[u], head[u] = cnt;
}

struct ad { int dis, l; };
bool operator<(const ad& a, const ad& b) { return a.dis > b.dis; }

struct node {
    int tag;
    map<int,int> a, b;
    priority_queue<ad> q;
    void add(int x, int y) {
        auto it = a.find(x+tag), it2 = b.find(x-tag);
        if (it != a.end()) { a[x+tag] += y; return; }//a 已有，直接加
        if (it2 != b.end()) {//b 中恰好有反向资源 → 抵消
            if (it2->second > y) { b[x-tag] -= y; return; }//b 盈余 > y
            if (it2->second == y) {//b 盈余 == y → 完全抵消
                if (it2 != b.begin()) {
                    auto l = it2; --l;
                    auto r = a.lower_bound(x+tag);
                    if (r != a.end()) q.push({r->first-l->first,l->first});
                }
                b.erase(it2);
                return;
            }
            //b 盈余 < y → 翻转
            a[x+tag] = y - it2->second;
            if (it2 != b.begin()) {
                auto l = it2; --l;
                q.push({x+tag-l->first, l->first});
            }
            b.erase(it2);
            return;
        }
        //// b 中没有 → 直接在 a 新增
        a[x+tag] = y;
        it2 = b.lower_bound(x-tag);
        if (it2 != b.begin()) {
            --it2;
            q.push({x+tag-it2->first, it2->first});
        }
    }
    void sub(int x, int y) {
        auto it = a.find(x+tag), it2 = b.find(x-tag);
        if (it2 != b.end()) { b[x-tag] += y; return; }
        if (it != a.end()) {
            if (it->second > y) { a[x+tag] -= y; return; }
            if (it->second == y) {
                auto r = it; ++r;
                if (r != a.end()) {
                    auto l = b.lower_bound(x-tag);
                    if (l != b.begin()) {
                        --l;
                        q.push({r->first-l->first, l->first});
                    }
                }
                a.erase(it);
                return;
            }
            b[x-tag] = y - it->second;
            auto r = it; ++r;
            if (r != a.end()) q.push({r->first-(x-tag), x-tag});
            a.erase(it);
            return;
        }
        b[x-tag] = y;
        it = a.lower_bound(x+tag);
        if (it != a.end()) q.push({it->first-(x-tag), x-tag});
    }
    void move(int x) {
        tag += x;//惰性平移所有坐标
        while (!q.empty()) {
            auto t = q.top();
            if (t.dis > tag*2) break; q.pop();
            auto it = b.find(t.l), it2 = a.find(t.l+t.dis);
            if (it == b.end() || it2 == a.end()) continue;
            if (it->second > it2->second) {
                b[t.l] -= it2->second;
                auto r = it2; ++r;
                if (r != a.end()) q.push({r->first-t.l,t.l});
                a.erase(it2);
            } else if (it->second < it2->second) {
                a[t.l+t.dis] -= it->second;
                if (it != b.begin()) {
                    auto l = it; --l;
                    q.push({t.l+t.dis-l->first, l->first});
                }
                b.erase(it);
            } else {
                b.erase(it); a.erase(it2);
                it = b.lower_bound(t.l); it2 = a.lower_bound(t.l+t.dis);
                if (it != b.begin() && it2 != a.end()) {
                    --it;
                    q.push({it2->first-it->first, it->first});
                }
            }
        }
    }
    int query(int x) {
        int res = 0;
        auto it = b.find(x-tag);
        if (it != b.end()) res = it->second;
        it = a.find(x+tag+1);
        if (it != a.end()) res = max(res, it->second);
        return res;
    }
    int get() {
        int res = 0, sum = 0;
        vector<ii> x;
        for (auto [fst, snd] : a)
            x.emplace_back(fst-tag, snd);
        for (auto [fst, snd] : b)
            x.emplace_back(fst+tag, -snd);
        ranges::sort(x);
        for (auto val: x | views::values) res = max(res, sum += val);
        return res;
    }
} f[N];

void merge(node &a, node &b) {
    //小合并到大
    if (a.a.size()+a.b.size() < b.a.size()+b.b.size()) swap(a,b);
    for (auto [fst, snd] : b.a) a.add(fst-b.tag,snd);//还原 b 的 a 真实坐标后并入
    for (auto [fst, snd] : b.b) a.sub(fst+b.tag,snd);//还原 b 的 b 真实坐标后并入
    priority_queue<ad> tmp;
    swap(tmp, b.q);//丢弃 b 的堆（已经用掉了）
}

int fa[N];
vector<ii> fh[N];
void dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u]) continue;
        fa[v] = u; dfs(v);
        f[v].move(w[i]-1);// 子节点容器沿带权边"平移/耗尽资源"
        merge(f[u], f[v]);// 启发式合并进父
    }
    //处理 u 自己点上的请求
    for (int i = 0; i < fh[u].size(); i++)
        fh[u][i].second -= f[u].query(fh[u][i].first);//看现有资源能否覆盖，先扣掉
    f[u].move(1);
    for (auto [fst, snd] : fh[u]) if (snd > 0)
        f[u].add(fst, snd), f[u].sub(fst+1,snd);//无法覆盖的余量加入容器
}

int n, m, d, ff, p;
int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v, c; i < n; i++) {
        cin >> u >> v >> c; c <<= 1;
        add(u, v, c); add(v, u, c);
    }
    cin >> m;
    while (m--) {
        cin >> d >> ff >> p;
        fh[p].emplace_back(d*2, ff);
    }
    dfs(1);
    cout << f[1].get() << '\n';
    return 0;
}