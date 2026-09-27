//
// Created by Psy.C on 2026/9/27.
//
/**
数组 a 存 (值 v, 原始位置 id)。
按值升序排序 → 排序后 a[i] 是第 i 小的元素，a[i].id 是它在原数组中的位置
merge 里 hm 做按大小合并：把小的集合整体搬进大的集合。
这里用 to[x] 作"描述符"避免移动大数组，v[to[x]] 才是真实容器——合并时始终把元素少的一端并入多的一端（启发式合并，保证每个元素被移动 O(log n) 次）。
find 里先 hm(fa[x], x) 把集合合并再路径压缩，属于"合并发生在 find 之前"的写法（预处理式合并）
每个节点 i 自成一个集合，集合内容 v[i] = {i}。
关键连边：merge(a[i].id, i)。
a[i].id：第 i 小元素在原数组中的位置。
i：排序后它应填的目标位置（第 i 小的数最终应到位置 i）。
连边含义：原位置 a[i].id 与 目标位置 i 之间可以通过一次交换联动（经典 "交换两个位置的元素使序列有序" 的建模——一个位置既放原本的元素、又会被新的元素占据，故两者必须属于同一连通块才能完成局部重排）。
这种连边方式对应经典问题："给定一个排列，允许任意交换两个位置，问最少需要多少次/最少分成几个互不影响的置换环"。这里统计的是连通块个数及每块包含的位置
把所有 fa 压缩到根并排序去重，得到 q 个不同连通块。
对每个代表元 fa[i]，输出其集合 v[to[fa[i]]] 内包含的所有位置编号。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+10;

struct node { int v, id; } a[N];
inline bool cmp(node x, node y) { return x.v < y.v; }
vector<int> v[N];//存以 x 为代表元的连通块内所有节点
int to[N];//指向"代表元 x 实际存集合的那个描述符"
inline void hm(int x, int y) {
    if (v[to[x]].size() < v[to[y]].size()) swap(to[x], to[y]);
    while (!v[to[y]].empty())
        v[to[x]].push_back(v[to[y]][v[to[y]].size()-1]), v[to[y]].pop_back();
}

int fa[N];
inline int find(int x) {
    if (x == fa[x]) return x;
    hm(fa[x], x);
    return fa[x] = find(fa[x]);
}
inline void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    hm(x, y);//小集合并入大集合
    fa[x] = y;//代表元直接指向 y
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].v, a[i].id = i;
    sort(a+1, a+n+1, cmp);
    for (int i = 1; i <= n; ++i) fa[i] = i, to[i] = i, v[to[i]].push_back(i);
    for (int i = 1; i <= n; ++i) merge(a[i].id, i);
    for (int i = 1; i <= n; ++i) fa[i] = find(fa[i]);
    sort(fa+1, fa+n+1);
    int q = unique(fa+1, fa+n+1) - fa - 1;
    cout << q << '\n';
    for (int i = 1; i <= q; ++i) {
        cout << v[to[fa[i]]].size() << ' ';
        for (int j : v[to[fa[i]]]) cout << j << ' ';
        cout << '\n';
    }
    return 0;
}