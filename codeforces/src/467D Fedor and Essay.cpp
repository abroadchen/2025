//
// Created by Psy.C on 2026/2/13.
//
///时间复杂度：O(n log k + m + k)，其中k是不同字符串的个数
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300005
using namespace std;

int k, v1[N], v2[N];
map<string, int> mp;
int get(string str) {
    for (char& i : str)
        if (i >= 'a') i = i - 'a' + 'A';//转换为大写
    if (mp[str]) return mp[str];//已存在
    mp[str] = ++k;//分配新ID
    v2[k] = str.size();//记录长度
    for (int j = 0; j < v2[k]; ++j)
        if (str[j] == 'R') v1[k]++;//统计'R'的个数
    return k;
}

int g[N];
vector<int> e[N];
void dfs(const int x) {
    g[x] = 1;//标记已访问
    for (const auto y : e[x]) {
        if (g[y]) continue;
        v1[y] = v1[x], v2[y] = v2[x];//将节点x的属性传递给所有可达节点
        dfs(y);
    }
}

int n, b[N], m, id[N];
string a[N];

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = get(a[i]);//转换为ID
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        string u, v; cin >> u >> v;
        int x = get(u);
        const int y = get(v);
        e[y].push_back(x);
    }
    for (int i = 1; i <= k; ++i) id[i] = i;//将ID存入数组id
    sort(id + 1, id + 1 + k, [](const int i, const int j) {
        return v1[i] != v1[j] ? v1[i] < v1[j] : v2[i] < v2[j];
    });
    for (int i = 1; i <= k; ++i) {
        if (g[id[i]]) continue;
        dfs(id[i]);
    }
    ll a1 = 0, a2 = 0;
    for (int i = 1; i <= n; ++i) {
        a1 += v1[b[i]];//'R'总数和长度总和
        a2 += v2[b[i]];
    }
    cout << a1 << ' ' << a2 << '\n';
    return 0;
}