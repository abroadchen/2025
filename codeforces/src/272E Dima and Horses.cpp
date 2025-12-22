//
// Created by Psy.C on 2025/12/22.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 300010
using namespace std;

vector<int> g[N]; bool c[N];
void dfs(const int x) {//当前节点编号
    int ans = 0;//与当前节点颜色相同的邻居数量
    for (const int i : g[x]) if (c[x] == c[i]) ans++;
    if (ans >= 2) {
        c[x] ^= 1;//翻转当前节点的颜色 翻转操作本质上是在最大化某种目标函数或最小化违反约束的数量
        for (const int i : g[x]) if (c[i] == c[x]) dfs(i);//对于所有与当前节点颜色相同的邻居，递归调用dfs函数
    }
}


int main() {
    fast;
    int n, m; cin>>n>>m;
    for (int i = 1, x, y; i <= m; ++i) {
        cin>>x>>y;
        g[x].push_back(y); g[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) dfs(i);
    for (int i = 1; i <= n; ++i) cout<<c[i];
    cout<<'\n';
    return 0;
}