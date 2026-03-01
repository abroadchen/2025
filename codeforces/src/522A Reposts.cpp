//
// Created by Psy.C on 2026/3/1.
//
/**
x, y为节点名称，s为连接词（通常是"is"）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 207;
vector<int> e[N];///节点i的所有邻接节点
void add(const int u, const int v) {
    e[u].push_back(v);
    e[v].push_back(u);
}

int n;///当前分配的节点编号
map<string, int> mp;///字符串名称映射到唯一的整数ID
void init() {
    mp.clear();
    for (auto& i : e) i.clear();//清空所有邻接表
    n = 0;
}

///将字符串转换为小写
void get(string& s) {
    int len = s.length();
    for (int i = 0; i < len; ++i)
        if (isupper(s[i]))
            s[i] = (char)(s[i] + 32);
}

int dp[N];//以节点i为根的子树的最大深度
void dfs(const int u, const int p) {//以节点u为根的子树的最大深度
    dp[u] = 1;//当前节点的深度为1
    for (int i = 0; i < e[u].size(); ++i) {
        const int v = e[u][i];
        if (v == p) continue;
        dfs(v, u);
        dp[u] = max(dp[u], dp[v] + 1);
    }
}

int m, b;
string str = "polycarp";
int main() {
    fast;
    cin >> m; init();
    string x, y, s;
    while (m--) {
        cin >> x >> s >> y;
        get(x), get(y);//节点名称转为小写
        if (!mp[x]) mp[x] = ++n;//未分配ID，则分配新ID
        if (!mp[y]) mp[y] = ++n;
        add(mp[x], mp[y]);//添加边到图中
    }
    b = mp[str]; dfs(b, -1);//以"polycarp"为根进行DFS，-1表示没有父节点
    cout << dp[b] << '\n';//"polycarp"子树的最大深度
    return 0;
}