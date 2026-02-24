//
// Created by Psy.C on 2026/2/24.
//
/**
{相邻节点, 边的编号}

a*(a-1)/2*b：从a个节点中选2个，再从b个节点中选1个的组合数
b*(b-1)/2.*a：从b个节点中选2个，再从a个节点中选1个的组合数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 100001;

vector<ii> g[N];
int cnt[N];//以第i条边为根的子树中节点的数量
int dfs(const int u, const int fa) {
    int tot = 0;//累计子树节点数
    for (int i = 0; i < g[u].size(); ++i) {
        const int v = g[u][i].first, id = g[u][i].second;
        if (v == fa) continue;
        cnt[id] = dfs(v, u);//递归计算以边id为根的子树大小
        tot += cnt[id];//累加所有子树的节点数
    }
    return tot + 1;//包括当前节点本身
}

int n;
double w[N], c3;
double get(const int id) {//第id条边对结果的贡献值
    const double a = cnt[id], b = n - cnt[id];
    return 2.*w[id]/c3*(a*(a-1)/2.*b+b*(b-1)/2.*a);
}

double res;
int main() {
    fast;
    cin >> n; c3 = 1.*n*(n-1)*(n-2)/6; res = 0;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v >> w[i];
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    const int m = dfs(1, 0);//每条边对应的子树大小
    for (int i = 1; i < m; ++i) res += get(i);
    int q; cin >> q;
    while (q--) {
        int x; double y;
        cin >> x >> y;//要修改的边编号x和新的权重y
        res -= get(x);//减去该边原来的贡献值
        w[x] = y;//更新边的权重
        res += get(x);//加上该边新的贡献值
        printf("%.9lf\n", res);
    }
    return 0;
}