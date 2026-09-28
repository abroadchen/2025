//
// Created by Psy.C on 2026/9/28.
//
/**
按分隔符 sep 拆分字符串。
技巧：stringstream ss(str+sep) 在源串末尾追加一个分隔符，这样 getline 能保证"最后一段"也能被读出来（避免因末尾无换行符而漏掉最后一段）。
例如 split("a:b:c", ':') 返回 {"a","b","c"}
cv（convert vertices）解析一个"顶点集合"格式的字符串，如 "1:3,5,7"：
split(str, ':') 得到 {"1", "3,5,7"}，取 t[1] 即 "3,5,7"。
再按 ',' 拆成 {"3","5","7"}，逐个 atoi 转成数字并 -1（把输入的 1-based 顶点号转成 0-based）。
插入 set<int> 里，保证顶点有序且去重。
返回值就是该"集合"所覆盖的顶点编号集合（0-based）
g：邻接表，存建出来的树（无向图）。N=1000 是顶点数上界
n：顶点的总数。
sum：统计所有"集合（clause/项）"的元素总数。
r[i]：i 号元素对应的若干集合，每个集合是一个 set<int>（顶点集合）。即 r[i] 是 vector< set<int> >。
idx：idx[i][v] 记录：在 r[i] 中，哪个下标 j 的集合包含了顶点 v（若没有则为 -1）。
注意这里 vector idx(n, vector(n, -1)) 依赖 C++17 CTAD 推导为 vector<vector<int>>
对每个元素 i：
读入一整串 s（形如 "1:3,5-2:7,9-..."，多个集合用 '-' 分隔）。
split(s, '-') 拆出每个集合字符串，逐个 cv(t) 转成 set<int>，push 进 r[i]。
遍历 r[i] 的每个集合 j，再遍历该集合里的每个顶点 v，记录 idx[i][v] = j（即元素 i 的集合 j 含顶点 v）。
sum += r[i].size()：累加所有集合的元素总数。
可行性检查 1：所有集合的元素数量总和必须等于 2*(n-1)，否则无解，输出 -1。
为什么是 2*(n-1)？一棵 n 个顶点的树有 n-1 条边；每条边连接两个顶点，贡献两个"顶点出现在集合中"的记录。总共就是 2*(n-1)。这个条件与树的性质吻合
建树边：对每一对顶点 (i, j)（j < i 避免重复）：
idx[i][j] = 元素 i 中含顶点 j 的集合下标；r[i][idx[i][j]] 就是"包含顶点 j 的那个集合"。
条件：元素 i 中含 j 的集合大小 + 元素 j 中含 i 的集合大小 == n。
满足则：e++；并在无向图 g 里连边 i—j。
这个条件就是本题的核心判定：若两个元素各自的"交叉集合"合起来恰好覆盖全部 n 个顶点，则说明它们之间存在一条树边。物理含义需结合原题（这类题里，"集合"代表一条连边所划分的子树顶点，两个端点各自的那份并起来覆盖全图 = 这条划分成立）
连通性检查：以顶点 0 为起点做 BFS，标记能到达的所有顶点。
目的：验证建出来的图是否连通
可行性检查 2：
con：图必须连通（BFS 能覆盖所有顶点）。
e != n-1：边的数量必须恰好是 n-1（树的边数）。
连通的 n 个顶点且有 n-1 条边 = 一棵树。两者都满足才输出答案，否则 -1
输出 n-1（边数）。
遍历邻接表 g，按 i < j 只输出一次每条无向边（避免重复），顶点号 +1 转回 1-based 输出。
格式：每行一条边 u v。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

vector<string> split(const string &str, char sep) {
    vector<string> v;
    stringstream ss(str+sep);
    string buf;
    while (getline(ss, buf, sep)) v.push_back(buf);
    return v;
}

set<int> cv(const string& str) {
    vector<string> t = split(str, ':');
    set<int> ret;
    for (const auto& x : split(t[1], ','))
        ret.insert(atoi(x.c_str())-1);
    return ret;
}
constexpr int N = 1e3;
vector<int> g[N];

void solve() {
    int n; cin >> n;
    int sum = 0;
    vector<vector<set<int>>> r(n);
    vector idx(n, vector(n, -1));
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (const string& t : split(s, '-')) r[i].push_back(cv(t));
        for (int j = 0; j < r[i].size(); ++j)
            for (int v : r[i][j]) idx[i][v] = j;
        sum += r[i].size();
    }
    if (sum != 2*(n-1)) { cout << "-1\n"; return; }
    int e = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (r[i][idx[i][j]].size() + r[j][idx[j][i]].size() == n) {
                ++e;
                g[i].push_back(j); g[j].push_back(i);
            }
        }
    }
    vector<bool> vis(n); vis[0] = true;
    queue<int> q; q.push(0);
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i : g[now]) {
            if (!vis[i]) { vis[i] = true; q.push(i); }
        }
    }
    bool con = true;
    for (int i = 0; i < n; ++i)
        if (!vis[i]) con = false;
    if (!con || e != n-1) { cout << "-1\n"; return; }
    cout << n-1 << '\n';
    for (int i = 0; i < n; ++i)
        for (int j : g[i])
            if (i < j) cout << i+1 << ' ' << j+1 << '\n';
}


int main() {
    fast;
    solve();
    return 0;
}