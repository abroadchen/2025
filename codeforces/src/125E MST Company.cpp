//
// Created by Psy.C on 2025/11/17.
//
/*
*N = 5005：最大节点数
M = 100005：最大边数
n, m, k：节点数、边数、特殊要求
val[M]：边的权重数组
fa[N]：并查集父节点数组
ryz：调节参数（用于处理相等权重的情况）
*node结构体表示边：起点x、终点y、权重z、边的编号id
重载<运算符按权重排序
v1：与节点1相关的边
v2：与其他节点相关的边
res：结果边的编号集合
 *
*t1, t2：两个向量的指针
tt：已选边数
vv：从v1中选择的边数
合并两个已排序的向量，但v1中的权重加上x后再比较
特殊处理权重相等的情况（使用ryz参数）
*使用并查集避免环路（Kruskal算法思想）
记录选中的边
更新并查集
*如果不能形成生成树，输出-1并退出
返回从v1中选择的边数
 */
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

const int N = 5005, M = 1e5+5;
int n, m, k, val[M], fa[N], ryz;
struct node {
    int x, y, z, id;
    bool operator<(const node& x) const {
        return z < x.z;
    }
};
vector<node> v1, v2;
vector<int> res;

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int get(int x) {
    res.clear();
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int t1(0), t2(0), tt(0), vv(0);
    for (int i = 1; i <= m; ++i) {
        node a; int vis = 0;
        if ((t1 < v1.size() && t2 < v2.size() && v1[t1].z + x < v2[t2].z) ||
            t2 == v2.size()) a = v1[t1++], vis = 1;
        else if ((t1 < v1.size() && t2 < v2.size() &&
            v1[t1].z + x == v2[t2].z) && ryz) a = v1[t1++], vis = 1, ryz--;
        else a = v2[t2++];
        if (find(a.x) == find(a.y)) continue;
        res.push_back(a.id);
        a.x = find(a.x), a.y = find(a.y);
        tt++; vv += vis;
        fa[a.x] = a.y;
    }
    if (tt != n - 1) puts("-1"), exit(0);
    return vv;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for (int i = 1, a, b, c; i <= m; ++i) {
        cin >> a >> b >> c; val[i] = c;
        if (a == 1 || b == 1) v1.push_back({a, b, c, i});
        else v2.push_back({a, b, c, i});
    }
    sort(v1.begin(), v1.end()); sort(v2.begin(), v2.end());
    if ((k == 0 && n > 1) || v1.size() < k) return puts("-1"), 0;
    int l = -1e6, r = 1e6, ans;
    if (get(1e6) > k) return puts("-1"), 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (get(mid) <= k) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    if (get(ans) == k) {//如果直接找到解，输出结果
        cout << n - 1 << '\n';
        for (int i = 0; i < res.size(); ++i) cout << res[i] << ' ';
        puts("");
        return 0;
    }
    l = 0, r = 1e6;
    while (l <= r) {
        int mid = l + r >> 1; ryz = mid;
        int w;
        if ((w = get(ans)) == k) {
            cout << n - 1 << '\n';
            for (int i = 0; i < res.size(); ++i) cout << res[i] << ' ';
            puts("");
            return 0;
        }
        if (w < k) l = mid + 1;
        else r = mid - 1;
    }
    return 0;
}