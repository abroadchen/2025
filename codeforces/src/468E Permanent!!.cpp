//
// Created by Psy.C on 2026/2/13.
//
/**
id[N]：节点ID映射
idx[N]：X集合的节点
idy[N]：Y集合的节点
cntx, cnty：X,Y集合的大小
dp[1<<20]：状压DP数组

n：矩阵大小
K：修改次数
sum[N]：存储每种匹配数的方案数
tmp[N]：临时数组
fac[N]：阶乘数组


时间复杂度：O(k^2 * 2^(k/2))，其中k是修改次数
 */
#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 2000010
#define mod 1000000007
#define ii pair<int, int>
using namespace std;

inline int add(int x, const int y) {//确保结果在[0, mod-1]范围内
    x += y;
    if (x >= mod) x -= mod;
    if (x < 0) x += mod;
    return x;
}
inline int sub(const int x, const int y) { return add(x, -y); }
inline void ckmul(int& x, const int y) { x = 1ll*x*y%mod; }
inline int mul(const int x, const int y) { return 1ll*x*y%mod; }
inline void ckdel(int& x, const int y) { x = sub(x, y); }

bool vis[N];
vector<int> node;//存储当前连通块的节点
int cnt;//当前连通块的边数
vector<ii> g[N];//节点i的所有相邻节点及其边权
inline void dfs(int x) {
    if (vis[x]) return;
    vis[x] = 1;
    node.emplace_back(x);
    cnt += g[x].size();//累加节点x的邻接边数量到总边数
    for (const auto key: g[x] | views::keys)
        dfs(key);//递归遍历所有可达节点
}

int n, res[N];
namespace Bitmask_DP {
    int id[N], idx[N], idy[N], cntx, cnty, dp[1<<20];
    inline void get() {
        cntx = cnty = 0;
        for (const auto x : node) {
            if (x <= n) {//放入X集合
                idx[++cntx] = x;
                id[x] = cntx;//记录x的新编号
            } else {//放入Y集合
                idy[++cnty] = x;
                id[x] = cnty;
            }
        }
        if (cntx < cnty) {//确保X集合更小（优化状态数）
            for (int i = 1; i <= cnty; ++i) {
                swap(idx[i], idy[i]);//交换X,Y集合的第i个节点
                swap(id[idx[i]], idy[idy[i]]);//更新编号映射
            }
            swap(cntx, cnty);//交换集合大小
        }
        int U = 1<<cnty; --U;//Y集合的全集状态
        dp[0] = 1;//不选择任何边的方案数为1
        for (int i = 1; i <= cntx; ++i) {//遍历X集合中的每个节点
            //从大到小遍历所有状态
            for (int s = U; s >= 0; --s) if (dp[s]) {//当前状态有方案数
                dp[s] %= mod;
                //遍历X集合第i个节点的邻接边 fst是邻接节点，snd是边权
                for (auto [fst, snd] : g[idx[i]]) {
                    //状态s中第(id[fst]-1)位是否为1
                    if (s>>(id[fst]-1)&1) continue;//Y集合中对应节点是否已被匹配
                    //选择这条边
                    dp[s|(1<<(id[fst]-1))] += dp[s]*snd%mod;//将对应位置设为1（匹配）
                }
            }
        }
        //统计结果，清空数组 准备处理下一个连通块
        for (int s = 0; s <= U; ++s) if (dp[s])
            //将每种状态的方案数累加到对应匹配数的结果中
            res[__builtin_popcount(s)] += dp[s], dp[s] = 0;
        for (int i = 1; i <= cntx; ++i) id[idx[i]] = 0, idx[i] = 0;
        for (int i = 1; i <= cnty; ++i) id[idy[i]] = 0, idy[i] = 0;
    }
}

namespace Brute_Force {
    struct DSU {
        int fa[N];
        void init(const int n) { for (int i = 1; i <= n; ++i) fa[i] = i; }
        int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
        void merge(const int x, const int y) { fa[find(x)] = find(y); }
    } Dsu;
    struct Edge { int u, v, w; } e[110];//存储非树边的数组
    int ecnt, idcnt;//非树边数量 节点重新编号
    vector<ii> tr[N];//生成树的邻接表
    bool mark[N];
    //以i为根的子树中选择j条边，节点i是否被选择的方案数 0表示节点未被选择，1表示被选择
    int dp[300][300][2], tmp[300][2], id[N], siz[300];
    inline void dfs(const int x, const int fa) {
        memset(dp[x], 0, sizeof(dp[x]));
        //x节点的子树中选择0条边，x节点状态为mark[x]的方案数为1
        dp[x][0][mark[x]] = siz[x] = 1;
        for (auto e : tr[x]) {
            const int t = e.first;
            if (t == fa) continue;
            dfs(t, x);//递归处理子节点t
            for (int i = 0; i <= siz[x]; ++i) {//枚举x子树中选择的边数
                for (int j = 0; j <= siz[t]; ++j) {//t子树中选择的边数
                    //x不被选择，t也不被选择，连接它们的边被选择
                    tmp[i+j+1][1] += dp[x][i][0]*dp[t][j][0]%mod*e.second%mod;
                    //x不被选择，t可选可不选，不连接它们
                    tmp[i+j][0] += dp[x][i][0]*(dp[t][j][0]+dp[t][j][1])%mod;
                    //x被选择，t可选可不选，不连接它们
                    tmp[i+j][1] += dp[x][i][1]*(dp[t][j][0]+dp[t][j][1])%mod;
                }
            }
            siz[x] += siz[t];//更新x的子树大小
            for (int i = 0; i <= siz[x]; ++i) {
                dp[x][i][0] = tmp[i][0]%mod;//将临时数组tmp的值转移到dp数组
                dp[x][i][1] = tmp[i][1]%mod;
                tmp[i][0] = tmp[i][1] = 0;
            }
        }
    }
    inline void get() {
        idcnt = ecnt = 0;
        for (const auto x : node) id[x] = ++idcnt;//建立新编号
        Dsu.init(idcnt);//初始化并查集
        for (int i = 1; i <= idcnt; ++i) tr[i].clear();//清空生成树的邻接表
        for (const auto x : node) {
            if (x > n) break;
            for (auto [fst, snd] : g[x]) {
                int v = id[fst];
                //u,v不在同一集合，是树边
                if (int u = id[x]; Dsu.find(u) != Dsu.find(v)) {
                    Dsu.merge(u, v);
                    tr[v].emplace_back(u, snd);//添加生成树边
                    tr[u].emplace_back(v, snd);
                } else {
                    e[++ecnt] = {u, v, snd};//非树边，保存到e数组
                }
            }
        }
        int S = 1<<ecnt; --S;
        for (int s = 0; s <= S; ++s) {//枚举所有非树边的选择方案
            bool flag = 1;
            int coef = 1;
            for (int i = 1; i <= ecnt; ++i) if (s>>(i-1)&1) {//第i条非树边是否被选择
                if (mark[e[i].u] || mark[e[i].v]) {//检查是否冲突
                    flag = 0;
                    break;
                }
                ckmul(coef, e[i].w);//累乘边权
                mark[e[i].u] = mark[e[i].v] = 1;//标记节点已被占用
            }
            if (flag) {//当前方案合法
                dfs(1, 0);//在生成树上进行树形DP
                int Bas = __builtin_popcount(s);//计算选择的非树边数量
                for (int i = 0; i <= siz[1]; ++i) {
                    int val = add(dp[1][i][0], dp[1][i][1]);//计算总的方案数
                    res[Bas+i] += val*coef%mod;//累加到结果
                }
            }
            for (int i = 1; i <= ecnt; ++i) mark[e[i].u] = mark[e[i].v] = 0;//清空标记数组
        }
    }
}

int K, sum[N], tmp[N], fac[N];
signed main() {
    fast;
    cin >> n >> K;
    for (int i = 1, x, y, z; i <= K; ++i) {
        cin >> x >> y >> z;
        ckdel(z, 1);//将边权减1（利用w=(w-1)+1的技巧）
        g[x].emplace_back(y+n, z);//建立二分图边
        g[y+n].emplace_back(x, z);//建立反向边
    }
    sum[0] = 1;//初始方案数
    //遍历所有连通块
    for (int x = 1; x <= n+n; ++x) if (g[x].size() && !vis[x]) {
        cnt = 0; node.clear(); dfs(x);
        ranges::sort(node); cnt /= 2;//无向图
        //稠密用状压DP，稀疏用暴力
        if (cnt*2 > node.size()*3) Bitmask_DP::get();
        else Brute_Force::get();
        //卷积合并不同连通块的贡献
        for (int i = 0; i <= K; ++i) res[i] %= mod;
        for (int i = 0; i <= K; ++i)
            for (int j = 0; i+j <= K; ++j)
                tmp[i+j] += sum[i]*res[j]%mod;
        for (int i = 0; i <= K; ++i)
            sum[i] = tmp[i]%mod, res[i] = tmp[i] = 0;
    }
    int ans = 0; fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = mul(fac[i-1], i);
    for (int i = n; i >= 0; --i) ans += mul(sum[i], fac[n-i]);
    cout << ans%mod << '\n';
    return 0;
}