//
// Created by Psy.C on 2025/12/30.
//
/**
* val[N]: 树状数组存储的值
n: 数组大小
init: 初始化数组大小
lb: 低比特函数，返回x的最低位1及其后面的0组成的数值
add: 在位置pos处增加值v
query: 查询前pos个元素的前缀和
tr: 创建树状数组实例
 *
*Edge: 边结构体，包含目标节点to、边权w、下一节点指针nxt
e[N<<1]: 边数组（N<<1 = N*2，因为是无向图）
head[N]: 邻接表头指针数组
cnt: 边的计数器
addEdge: 添加无向边（实际添加两条有向边）
 *
*输入节点数n、长度限制l、权重限制w
初始化边计数器为0
初始化邻接表头为-1（表示空）
读入树的边信息，构建邻接表（无向图）
 *
*rt: 重心节点
sum: 当前子树节点总数
f[N]: 记录以u为根时，删除u后最大子树的大小
son[N]: 记录子树大小
vis[N]: 访问标记数组
get_root: lambda函数，用于寻找树的重心
son[u] = 1: 初始化子树大小为1
遍历所有相邻节点，递归处理子树
f[u] = max(f[u], sum - son[u]): 更新删除当前节点后剩余部分的最大子树大小
重心是使f[u]最小的节点
*从节点1开始寻找重心
vec: 存储当前子树的所有节点
dis[N]: 存储距离（边数）
wi[N]: 存储权重和
get_dis: 获取从u开始的所有可达节点，记录距离和权重
 *
*cal: 计算从节点u开始的满足条件的路径数量
x1, x2: 初始距离和权重
清空vec，调用get_dis获取子树信息
按权重排序vec
初始化树状数组并添加所有节点的距离信息
使用双指针算法：如果两端点权重和≤w，统计距离和≤l的路径数
tr.query(l - dis[vec[L]] + 1): 查询距离≤l-dis[vec[L]]的节点数
最后清理树状数组
 *
*solve: 递归解决函数
res += cal(u, 0, 0): 计算经过当前重心的所有路径
vis[u] = 1: 标记当前节点已访问
遍历所有子树，减去重复计算的路径
res -= cal(v, 1, w3): 减去在子树内部重复计算的路径
重新寻找子树重心并递归处理
 *
 *时间复杂度优化到O(n log n)
 */
#include <iostream>
#include <functional>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

class BIT {
public:
    int val[N], n;
    void init(const int _n) { n = _n; }
    static int lb(const int x) { return x & -x; }
    void add(const int pos, const int v) {
        for (int i = pos; i <= n; i += lb(i)) val[i] += v;
    }
    int query(const int pos) const {
        int ans = 0;
        for (int i = pos; i >= 1; i -= lb(i)) ans += val[i];
        return ans;
    }
} tr;

struct Edge { int to, nxt; ll w; } e[N<<1];
int head[N], cnt;
void addEdge(const int u, const int v, const ll w) {
    e[cnt].to = v, e[cnt].w = w, e[cnt].nxt = head[u], head[u] = cnt, cnt++;
}

int main() {
    fast;
    int n, l; ll w; cin >> n >> l >> w;
    cnt = 0;
    for (int i = 1; i <= n; ++i) head[i] = -1;
    for (int i = 2, v; i <= n; ++i) {
        ll w1; cin >> v >> w1;
        addEdge(i, v, w1); addEdge(v, i, w1);
    }
    int rt = 0, sum = n, f[N], son[N], vis[N]; f[0] = n;
    function<void(int,int)> get_root = [&](const int u, const int fa) {
        son[u] = 1, f[u] = 0;
        for (int i = head[u]; ~i; i = e[i].nxt) {
            const int v = e[i].to;
            if (vis[v] || v == fa) continue;
            get_root(v, u);
            son[u] += son[v], f[u] = max(f[u], son[v]);
        }
        f[u] = max(f[u], sum - son[u]);
        if (f[u] < f[rt]) rt = u;
    };
    get_root(1, 0);
    vector<int> vec; int dis[N]; ll wi[N];
    function<void(int,int)> get_dis = [&](const int u, const int fa) {
        vec.push_back(u);
        for (int i = head[u]; ~i; i = e[i].nxt) {
            const int v = e[i].to;
            const ll w2 = e[i].w;
            if (v == fa || vis[v]) continue;
            dis[v] = dis[u] + 1, wi[v] = wi[u] + w2;
            get_dis(v, u);
        }
    };
    auto cal = [&](const int u, const int x1, const ll x2) {
        vec.clear();
        dis[u] = x1, wi[u] = x2, get_dis(u, 0);
        sort(vec.begin(), vec.end(), [&](const int ta, const int tb) {
            return wi[ta] < wi[tb];
        });
        tr.init(n + 1);
        for (const int i : vec) tr.add(dis[i] + 1, 1);
        ll ans = 0;
        int L = 0, R = static_cast<int>(vec.size()) - 1;
        while (L < R) {
            if (wi[vec[L]] + wi[vec[R]] <= w) {
                tr.add(dis[vec[L]] + 1, -1);
                ans += tr.query(l - dis[vec[L]] + 1);
                L++;
            } else {
                tr.add(dis[vec[R]] + 1, -1);
                R--;
            }
        }
        tr.add(dis[vec[L]] + 1, -1);
        return ans;
    };
    ll res = 0;
    function<void(int)> solve = [&](const int u) {
        res += cal(u, 0, 0);
        vis[u] = 1;
        for (int i = head[u]; ~i; i = e[i].nxt) {
            const int v = e[i].to;
            const ll w3 = e[i].w;
            if (vis[v]) continue;
            res -= cal(v, 1, w3);
            rt = 0, sum = son[v];
            get_root(v, 0);
            solve(rt);
        }
    };
    solve(rt);
    cout << res << '\n';
    return 0;
}