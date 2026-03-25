//
// Created by Psy.C on 2026/3/24.
//
/**
N: 最大数组大小
n: 数组长度
a[N]: 输入数组
vis[N]: 访问标记数组
cnt: 连通分量计数
id[N]: 临时ID数组
ans[N]: 结果数组
v[N]: 每个连通分量的节点集合

寻找所有环结构（连通分量）
从每个未访问的节点开始DFS，找到整个环
do-while循环：沿着路径走直到回到起点
v[cnt]存储第cnt个环的所有节点
按环的大小从小到大排序

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define vi vector<int>
using namespace std;
constexpr int N = 1e6+5;
int n, a[N], vis[N], cnt, id[N], ans[N];
vi v[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) if (vis[i] != 1) {
        int x = i; ++cnt;
        do {
            vis[x] = 1;
            v[cnt].push_back(x);
            x = a[x];
        } while (x != i);
    }
    sort(v + 1, v + 1 + cnt, [](const vi& x, const vi& y) {
        return x.size() < y.size();
    });
    for (int i = 1; i <= cnt; ++i) {
        int sz = v[i].size();
        if (sz&1) {
            for (int k = 0; k < sz; ++k)
                id[k*2%sz] = v[i][k];//重新排列节点
            for (int k = 0; k < sz; ++k)
                ans[id[k]] = id[(k+1)%sz];//重新连接
        } else if (sz == v[i+1].size()) {//偶数长度环且有配对
            for (int k = 0; k < sz; ++k) {
                ans[v[i][k]] = v[i+1][k];//第i个环指向第i+1个环
                ans[v[i+1][k]] = v[i][(k+1)%sz];//第i+1个环指回第i个环的下一个
            }
            i++;//跳过下一个环，因为它已被配对
        } else return puts("-1"), 0;
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}