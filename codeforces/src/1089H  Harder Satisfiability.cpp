//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
读 n（变量数）、m（关系数）、字符串 s（每个变量的标签，E / A，后面用）。
对每对 (x, y) 做解析化：负数做 n - x 的取正、转 0-based、并把两者排序
变量范围 [0, n) 和其取反 [n, 2n)，get 把下标翻到另一半（即取反节点）。
对每个关系 (fr, to) 建两条蕴含边：¬fr → to 和 ¬to → fr。这是标准 2-SAT 的建边方式
标准 Tarjan，给每个节点标上所属 SCC 编号 scc[x]，cc 是 SCC 总数。
对图中所有节点跑一遍
若变量 i 与它的取反 i+n 都在同一个 SCC，则矛盾，直接返回 FALSE（不可满足）
对标签为 E 的变量：把它的两个取值节点所在 SCC 都标为 no（禁止）。
对标签 A 的变量：若任一侧已在 no 中则返回 FALSE
重置所有 no，然后对标签 A 的变量：x 和 ¬x 两个分量都会被设为禁止，且若有重复/冲突则返回 FALSE。即 A 变量两个方向都"必须/被占用"。
E 和 A 在此处理成两类强制"禁止节点"的选择。
在 SCC 的 DAG 上，如果某个分量的后继（可达的）已 ok 或 no，则把当前设 ok。
若一个分量既 ok 又 no，则矛盾返回 FALSE。
这是一种依赖/逃逸检查：判断是否存在"必须满足又必须禁止"的冲突
对每组输出 TRUE/FALSE。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define vi vector<int>
using namespace std;

bool solve() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vi fr(m), to(m);
    rep(i,m) {
        int x, y; cin >> x >> y;
        if (x < 0) x = n - x;
        if (y < 0) y = n - y;
        --x, --y; fr[i] = x; to[i] = y;
        if (fr[i] > to[i]) swap(fr[i], to[i]);
    }
    auto get = [&](int x) { return x >= n ? x - n : x + n; };
    vector<vi> e(n<<1);
    rep(i,m) { e[get(fr[i])].push_back(to[i]); e[get(to[i])].push_back(fr[i]); }
    vi dfn(n<<1,-1), low(n<<1,-1), scc(n<<1,-1);
    stack<int> st;
    int cc = 0, tim = 0;
    function<void(int)> tarjan = [&](int x) {
        dfn[x] = low[x] = ++tim; st.push(x);
        for (auto y : e[x]) {
            if (!~dfn[y]) { tarjan(y); low[x] = min(low[x], low[y]); }
            else if (!~scc[y]) low[x] = min(low[x], dfn[y]);
        }
        if (dfn[x] == low[x]) {
            for (int t = -1; t != x; ) { t = st.top(); scc[t] = cc; st.pop(); }
            ++cc;
        }
    };
    rep(i,n<<1) if (!~dfn[i]) tarjan(i);
    rep(i,n) if (scc[i] == scc[i+n]) return 0;
    vector<bool> no(cc);
    rep(i,n) {
        if (s[i] == 'E') no[scc[i]] = no[scc[i+n]] = 1;
        else { if (no[scc[i]] || no[scc[i+n]]) return 0; }
    }
    rep(i,cc) no[i] = 0;
    rep(i,n) if (s[i] == 'A') {
        if (no[scc[i]]) return 0;
        no[scc[i]] = 1;
        if (no[scc[i+n]]) return 0;
        no[scc[i+n]] = 1;
    }
    vector<bool> ok(cc);
    vector<vi> g(cc);
    rep(x,n<<1) for (auto y : e[x]) if (scc[x] != scc[y]) g[scc[x]].push_back(scc[y]);
    rep(x,cc) {
        for (auto y : g[x]) if (ok[y] || no[y]) ok[x] = 1;
        if (ok[x] && no[x]) return 0;
    }
    return 1;
}


int main() {
    fast;
    int T; cin >> T;
    while (T--) { cout << (solve() ? "TRUE" : "FALSE") << '\n'; }
    return 0;
}