//
// Created by Psy.C on 2026/10/12.
//
/**
du[i]：入度。
a[i]：节点标签 0/1。
q1、q2：两个数组队列（分别装标签 0、1 的待处理节点），tp1/tp2 是队尾指针，h1/h2 是队头指针（在 topp 内定义）。
g[]：邻接表（出边）。
ans：答案（切换次数相关）
先把所有入度为 0 的节点按标签分入 q1（标签0）或 q2（标签1）。
主循环：只要任一队列非空。
阶段1：把 q1（标签0）中所有节点一口气处理完（每个出队节点把出边目标节点入度减1，减到0就按标签入队）。这个 while 会一直处理到 q1 清空。
然后 ans += (h2 <= tp2)：若此时 q2 里还有节点（说明要切到标签1），ans 加 1（记一次切换）。
阶段2：同理把 q2（标签1）处理完，出边入度减1、减到0按标签入队。
循环会持续到两个队列都空。
关键：while (h1<=tp1) 里处理 q1 时，新入队的标签0节点也会继续在本阶段内处理（因为 q1 还在增长），从而保证"同一批次尽量把同一标签的都处理完，减少标签切换"。【这正是求最少切换次数的贪心。】
读入 n、m 和各节点标签。
读入 m 条边 (u,v)，下标整体 +1（把 0-based 输入转 1-based），建边 u->v 并累加入度 du[v]。
调用 topp() 输出 ans

rep(i,0,g[t].size()-1)：当 g[t] 为空时，g[t].size()-1 = -1（size_t 无符号下会下溢为超大值），导致循环不执行？——实际上 size() 是无符号数，0-1 会变成很大的数，但循环条件 i <= 巨大值 成立，i 从 0 开始……由于邻接表为空没有元素，g[t][i] 在 i=0 时会越界访问！这是潜在 bug。
不过实际中若 g[t] 为空，g[t].size()-1 下溢成 2^64-1，rep(i,0,巨型数) 会访问 g[t][i]，在 i=0 就已越界 → 未定义行为。好在通常拓扑排序中出度节点一般有边，若无出边节点入队，这里会踩坑。更安全的写法应是 i+1 <= g[t].size() 或 int sz=g[t].size(); rep(i,0,sz-1) 且 sz>0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e5+5;

int n, du[N], a[N], q1[N], tp1, q2[N], tp2, ans;
vector<int> g[N];
void topp() {
    int h1 = 1, h2 = 1;
    rep(i,1,n) {
        if (!du[i]) {
            if (!a[i]) q1[++tp1] = i;
            else q2[++tp2] = i;
        }
    }
    while (h1 <= tp1 || h2 <= tp2) {
        while (h1 <= tp1) {
            int t = q1[h1++];
            rep(i,0,g[t].size()-1) {
                --du[g[t][i]];
                if (!du[g[t][i]])
                    a[g[t][i]]==0 ? q1[++tp1]=g[t][i] : q2[++tp2]=g[t][i];
            }
        }
        ans += h2 <= tp2;
        while (h2 <= tp2) {
            int t = q2[h2++];
            rep(i,0,g[t].size()-1) {
                --du[g[t][i]];
                if (!du[g[t][i]])
                    a[g[t][i]]==0 ? q1[++tp1]=g[t][i] : q2[++tp2]=g[t][i];
            }
        }
    }
}

int m, u, v;
signed main() {
    fast;
    cin>>n>>m;
    rep(i,1,n) cin >> a[i];
    while(m--) {
        cin >> u >> v; ++u, ++v;
        g[u].push_back(v); ++du[v];
    }
    topp();
    cout << ans << '\n';
    return 0;
}