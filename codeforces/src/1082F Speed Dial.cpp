//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
tr[]：Trie 节点池，son[10] 表示数字 0–9 的 10 个孩子（-1=空）。
dep：节点在 Trie 中的深度。
cnt：该节点累加的权值（完整串结尾处累加）。
tot：节点计数，0 号节点是根。
N=1e5+5 是字符串总长上限，M=505 是节点数上限
从根 0 出发，按串的每个字符 s[i] 走到对应孩子；若不存在则新建节点，并把其 dep 设为父深度+1。
走到串末节点后，把该节点 cnt 累加 cnt（表示这个完整串的权值集中在此节点）
dp[x][rem][fa]
含义：在"父亲深度为 fa"的前提下，节点 x 及其子树，共被分配 rem 个标记，所花费的最小总费用
若还有标记配额，其中一种方案是在 x 自己这里放一个标记（fa 更新为 x 本身，rem-1），这样 x 的子孙距标记更近，费用更低
dp2[x][rem][fa][i]
用来做分组背包合并：在 x 的所有孩子（ch[]）上，从后往前分配 rem 个标记。i 表示当前处理到第 i 个孩子。
转移
给第 i 个孩子分配 j 个标记（成本由 dfs(ch[i],j,fa) 给出），剩余的 rem-j 分给后面的孩子
dp2[x][rem][fa][0] 是所有孩子都分配完后的最小费用。
加上 tr[x].cnt * (tr[x].dep - tr[fa].dep)：即 x 节点处累积的完整串权值 tr[x].cnt，要按"从最近标记祖先（深度 tr[fa].dep）到 x（深度 tr[x].dep）的深度差"计费——每差一层产生一份费用，共 tr[x].cnt 份
从根开始，分配 k 个标记，初始"父亲"就是根（深度 0
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5, M = 505, inf = 0x3f3f3f3f;

struct node {
    int son[10], dep, cnt;
    node() { memset(son, -1, sizeof(son)); cnt = dep = 0; }
} tr[M];

char s[N];
int tot;
void add() {
    int now = 0, cnt; cin >> s >> cnt;
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        int to = s[i] - '0';
        if (tr[now].son[to] == -1) {
            tr[now].son[to] = ++tot;
            tr[tot].dep = tr[now].dep + 1;
        }
        now = tr[now].son[to];
    }
    tr[now].cnt += cnt;
}

int dp[M][15][M], dp2[M][15][M][15];
int dfs(int x, int rem, int fa) {
    if (dp[x][rem][fa] != -1) return dp[x][rem][fa];
    dp[x][rem][fa] = inf;
    if (rem) dp[x][rem][fa] = min(dfs(x,rem-1,x), dp[x][rem][fa]);
    vector<int> ch;
    for (int i : tr[x].son) if (i != -1) ch.push_back(i);
    dp2[x][rem][fa][ch.size()] = 0;
    for (int i = int(ch.size())-1; i >= 0; --i)
        for (int j = 0; j <= rem; ++j)
            dp2[x][rem][fa][i] = min(dp2[x][rem][fa][i],
                dp2[x][rem-j][fa][i+1]+dfs(ch[i],j,fa));
    dp[x][rem][fa] = min(dp[x][rem][fa],
        dp2[x][rem][fa][0]+tr[x].cnt*(tr[x].dep-tr[fa].dep));
    return dp[x][rem][fa];
}

int n, k;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1, v; i <= n; ++i) add();
    memset(dp, -1, sizeof(dp));
    memset(dp2, inf, sizeof(dp2));
    int ans = dfs(0, k, 0);
    cout << ans << '\n';
    return 0;
}