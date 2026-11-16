//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
读入 n 个点、m 条边。
g[i] 用 set 存点 i 的邻居（set 便于删除和取最小值）。
--x, --y 把题目 1-based 编号转成 0-based 下标。
无向边：g[x].insert(y); g[y].insert(x)
deg 是一个按"度数"排序的集合，元素是 {度数, 编号}，用于快速找叶子。
w[i] 记录点 i 所在"连通块/已合并部分"的权重（初始每个点权重 1）。
ans 累积答案（点对距离贡献）
每次取度数最小的点（deg.begin()）。
若它的度数 >1，说明已经不是叶子（叶子度数应为 1），停止剥叶——因为剩下的结构含环。
当 deg.size()>1 才继续（只剩一个点说明整棵树处理完）
y 是 x 的唯一邻居。
从 deg 和 g 中删掉这条边 x-y。
贡献计算：x 所在分块（权重 w[x]）与"所有其他点"（n - w[x]）之间，每条路径都要经过这条边 x-y，贡献 w[x]*(n-w[x])，无向双向所以乘 2。累加进 ans。
把 x 的分块并入 y：w[y] += w[x]。
更新 y 的度数重新插入 deg。
这段本质是"树的部分逐层剥离，边对答案贡献 = 两侧点数的乘积 ×2"
如果剥完只剩 1 个点 → 整张图是树，答案已算完。
但为什么 ans>>1？因为阶段 1 里每条边贡献乘了 2，且树的所有边都被剥了一遍；不过... 实际上这里 (ans>>1) 是因为每条边的"两侧点数乘积"在双向累加时可能被重复计算了一次（见阶段 4 末尾整体除以 2 的道理类似）。在此树的情况直接输出
id[i]：点 i 是否被标记为"关键点/主节点"，初始 -1。
e 存每个点的邻居列表（把 set 转成 vector 方便遍历）。
m 用来计数关键点的数量
建出邻接表 e。
度数 > 2 的点设为关键节点（因为它们是树与环的交汇点，必须拆出来，不能并入环链处理）
如果没有任何度数>2的点（即全是环，图本身是一个大环），就随便选一个度数为 2 的点作为唯一的"关键点"，保证后面至少有一个主节点
bw[i][j]：记录从关键点 i 到关键点 j 的所有分支路径。
先为"关键点间直接相邻"的空路径占位
对每个度数为 2 且还不是关键点的普通点 i（它处于某条环链的内部），开始沿链走，收集链上各点的权重 ws
从 i 的两个方向（j=0,1）各走一条链，直到到达某个关键点。
链上每个点 id[x] = m 标记为已经归属于这条链（不再重复处理）。
nxt = e[x][0]+e[x][1]-pre：因为 x 度数为 2，两个邻居之和减去"来路"就是"去路"，即沿链线性前进的小技巧。
end[j] 记录链两端的关键点。
ranges::reverse(ws)：反转权重列表（配合另一端，让 ws 顺序与方向一致）
把这条链（点权重序列 ws）存入 bw，方向为从 end[1] 到 end[0]
重新整理 w：把所有点按自己的关键点/链 id 归并，得到"每个主节点/链的分块权重 w[id]"
压缩图有 m 个节点（关键点）。
dis[i][j]：关键点 i 到 j 的最短路（边权 = 链长+1；因为链上有 p.size() 个点，加上两端的节点）。
对每条链更新两端点距离，取最小。
no 记录所有"存在直接连链"的节点对
Floyd 求压缩图上的全源最短路。
关键点之间的路径贡献：每对关键点 i、j 间的距离 dis[i][j]，两侧关键点为两个分块（权重 w[i]、w[j]），贡献 w[i]*w[j]*dis[i][j]，乘 2 表示双向。累加进 ans。
这里说明：压缩图节点间的最短路径贡献，已经用 w[i]*w[j]*dis[i][j] 覆盖了"跨关键点"的路径
sw：权重前缀和（链上前 k 个点的权重和）。
sd：带位置加权的前缀和（权重 × 位置 l）。
这两个前缀和让"任意区间 [l,r] 内所有点与某点的距离和"能用 O(1) 算出，避免每对点重新遍历
计算链 (i,j) 的第 k 条路径里，区间 [l,r] 的点，到某个参照点距离为 dist + 位置×dif 的总和（用前缀和 O(1) 求）
对链上每个位置 l 的点 z，考虑它到任意关键点 x 的最短路：
从这端走：dis[i][x] + l(链内点到 i 的距离)
从另一端走：dis[j][x] + (链长 - l)
取两者较小者。
贡献 2 * w[z] * w[x] * min(...)
同链不同位置点对：两个点都在 i-j 这一条链上，距离 = 位置差（取小），用 solve 依据谁在哪端分段累加。
不同链点对：考虑两条链 (i,j,k) 和 (x,y,kk) 的任意两个位置，最短路径要么经过中间关键点走，用 L/R 表示这两个位置到目标关键点的距离下界，再用 solve 的区间去逼近最短路（类似把两边到关键点的最短路在"中间关键点"处接起来，取 min）
因所有点对贡献都被"双向 ×2"累加（如 ans += 2 * ...），无向点对实际只应计一次，所以最后 >>1（除以 2）再输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0;i<n;++i)
#define ii pair<int,int>
#define vi vector<int>
#define ll long long
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<set<int>> g(n);
    rep(i,m) {
        int x, y; cin >> x >> y; --x, --y;
        g[x].insert(y); g[y].insert(x);
    }
    set<ii> deg; vi w(n,1); ll ans = 0;
    rep(i,n) deg.insert({g[i].size(), i});
    while (deg.size() > 1) {
        int x = deg.begin()->second;
        if (g[x].size() > 1) break;
        int y = *g[x].begin();
        deg.erase({g[x].size(), x}); deg.erase({g[y].size(), y});
        g[x].erase(y); g[y].erase(x);
        ans += 2ll*w[x]*(n-w[x]); w[y] += w[x];
        deg.insert({g[y].size(), y});
    }
    if (deg.size() == 1) { cout << (ans>>1) << '\n'; return 0; }
    vi id(n,-1); vector<vi> e(n); m = 0;
    rep(x,n) {
        for (auto y : g[x]) e[x].push_back(y);
        if (e[x].size() > 2) id[x] = m++;
    }
    if (!m) rep(i,n) if (e[i].size() == 2) { id[i] = m++; break; }
    vector bw(m,vector<vector<vi>>(m));
    rep(x,n) if (~id[x]) for (auto y : e[x]) if (~id[y]) bw[id[x]][id[y]].emplace_back();
    rep(i,n) if (e[i].size() == 2 && !~id[i]) {
        vi ws(1,w[i]), end(2); id[i] = m;
        rep(j,2) {
            int x = e[i][j], pre = i;
            while (!~id[x]) {
                ws.push_back(w[x]); id[x] = m;
                int nxt = e[x][0] + e[x][1] - pre;
                pre = x; x = nxt;
            }
            end[j] = x; ranges::reverse(ws);
        }
        bw[id[end[1]]][id[end[0]]].push_back(ws);
    }
    {
        vi now(m);
        rep(i,n) if (id[i] != -1 && id[i] < m) now[id[i]] = w[i];
        w = now;
    }
    vector dis(m, vi(m,n));
    rep(i,m) dis[i][i] = 0;
    vector<ii> no;
    rep(i,m) rep(j,m) {
        for (auto &p : bw[i][j])
            dis[i][j] = dis[j][i] = min(dis[i][j],(int)p.size()+1);
        if (!bw[i][j].empty()) no.emplace_back(i,j);
    }
    rep(k,m) rep(i,m) rep(j,m) dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
    rep(i,m) rep(j,i) ans += 2ll*w[i]*w[j]*dis[i][j];
    vector sw(m,vector<vector<vector<ll>>>(m)), sd(m, vector<vector<vector<ll>>>(m));
    rep(i,m) rep(j,m) {
        sw[i][j].resize(bw[i][j].size()); sd[i][j].resize(bw[i][j].size());
        rep(k,bw[i][j].size()) {
            sw[i][j][k].resize(bw[i][j][k].size()+1);
            sd[i][j][k].resize(bw[i][j][k].size()+1);
            rep(l,bw[i][j][k].size()) {
                sw[i][j][k][l+1] = sw[i][j][k][l]+bw[i][j][k][l];
                sd[i][j][k][l+1] = sd[i][j][k][l]+(ll)bw[i][j][k][l]*l;
            }
        }
    }
    auto solve = [&](int i, int j, int k, int l, int r, int dist, int dif) {
        return dist*(sw[i][j][k][r]-sw[i][j][k][l])+dif*(sd[i][j][k][r]-sd[i][j][k][l]);
    };
    rep(i,m) rep(j,m) rep(k,bw[i][j].size()) rep(l,bw[i][j][k].size()) {
        ll z = bw[i][j][k][l];
        rep(x,m) ans += 2ll*z*w[x]*min(dis[i][x]+l+1,dis[j][x]+(int)bw[i][j][k].size()-l);
        for (auto p : no) {
            int x = p.first, y = p.second;
            rep(kk,bw[x][y].size()) {
                if (i == x && j == y && k == kk) {
                    {
                        int L = l, R = dis[i][j]+bw[i][j][k].size()-l+1;
                        if (L <= R) ans += z*solve(i,j,k,0,l,L,-1);
                        else {
                            int mid = (L-R+1)>>1;
                            ans += z*solve(i,j,k,0,mid,R,1);
                            ans += z*solve(i,j,k,mid,l,L,-1);
                        }
                    }
                    {
                        int L = -l, R = dis[i][j]+bw[i][j][k].size()+l+1;
                        int mid = min((int)bw[i][j][k].size(),(R-L+1)>>1);
                        ans += z*solve(i,j,k,l,mid,L,1);
                        ans += z*solve(i,j,k,mid,bw[i][j][k].size(),R,-1);
                    }
                } else {
                    int L = min(dis[i][x]+l+1,dis[j][x]+(int)bw[i][j][k].size()-l);
                    int R = min(dis[i][y]+l+1,dis[j][y]+(int)bw[i][j][k].size()-l);
                    int mid = min(bw[x][y][kk].size(),(R-L+bw[x][y][kk].size()+1)>>1);
                    ans += z*solve(x,y,kk,0,mid,L+1,1);
                    ans += z*solve(x,y,kk,mid,bw[x][y][kk].size(),R+bw[x][y][kk].size(),-1);
                }
            }
        }
    }
    cout << (ans>>1) << '\n';
    return 0;
}