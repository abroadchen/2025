//
// Created by Psy.C on 2026/3/28.
//
/**
siz[x]: 以x为根的子树中，在当前二分条件下能达到的最大路径长度
all[x]: 以x为根的子树的总节点数
a[N]: 每个节点的值
mid: 二分查找的当前中间值
ans: 当前找到的最大路径长度
v[N]: 邻接表表示树的边
初始化当前节点的值，mx表示子树中最长路径，y表示第二长路径
递归处理所有子节点
all[x]累加子树节点数
如果子树全部可用(siz[v[x][i]] == all[v[x][i]])，则整个子树都可以加入路径
否则更新最长和次长路径
将最长子路径加到当前节点
如果当前节点值小于中位数，则不能使用该节点，置siz[x] = 0
更新全局最大路径长度（当前路径+次长路径）
以p为根执行DFS，检查是否存在长度≥k的符合条件路径
在所有可能的值范围内二分查找
找到最大的满足条件的中位数值
以最小值所在节点为根进行搜索
O(n log n log V), where V is the value range
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, inf = 1e9+7;

int siz[N], all[N], a[N], mid, ans;
vector<int> v[N];
void dfs(int x, int fa) {
    siz[x] = all[x] = 1;
    int mx = 0, y = 0;
    for (int i = 0; i < v[x].size(); ++i)
        if (v[x][i] != fa) {
            dfs(v[x][i], x);
            all[x] += all[v[x][i]];
            if (siz[v[x][i]] == all[v[x][i]])
                siz[x] += siz[v[x][i]];
            else {
                if (siz[v[x][i]] > mx) swap(mx, siz[v[x][i]]);
                if (siz[v[x][i]] > y) swap(y, siz[v[x][i]]);
            }
        }
    siz[x] += mx;
    if (a[x] < mid) siz[x] = 0;
    ans = max(ans, siz[x] + y);
}

int p, k;
bool check() {
    ans = 0; dfs(p, 0);
    if (ans >= k) return true;
    return false;
}

int n;
int main() {
    fast;
    cin >> n >> k;
    int mn = inf, i, x, y;
    for (i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] < mn) mn = a[i], p = i;
    }
    for (i = 1; i < n; ++i) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
    }
    int l = 1, r = 1e6+9;
    while (r - l > 1) {
        mid = (l + r) >> 1;
        if (check()) l = mid; else r = mid;
    }
    cout << l;
    return 0;
}