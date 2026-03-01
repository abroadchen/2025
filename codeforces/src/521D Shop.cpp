//
// Created by Psy.C on 2026/3/1.
//
/**
数组长度 n，操作数 m，选择数量 k
a[N]：原始数组
c[N]：记录每种类型1操作的最优ID 每个位置的最佳操作
v[N]：为每个位置存储操作2的列表
p：存储所有待排序的节点
ans[4]：按类型分类存储选中的操作ID

类型1操作（tp=1）：对于每个位置，保留价值最大的操作
类型2操作（tp=2）：将操作添加到对应位置的列表中
类型3操作（tp=3）：直接添加到待排序列表中（比值为 val/1）

初始值：x 设为 a[i]
类型1的增益：如果类型1操作能带来增益，则加入列表
降序排序：按增益值降序排列
计算比值：将每个操作的增益比值（新值/旧值）加入待排序列表

降序排序：按比值从大到小排序（因为是反向迭代器）
选择前k个：选择比值最大的前k个操作
按类型分类：将选中的操作按类型存入对应数组

输出总数：输出选中的操作总数
按类型输出：依次输出类型1、2、3的所有选中操作ID


!c[g[i].x]：如果位置g[i].x还没有记录操作
g[c[g[i].x]].val < g[i].val：或者当前位置已有的操作价值小于当前操作
c[g[i].x] = i：更新位置g[i].x的最佳操作ID为i
if (g[i].tp == 2)：如果是类型2操作
v[g[i].x].push_back({g[i].val, i})：将{值, ID}对添加到位置g[i].x的向量中
else：如果是类型3操作
p.push_back({{g[i].val, 1}, i})：创建node2对象并添加到p中
{{g[i].val, 1}：创建node对象，x=g[i].val, y=1
i：操作ID

if (c[i] && g[c[i]].val > x)：如果位置i有最佳操作且该操作值大于当前位置值
v[i].push_back({g[c[i]].val-x, c[i]})：添加增益值和操作ID到向量中
v[i].rbegin()：反向迭代器，指向向量末尾
v[i].rend()：反向迭代器，指向向量开头
效果：将向量按降序排序（从大到小）
for (int j = 0; j < v[i].size(); ++j)：遍历位置i的所有操作
p.push_back({{x+v[i][j].first, x}, v[i][j].second})：
创建node对象：x+v[i][j].first（新值）和x（旧值）
第二个参数是操作ID
x += v[i][j].first：更新当前值

p.rbegin()：反向迭代器，指向向量末尾
p.rend()：反向迭代器，指向向量开头
由于node的比较是基于x/y的，这会按效益比降序排列

i < k && i < p.size()：确保不超过k个且不超过p的大小
g[p[i].id].tp：获取操作p[i].id的类型
ans[g[p[i].id].tp].push_back(p[i].id)：将操作ID添加到对应类型的答案向量中

输出三种类型选中操作的总数量
for (int x = 1; x <= 3; ++x)：遍历类型1、2、3
for (int i = 0; i < ans[x].size(); ++i)：遍历每个类型的答案
cout << ans[x][i] << ' '：输出每个操作的ID
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ld long double
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+1;

struct node {
    ll x, y;
    bool operator<(const node& o) const {
        return (ld)x/y < (ld)o.x/o.y;
    }
};
struct node2 {
    node f; int id;
    bool operator<(const node2& o) const {
        return f < o.f;
    }
};
///tp 类型，x 位置，val 值
struct node3 { int tp, x, val; } g[N];

int n, m, k, a[N], c[N];
vector<ii> v[N];///为每个位置存储一对整数的动态数组
vector<node2> p;///所有待排序的元素
vector<int> ans[4];
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) {
        cin >> g[i].tp >> g[i].x >> g[i].val;
        if (g[i].tp == 1) {
            if (!c[g[i].x] || g[c[g[i].x]].val < g[i].val)
                c[g[i].x] = i;
        } else {
            if (g[i].tp == 2)
                v[g[i].x].emplace_back(g[i].val, i);
            else
                p.push_back({{g[i].val, 1}, i});
        }
    }
    for (int i = 1; i <= n; ++i) {
        ll x = a[i];
        if (c[i] && g[c[i]].val > x)
            v[i].emplace_back(g[c[i]].val-x, c[i]);
        sort(v[i].rbegin(), v[i].rend());
        for (auto &[fst, snd] : v[i]) {
            p.push_back({{x+fst, x}, snd});
            x += fst;
        }
    }
    sort(p.rbegin(), p.rend());
    for (int i = 0; i < k && i < p.size(); ++i)
        ans[g[p[i].id].tp].push_back(p[i].id);
    cout << ans[1].size()+ans[2].size()+ans[3].size() << '\n';
    for (int x = 1; x <= 3; ++x)
        for (const int i : ans[x])
            cout << i << ' ';
    return 0;
}