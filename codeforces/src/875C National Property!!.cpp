//
// Created by Psy.C on 2026/10/6.
//
/**
求有向图的强连通分量。
dfn 访问序号、low 可达最小序、tim 时间戳、cnt SCC 计数、scc[v] 记录 v 属于第几个 SCC。
递归访问，遇到未访问子节点递归并更新 low；遇到已在栈中的用 dfn 更新 low；当 dfn[u]==low[u] 时弹栈形成一个新的 SCC。
这是后面 2-SAT 判断的基础
读入 n 个长度为 l 的序列存到 a[i]，元素范围 1..m。
n==1 时直接输出 Yes 和 0（只有一组序列恒成立
判断相邻序列的字典序关系，并构建 JSAT/.2SAT 约束：

对相邻序列 a[i-1] 和 a[i]，逐位比较直到第一个不同位置 j。
在该位置，x = a[i-1][j]（前一个序列的值），y = a[i][j]（后一个序列的值）。
若所有公共前缀都相等（flg 仍为 true）且 a[i] 比 a[i-1] 短：则后一个序列是前一个的前缀，此时必然前一个 > 后一个（字典序中前缀更长的更大），所以违反"非降序"，输出 No。
若在第一个不同位：
若 x < y（前一个序列在该位更小 → 前一个字典序更小，满足约束）：添加边 g[x]→g[y] 和 g[y+m]→g[x+m]。这里的语义是 SAT 蕴含关系：x 为真蕴含 y 为真，y 非真蕴含 x 非真。
若 x > y（前一个在该位更大 → 违反原有非降序）：要满足就需要对某个值取反（翻转），添加 g[x]→g[x+m] 和 g[y+m]→g[y]。
这里的 i 与 i+m 表示一个变量的"真/假"两个节点（2-SAT 的经典拆点：i 为真、i+m 为假或相反）。我没法 100% 确认题目到底是要"让序列非降序，通过翻转某些值来实现"还是别的变形，但 2-SAT 建边 + SCC 判断的模式非常明确。
对所有 2m 个节点跑 Tarjan。
标准的 2-SAT 判定：若同一个变量的"真/假"两个节点（i 和 i+m）在同一 SCC 中，则矛盾，输出 No
若可满足，构造一个赋值：遍历每个变量，若 scc[i] > scc[i+m]（拓扑序更后，即"真"分量更靠后），则把该变量置为"翻转/选中"，加入 v 并计数 ans。
输出 Yes、选中个数 ans 和选中的元素列表
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(a) ((int)a.size())
using namespace std;
constexpr int N = 3e5+10;

int dfn[N], low[N], tim, cnt, scc[N];
stack<int> s;
vector<int> g[N];
bool vis[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++tim; s.push(u); vis[u] = true;
    for (auto v : g[u]) {
        if (!dfn[v]) { tarjan(v); low[u] = min(low[u], low[v]); }
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++cnt;
        int v = -1;
        do {
            v = s.top(); s.pop();
            scc[v] = cnt;
            vis[v] = false;
        } while (u != v);
    }
}

vector<int> a[N];
int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1, l; i <= n; ++i) {
        cin >> l;
        for (int j = 1, x; j <= l; ++j) {
            cin >> x;
            a[i].push_back(x);
        }
    }
    if (n == 1) { cout << "Yes\n" << 0 << '\n'; return 0; }
    for (int i = 2; i <= n; ++i) {
        bool flg = true;
        for (int j = 0; j < min(sz(a[i]), sz(a[i-1])); ++j) {
            if (a[i][j] == a[i-1][j]) continue;
            flg = false;
            int x = a[i-1][j], y = a[i][j];
            if (x < y) {
                g[x].push_back(y);
                g[y+m].push_back(x+m);
            } else {
                g[x].push_back(x+m);
                g[y+m].push_back(y);
            }
            break;
        }
        if (flg && (sz(a[i]) < sz(a[i-1]))) { cout << "No\n"; return 0; }
    }
    for (int i = 1; i <= 2*m; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= m; ++i)
        if (scc[i] == scc[i+m]) { cout << "No\n"; return 0; }
    int ans = 0;
    vector<int> v;
    for (int i = 1; i <= m; ++i) {
        if (scc[i] > scc[i+m]) { ans++; v.push_back(i); }
    }
    cout << "Yes\n" << ans << '\n';
    for (auto x : v) cout << x << ' ';
    return 0;
}