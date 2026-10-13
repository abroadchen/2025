//
// Created by Psy.C on 2026/10/13.
//
/**
N: 节点数上限 110；M: 字母种类上限 26(用 30 留余量)
dp[起点i][当前点j][当前字母c]
0=未算, 1=先手胜(该走子方必胜), -1=先手负
邻接表：g[u] 存放 {能到达的点 v, 边上的字母编号}
当前正轮到的玩家站在点 i，对手站在点 j，上一步用的字母是 c（必须是 >=c 的字母才能走）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 110, M = 30;

int dp[N][N][M];
vector<ii> g[N];
int dfs(int i, int j, int c) {
    if (dp[i][j][c]) return dp[i][j][c];
    dp[i][j][c] = -1;//先默认"当前走子方必败"
    for (auto [fst, snd] : g[i]) {//枚举当前玩家从 i 出发的所有出边
        int to = fst, ch = snd;//to: 目标点；ch: 边的字母
        if (ch >= c) {//字母必须不小于上一步的 c（字母递增限制）
            dfs(j, to, ch);//走完这步，轮到对方：对方站 j，走 to，字母变成 ch
            if (dp[j][to][ch] == -1) {//若对方在该状态下"必败"
                dp[i][j][c] = 1;//则当前玩家必胜
                break;//找到必胜方案，停止
            }
        }
    }
    return dp[i][j][c];
}


int main() {
    fast;
    int n, m; cin >> n >> m;
    char ch;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v >> ch;
        g[u].emplace_back(v, ch-'a');//存入邻接表，字母转成 0~25 的编号
    }
    for (int i = 1; i <= n; ++i) {//枚举第一颗棋子初始位置 i
        for (int j = 1; j <= n; ++j) {//枚举第二颗棋子初始位置 j
            if (dfs(i, j, 0) == 1) cout << "A";//先手必胜 → 输出 A
            else cout << "B";//否则（必败）→ 输出 B
        }
        cout << '\n';
    }
    return 0;
}