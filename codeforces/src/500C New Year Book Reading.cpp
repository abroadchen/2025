//
// Created by Psy.C on 2026/2/24.
//
/**
n：物品数量
m：操作次数
w[N]：存储每个物品的权重值
d[M]：存储操作序列 物品编号

外层循环遍历所有操作
内层循环遍历当前向量v中的所有元素
如果找到与当前操作相同的物品编号：
v.erase(v.begin() + j)：删除当前位置的元素
v.insert(v.begin(), d[i])：将该元素插入到向量开头（实现了类似LRU缓存的功能）
break：跳出内层循环
如果当前元素不是目标元素，则累加其权重值到答案中
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 501, M = 1001;
int n, m, w[N], d[M];
bool vis[N];
vector<int> v;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= m; ++i) {
        cin >> d[i];
        if (!vis[d[i]]) {
            vis[d[i]] = true;
            v.push_back(d[i]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j < v.size(); ++j) {
            if (d[i] == v[j]) {
                v.erase(v.begin() + j);
                v.insert(v.begin(), d[i]);
                break;
            }
            ans += w[v[j]];
        }
    cout << ans << '\n';
    return 0;
}