//
// Created by Psy.C on 2026/4/16.
//
/**
seed是哈希种子值
N是最大节点数
val数组存储每棵树的哈希值
ms是multiset容器，存储哈希值
siz[N]：子树大小数组
used[N]：标记节点是否被使用
vis[N]：标记节点是否被访问
v[N]：邻接表，存储图的结构

计算以x为根的子树大小
标记节点x为已使用
计算每个节点作为重心时的最大子树大小
f1和f2存储最小和第二小的重心
计算以x为根的子树的哈希值
递归计算所有子树的哈希值
排序后用多项式哈希公式计算
对于单重心树，返回以重心为根的哈希值
对于双重心树，分别计算两个重心的哈希值，合并

读入图的边
对每个连通分量计算哈希值
将所有连通分量的哈希值合并成整体哈希值
计算删除每个节点后的剩余部分的哈希值
检查是否与目标树匹配
如果存在孤立节点（top==2表示只有两个连通分量，其中一个为空）
尝试将孤立节点与其他节点连接
检查是否能形成同构树
 */
#include <bits/stdc++.h>
#define ull unsigned long long
#define seed 11333333
using namespace std;
constexpr int N = 105;

int n;
ull val[N];
multiset<ull> ms;
multiset<ull>::iterator it;
struct node {
    int siz[N]{}, used[N]{}, vis[N]{};
    vector<int> v[N];
    void dfs1(int x, int y) {
        siz[x] = 1; used[x] = 1;
        for (int i = 0, t; i < v[x].size(); ++i)
            if ((t=v[x][i]) != y && !vis[t])
                dfs1(t, x), siz[x] += siz[t];
    }
    int f[N]{}, sum{}, f1{}, f2{};
    void dfs2(int x, int y) {
        f[x] = sum - siz[x];
        for (int i = 0, t; i < v[x].size(); ++i)
            if ((t=v[x][i]) != y && !vis[t])
                dfs2(t, x), f[x] = max(f[x], siz[t]);
        if (f[x] < f[f1]) f1 = x;
        else if (f[x] < f[f2]) f2 = x;
    }
    vector<ull> v1[N];
    ull dfs3(int x, int y) {
        v1[x].clear();
        for (int i = 0, t; i < v[x].size(); ++i)
            if ((t=v[x][i]) != y && !vis[t])
                v1[x].push_back(dfs3(t, x));
        ranges::sort(v1[x]);
        ull ret = 1;
        for (ull i : v1[x]) ret = ret*seed+i;
        return ret;
    }
    ull calc(int x) {
        f1 = f2 = 0; f[0] = 1<<30; dfs1(x, 0);
        sum = siz[x]; dfs2(x, 0);
        if (f[f1] != f[f2]) return dfs3(f1, 0);
        ull t1 = dfs3(f1, f2), t2 = dfs3(f2, f1);
        if (t1 > t2) swap(t1, t2);
        return t1*seed + t2;
    }
    int m{}, id{}, top{};
    ull st[N]{};
    void init(int x) {
        scanf("%d", &m); id = x;
        for (int i = 1; i <= n; ++i) v[i].clear();
        for (int i = 1, a, b; i <= m; ++i) {
            cin >> a >> b; v[a].push_back(b); v[b].push_back(a);
        }
        memset(used, 0, sizeof(used)); top = 0;
        for (int i = 1; i <= n; ++i)
            if (!used[i]) st[++top] = calc(i);
        sort(st + 1, st + top + 1);
        val[id] = 0;
        for (int i = 2; i <= top; ++i)
            val[id] = val[id]*seed + st[i];
    }
    int check() {
        ms.clear();
        for (int i = 1; i <= n; ++i) {
            vis[i] = 1; top = 0;
            for (int j : v[i]) st[++top] = calc(j);
            vis[i] = 0;
            ull t = 0; sort(st + 1, st + top + 1);
            for (int j = 1; j <= top; ++j) t = t*seed + st[j];
            ms.insert(t);
        }
        for (int i = 1; i <= n; ++i)
            if (i != id) {
                if ((it=ms.find(val[i])) == ms.end()) return 0;
                ms.erase(it);
            }
        return 1;
    }
    void print() const {
        puts("YES");
        for (int i = 1; i <= n; ++i)
            for (int j = 0, t; j < v[i].size(); ++j)
                if ((t=v[i][j]) < i)
                    printf("%d %d\n", t, i);
    }
} tr[N];

void out() {
    scanf("%d%*d", &n);
    for (int i = 1; i <= n; ++i) tr[i].init(i);
    for (int i = 1; i <= n; ++i)
        if (tr[i].top == 2) {
            for (int j = 1; j <= n; ++j)
                if (tr[i].v[j].empty()) {
                    for (int k = 1; k <= n; ++k)
                        if (k != j) {
                            tr[i].v[k].push_back(j);
                            tr[i].v[j].push_back(k);
                            if (tr[i].check()) {
                                tr[i].print();
                                return;
                            }
                            tr[i].v[k].pop_back();
                            tr[i].v[j].pop_back();
                        }
                }
            break;
        }
    puts("NO");
}

int q;
int main() {
    scanf("%d", &q);
    while (q--) out();
    return 0;
}