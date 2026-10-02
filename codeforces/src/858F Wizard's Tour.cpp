//
// Created by Psy.C on 2026/10/2.
//
/**
G[u]：邻接表，edge.v 是邻居点，edge.i 是边的编号（1..m，唯一标识每条边）。
vis：DFS 访问标记（点是否已遍历）。
use：边是否已被配对使用。
cnt：配对数（组数）。
ss：把输出缓冲起来
dfs(u, f, fi)：从 u 出发，f 是父节点，fi 是通向父的那条边的编号。

lzy（lazy，暂存的配对伙伴端点）、lzyi（对应的边编号）。这里 lzy 存的是待配对的那条边的另一端端点，lzyi 是那条边编号。

遍历 u 的所有出边（跳过父边 v==f 和已用过 use[i] 的边）：

vis[v]?1:!dfs(v,u,i)：

如果 v 已访问 → 说明是回边/已处理过，enable=1（这条边可用，但不会再向下去配对别的，直接作为备选）。
如果 v 未访问 → 递归下去 dfs(v,u,i)，若子树返回 0（没把这条边用掉）则 enable = !0 = 1（这条边还剩着可用）；若返回 1（子树里这条边已被配对用掉）则 enable=0。
若 enable（这条边可用）：

若之前已暂存了一条 lzy → 两条边现在配成一对：输出 lzy u v（两条边分别是 u-lzy 和 u-v，共享点 u），同时把两条边 i 和 lzyi 标记已用，清空暂存。
若没有暂存 → 把当前这条边暂存起来（lzy=v, lzyi=i），等待后续的边来配对。
遍历完后若还剩一条暂存未配对（lzy 非空）且当前点不是根（f!=0）：把这条边和父边 fi 配成一对，输出 lzy u f（两条边 u-lzy 和 u-f 共享点 u），标已用，并 return 1 告诉父节点"父边已经被我用掉了"。

return 0：表示自己的父边没被用到（父边可用）。
读入 n 点 m 边，建无向图（每条边两个方向各存一次，编号 i 相同，保证同一边的 use[i] 一致）。
对每个未访问点跑 dfs，覆盖所有连通分量（图不一定连通）。
输出 cnt（组数）和每一步配对。
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5;

struct edge { int v, i; };
vector<edge> G[N];
bitset<N> vis, use;
int cnt;
stringstream ss;
bool dfs(int u, int f, int fi) {
    int lzy=0,lzyi=0;
    vis[u]=1;
    for(auto [v,i]:G[u]){
        if(v==f||use[i])continue;
        bool enable=vis[v]?1:!dfs(v,u,i);
        if(enable){
            if(lzy){
                cnt++;
                ss<<lzy<<" "<<u<<" "<<v<<"\n";
                use[i]=use[lzyi]=1;
                lzy=lzyi=0;
            }else{
                lzy=v;lzyi=i;
            }
        }
    }
    if(lzy&&f){
        cnt++;
        ss<<lzy<<" "<<u<<" "<<f<<"\n";
        use[fi]=use[lzyi]=1;
        return 1;
    }
    return 0;
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 1, a, b; i <= m; ++i) {
        cin >> a >> b; G[a].push_back({.v = b, .i = i});
        G[b].push_back({.v = a, .i = i});
    }
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) dfs(i, 0, 0);
    cout << cnt << '\n' << ss.rdbuf();
    return 0;
}