//
// Created by Psy.C on 2025/11/7.
//
/*
*读取节点数量n。
初始化根节点root为-1（表示尚未找到）。
创建大小为n的数组a，存储每个节点的权值。
创建大小为n的二维数组adj，表示树的邻接表（每个节点的子节点列表）
*遍历所有节点，读取每个节点的父节点pr和权值a[i]。
如果pr不等于-1，说明不是根节点，将pr减1（转换为0索引），然后将当前节点i添加到父节点pr的子节点列表中。
如果pr等于-1，说明这是根节点，记录root为当前节点i
*遍历所有节点，如果某个节点有子节点（非叶子节点）：
比较其两个子节点的权值，如果第一个子节点权值大于第二个，则交换它们的位置。
这样确保每个非叶子节点的左子节点权值小于等于右子节点权值
 *
*创建大小为n的数组mn和mx，分别存储每个节点子树中的最小值和最大值。
创建pair向量vv，用于存储区间信息
 *
*定义并调用递归lambda函数pre进行前序遍历：
如果是叶子节点：设置该节点的最小值和最大值都为自身权值，并将(起始值, 节点编号)加入vv向量。
如果是非叶子节点：递归处理左子树(起始值不变)和右子树(起始值为当前节点权值+1)。
更新当前节点的最小值为左子树最小值，最大值为右子树最大值
 *
*定义并调用递归lambda函数dfs进行深度优先搜索：
如果是叶子节点：计算平均值 sum/c 并存储在f[v]中。
如果是非叶子节点：递归处理左右子树，传递更新后的sum和c值
 *
*读取查询值x。
使用lower_bound在vv中查找第一个大于等于(x+1, 0)的元素，然后向前移动一位(--操作)。
输出对应节点的计算结果f[it->second]
 *
 *-- 小于 make_pair(x + 1, 0) 的元素位置
*访问左子节点时，包含右子树的最小值
访问右子节点时，包含左子树的最大值
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);

    int n; cin>>n;
    int root = -1;
    vector<int> a(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        int pr; cin >> pr >> a[i];
        if (pr != -1) { --pr; adj[pr].emplace_back(i); }
        else root = i;
    }
    for (int i = 0; i < n; ++i) {
        if (!adj[i].empty()) {
            if (a[adj[i][0]] > a[adj[i][1]]) swap(adj[i][0], adj[i][1]);
        }
    }
    vector<int> mn(n), mx(n);
    vector<pair<int, int>> vv;

    auto pre = [&](auto&& self, int v, int st) {
        if (adj[v].empty()) {
            mn[v] = mx[v] = a[v];
            vv.emplace_back(st, v);
            return;
        }
        self(self, adj[v][0], st);
        self(self, adj[v][1], a[v] + 1);
        mn[v] = mn[adj[v][0]];
        mx[v] = mx[adj[v][1]];
    };
    pre(pre, root, 0);

    vector<double> f(n);
    auto dfs = [&](auto&& self, int v, ll sum, int c) {
        if (adj[v].empty()) { f[v] = sum / (1. * c); return; }
        self(self, adj[v][0], sum + mn[adj[v][1]], c + 1);
        self(self, adj[v][1], sum + mx[adj[v][0]], c + 1);
    };
    dfs(dfs, root, 0, 0);

    int q; cin>>q;
    while (q--) {
        int x; cin>>x;
        auto it = --lower_bound(vv.begin(), vv.end(), make_pair(x + 1, 0));
        cout << f[it->second] << '\n';
    }
    return 0;
}