//
// Created by Psy.C on 2025/12/13.
//
/*
*st: 起点
to: 终点
cp: 容量(capacity)
fl: 流量(flow)
w: 费用(weight/cost)
*n: 节点数
m: 边数
e: 所有边的集合
g[N]: 邻接表，g[i]存储从节点i出发的边的索引
q[N]: SPFA算法中的队列标记数组
d[N]: 最短距离数组
p[N]: 前驱边数组
a[N]: 可行流数组
 *
*num: 统计字符串s中各字符出现次数
mp: 存储每个单词中各字符出现次数
a: 存储每个单词的价值
 *
*节点0为源点，节点(n+26+1)为汇点
字符节点：1-26
单词节点：27-(n+26)
从源点向各字符连边，容量为该字符需求量，费用0
从字符向包含该字符的单词连边，容量为单词中该字符数量，费用为单词索引
从单词向汇点连边，容量为单词可用次数，费用0
 *
 *如果最大流等于字符串长度，说明可以完全重构，输出最小费用
 */
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
#define inf 0x3f3f3f3f
using namespace std;

struct edge {
    int st, to, cp, fl, w;
    edge(const int st, const int to, const int cp, const int fl, const int w) :
        st(st), to(to), cp(cp), fl(fl), w(w) {}
};

struct node {
    int n{}, m{};
    vector<edge> e;
    vector<int> g[N];
    int q[N]{}, d[N]{}, p[N]{}, a[N]{};
    void init(const int x) {//设置节点数并清空边和邻接表
        this->n = x;
        for (int i = 0; i <= n; ++i) g[i].clear();
        e.clear();
    }
    void add(int st, int to, int cp, int w) {
        e.emplace_back(st, to, cp, 0, w);
        e.emplace_back(to, st, 0, 0, -w);
        m = static_cast<int>(e.size());
        g[st].emplace_back(m - 2);
        g[to].emplace_back(m - 1);
    }
    bool spfa(const int s, const int t, int& fl, int& w) {
        for (int i = 1; i <= n; ++i) d[i] = inf;
        memset(q, 0, sizeof(q));
        d[s] = 0, q[s] = 1, p[s] = 0;
        queue<int> pq; a[s] = inf; pq.push(s);
        while (!pq.empty()) {
            const int u = pq.front(); pq.pop(); q[u] = 0;
            for (int i = 0; i < g[u].size(); ++i) {
                edge& v = e[g[u][i]];
                if (v.cp > v.fl && d[v.to] > d[u] + v.w) {
                    d[v.to] = d[u] + v.w;
                    p[v.to] = g[u][i];//记录前驱边和可行流量
                    a[v.to] = min(a[u], v.cp - v.fl);
                    if (!q[v.to]) { pq.push(v.to); q[v.to] = 1; }
                }
            }
        }
        if (d[t] == inf) return false;//无法到达汇点
        fl += a[t]; w += d[t] * a[t];//更新总流量和总费用
        for (int u = t; u != s; u = e[p[u]].st) {//沿着增广路径更新流量
            e[p[u]].fl += a[t];
            e[p[u] ^ 1].fl -= a[t];
        }
        return true;
    }
    int solve(const int s, const int t, int& w) {
        int fl = 0; w = 0;
        while (spfa(s, t, fl, w)) {}//反复调用SPFA直到找不到增广路径
        return fl;
    }
} mc;

int main() {
    fast;
    string s; cin >> s;
    int n; cin >> n;
    map<int, int> num;
    vector<map<int, int> > mp(n + 1);
    vector<int> a(n + 1);
    for (const char i : s) num[i - 'a' + 1]++;//目标字符串中各字符频次
    for (int i = 1; i <= n; ++i) {
        string t;//读入每个单词及其价值，并统计各单词中字符频次
        cin >> t >> a[i];
        for (const char j : t) mp[i][j - 'a' + 1]++;
    }
    const int st = 0, t = n + 26 + 1; mc.init(t);
    for (int i = 1; i <= 26; ++i) {//遍历每个字符
        if (!num[i]) continue;//目标字符串不需要字符i
        mc.add(st, i, num[i], 0);//从源点到字符i，容量为需求量
        for (int j = 1; j <= n; ++j) {//遍历每个单词
            if (!mp[j][i]) continue;//第j个单词不包含字符i
            mc.add(i, j + 26, mp[j][i], j);//从字符i到单词j，容量为单词中字符i的数量
        }
    }
    for (int i = 1; i <= n; ++i) mc.add(i + 26, t, a[i], 0);
    int mn;
    const int mx = mc.solve(st, t, mn);
    if (mx == s.size()) cout << mn << '\n'; else cout << -1 << '\n';
    return 0;
}