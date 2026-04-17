//
// Created by Psy.C on 2026/4/16.
//
/**
node结构体包含哈希值v和两个整数x,y
a[2]存储两棵树的节点信息
n是节点数
id: 树的标识
used, vis: 标记数组
v2: 存储连通分量的哈希值
v[N]: 邻接表
sub[N]: 子树节点集合
init(): 清空并初始化

将节点x加入到以rt为根的连通分量中
递归遍历所有相邻节点
dfs1: 计算子树大小
dfs2: 找到树的重心（一个或两个）
计算以x为根的子树哈希值
使用排序确保相同结构产生相同哈希
计算连通分量哈希
读入图的边
对每个连通分量计算哈希值
计算除了当前连通分量外其他连通分量的哈希值
枚举删除每个节点后的哈希值
生成各种可能的连接方案
将哈希值重构为实际的树结构
匹配两棵树的哈希值
尝试不同的连接方式
验证同构性
 */
#include <bits/stdc++.h>
#define ull unsigned long long
#define seed 11333333
#define seed1 23333333
#define seed2 5462617
using namespace std;
constexpr int N = 1005;

struct node {
    ull v;
    int x, y;
    bool operator<(const node &o) const {
        return v < o.v;
    }
};
vector<node> a[2];
int n;
struct tree {
    int id{}, used[N]{}, vis[N]{};
    vector<ull> v2;
    vector<int> v[N], sub[N];
    void init() {
        a[id].clear();
        memset(used, 0, sizeof(used));
        memset(vis, 0, sizeof(vis));
        v2.clear();
        for (int i = 1; i <= n; ++i)
            v[i].clear(), sub[i].clear();
    }
    void get(int x, int y, int rt) {
        sub[rt].push_back(x);
        for (int i = 0, t; i < v[x].size(); ++i)
            if ((t=v[x][i]) != y)
                get(t, x, rt);
    }
    int siz[N]{};
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
        for (ull i : v1[x]) ret = ret*seed + i;
        return ret;
    }
    ull calc(int x) {
        f1 = f2 = 0; f[0] = 1<<30; dfs1(x, 0);
        sum = siz[x]; dfs2(x, 0);
        if (f[f1] != f[f2]) return dfs3(f1, 0);
        ull t1 = dfs3(f1, f2), t2 = dfs3(f2, f1);
        if (t1 > t2) swap(t1, t2);
        return t1 * seed + t2;
    }
    int m{};
    ull val[N]{};
    vector<node> v3;
    void solve(int x) {
        id = x; init();
        scanf("%d", &m);
        for (int i = 1, xx, yy; i <= m; ++i) {
            cin >> xx >> yy;
            v[xx].push_back(yy); v[yy].push_back(xx);
        }
        for (int i = 1; i <= n; ++i)
            if (!used[i]) {
                get(i, 0, i);
                val[i] = calc(i);
                v2.push_back(val[i]);
            }
        ranges::sort(v2);
        for (int i = 1; i <= n; ++i)
            if (!sub[i].empty()) {
                ull t1 = 0, t2 = 0, t3 = 0;
                for (int j = 0, flag = 0; j < v2.size(); ++j) {
                    if (v2[j] == val[i] && !flag) {
                        flag = 1; continue;
                    }
                    t1 = t1*seed1 + v2[j];
                }
                for (int j = 0, t; j < sub[i].size(); ++j) {
                    vis[t=sub[i][j]] = 1;
                    v3.clear(); v3.push_back({1, 0, 0});
                    for (int & k : v[t])
                        v3.push_back({calc(k), k, 0});
                    sort(v3.begin(), v3.end());
                    for (int k = 1; k < v3.size(); ++k) {
                        t2 = 0;
                        for (int w = 0; w < v3.size(); ++w)
                            if (w != k) t2 = t2*seed1 + v3[w].v;
                        if (id == 0) t3 = v3[k].v*seed2*seed2 + t2*seed2 + t1;
                        else t3 = v3[k].v*seed2*seed2 + t1*seed2 + t2;
                        a[id].push_back({t3, v3[k].x, t});
                    }
                    t2 = 0;
                    for (auto & w : v3) t2 = t2*seed1 + w.v;
                    if (id == 0) t3 = t2*seed2 + t1;
                    else t3 = t1*seed2 + t2;
                    a[id].push_back({t3, 0, t});
                    vis[t] = 0;
                }
            }
        sort(a[id].begin(), a[id].end());
    }
    void print() const {
        puts("YES");
        for (int i = 1; i <= n; ++i)
            for (int j = 0, t; j < v[i].size(); ++j)
                if ((t=v[i][j]) < i)
                    printf("%d %d\n", i, t);
    }
} tr[2], ans;

int pos[2][N], lb;
int dfs(int x, int y, int type) {
    int ret = pos[type][x] = ++lb;
    for (int i = 0, t; i < tr[type].v[x].size(); ++i)
        if ((t=tr[type].v[x][i]) != y) {
            int t1 = dfs(t, x, type);
            ans.v[ret].push_back(t1);
            ans.v[t1].push_back(ret);
        }
    return ret;
}

void out() {
    scanf("%d%*d", &n);
    for (int i = 0; i <= 1; ++i) tr[i].solve(i);
    for (int i = 0, now = 0; i < a[0].size(); ++i) {
        while (now < a[1].size() && a[1][now].v < a[0][i].v) now++;
        if (now < a[1].size() && a[1][now].v == a[0][i].v) {
            dfs(a[0][i].y, 0, 0);
            int t = lb;
            dfs(a[1][now].y, a[1][now].x, 1);
            ans.vis[pos[0][a[0][i].y]] = 1;
            int t1 = pos[1][a[1][now].y];
            ull vv = tr[1].calc(a[1][now].y);
            for (int j = 1; j <= t; ++j) {
                ans.v[j].push_back(t1);
                ans.v[t1].push_back(j);
                if (ans.calc(t1) == vv) {
                    ans.print();
                    return;
                }
                ans.v[j].pop_back();
                ans.v[t1].pop_back();
            }
        }
    }
    puts("NO");
}

int q;
int main() {
    scanf("%d", &q);
    while (q--) {
        lb = 0;
        memset(pos, 0, sizeof(pos));
        a[0].clear(); a[1].clear();
        ans.init();
        out();
    }
    return 0;
}