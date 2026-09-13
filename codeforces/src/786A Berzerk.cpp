//
// Created by Psy.C on 2026/9/13.
//
/**
sg[k][pos]：k 号玩家（0=A,1=B）‍从 pos 位置出发、轮到该玩家走时的状态：-1=未算，0=必败(Lose)，1=必胜(Win)。
g[k]：玩家 k 的步长集合。
d[k][pos]：玩家 k 在 pos 位置尚未处理的"可出走法"计数（用于拓扑判定剩余状态）
读入两步长集合。
d[i][j] 初始化为该玩家的步长总数（1..n-1 每个位置都一样），意思是"从这个位置出发的候选走法数"
从确定态出发反向 DFS：

若当前位置是必败态（v=0）‍，则它所有"前驱"（反推出的 j）必然是必胜态，直接标 v=1 继续（dfs(k^1, j, 1)）。
若当前位置是必胜态（v=1）‍，则对每个前驱 j，它少了一种"通向必败"的走法（因为从 j 走会走到一个必胜态，不是好走法）。用 d[k^1][j] 记录 j 还有多少个"未知走法"。当 --d[k^1][j]==0，说明 j 的所有走法都通向必胜态，于是 j 就是必败态（标 v=0 继续）。
初始调用 dfs(0,0,0) 和 dfs(1,0,0)：位置 0 视为终点/必败基准（从 0 开始无法赢，标 0 为 Lose），从它反向推全图。

没被 DFS 访问到的状态保持 -1，在输出时对应 Loop（循环）‍——这些状态无法确定胜负，会陷入无限循环。

j = (pos + n - x) % n 的解释

当前在 pos（k 玩家），对方的步长是 x。反推前驱：如果对方从 j 走了 x 步到达 pos，则 (j + x) % n == pos，即 j = (pos - x + n) % n。
if (j == 0) continue;：跳过位置 0，因为它被当作已确定基准，不参与反推

sg[k][i] 是 -1/0/1，s[值+1] 映射到 {"Loop","Lose","Win"}：
-1+1=0 → "Loop"
0+1=1 → "Lose"
1+1=2 → "Win"
按玩家 0、玩家 1 两组，输出每个起始位置（1..n-1）的先手结果，以空格分隔每行，最后一个位置换行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int sg[2][N], n, d[2][N];
vector<int> g[2];
int dfs(int k, int pos, int v) {
    int& ret = sg[k][pos];
    if (~ret) return ret;
    ret = v;
    if (v == 0) {
        for (int i = 0; i < g[k^1].size(); ++i) {
            int x = g[k^1][i], j = (pos+n-x)%n;
            if (j == 0) continue;
            dfs(k^1, j, 1);
        }
    } else {
        for (int i = 0; i < g[k^1].size(); ++i) {
            int x = g[k^1][i], j = (pos+n-x)%n;
            if (j == 0) continue;
            if (--d[k^1][j] == 0) dfs(k^1, j, 0);
        }
    }
    return ret;
}

string s[] = {"Loop", "Lose", "Win"};
int main() {
    fast;
    cin >> n;
    for (int i = 0, k, x; i < 2; ++i) {
        cin >> k; g[i].clear();
        while (k--) {
            cin >> x; g[i].push_back(x);
        }
        for (int j = 1; j < n; ++j)
            d[i][j] = g[i].size();
    }
    memset(sg, -1, sizeof sg);
    dfs(0, 0, 0); dfs(1, 0, 0);
    for (auto& k : sg)
        for (int i = 1; i < n; ++i)
            cout << s[k[i]+1].c_str() << (i+1==n?'\n':' ');
    return 0;
}