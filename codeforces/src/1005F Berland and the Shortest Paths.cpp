//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
经典链式前向星存边。因为无向图，主函数里对每条边调用两次 add（add(x,y) 和 add(y,x)），所以 tot 会存 2m 条有向边。

注意一条原边对应 num 中两个连续的位置（2i-1、2i），这就是后面 bfs 里 (i+1)/2 用来还原"原始边编号"的原因
q：BFS 队列；dis 最短距离；vis 是否入过队。
从 1 号点开始，dis[1]=0, vis[1]=1。
BFS 逐层扩展：
dis[now]+1 <= dis[num[i]]：能刷新（或等于当前最优）的松弛时，就认为 now → num[i] 是一条"合法的最短路入边"。
add2(num[i], now, (i+1)/2)：把"num[i] 这个点 + 边 now"记入 num[i] 的可选入边集合，边编号是 (i+1)/2（恢复原始无向边编号，因为每条原边占了 two slots）。
若 num[i] 没进过队，标记并压队。
这里 <= 而不是 < 很关键：**既接受严格最短（<）也接受"等长"的边，从而每个点可能有多条最短路入边（来自不同父亲、同深度）。这为后面"方案有多重选择"打基础
cnt[x]++：点 x 的可选入边数量 +1。
把这条"入边信息"压入点 x 的链表 h[x]：记录前驱 y（nu）和边编号 ID（id）。
所以**cnt[i] 就是"点 i 有多少种最短路入边选择"**，也是方案数的一个因子
方案总数 = ∏_{i=1..n} cnt[i]：对每个点独立选一条入边，总方案数就是各点选择数的乘积。
now 从 1 开始累乘；如果中途 now >= k 就提前跳出返回 k（防止溢出 long long，因为方案数可能天文数字，这里用 k 截断）。
把 cnt[1]=1（起点 1 只有一个"选择"）。返回的 calc() 最终会输出方案总数（题目第一行通常要求输出方案数，若超过 k 则... 看题，此处 cout << calc()）
b[i]：标记"第 i 条原始边是否被选中"。
dfs(now)：为点 now 选一条入边，然后继续下一个点 now+1。
结束条件 now == n+1：所有点都选好了，输出 b[1..m]（0/1 串，表示每条边是否入选），ac++ 计一个方案；当 ac==k（找到第 k 个）时置 flg=1 停止。
对 h[now] 链表遍历（按加入顺序，即按边编号从小到大的加入顺序），选一条边 b[id[i]]=1，递归，回溯时 b[id[i]]=0。
因为 BFS/构建时入边按编号递增挂桶（for i 顺序遍历邻接表，边编号 (i+1)/2 递增），dfs 按这个顺序尝试，天然就是字典序（按边编号从小到大）从小到大枚举方案，因此第 k 个被完整枚举到的方案就是题目要的字典序第 k 个
读入点数 n、边数 m、目标 k。
建无向图。
BFS 建最短路入边集合。
第一行输出方案总数 calc()。
从点 2 开始（点 1 是起点，固定无入边选择），DFS 构造并输出第 k 个方案的边集 b[2..m]（实际按 b[1..m] 顺序打印一个 0/1 串）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); i++)
using namespace std;

constexpr int N = 4e5+5, inf = 2147483647;

int num[N], nxt[N], head[N], tot;
void add(int x, int y) {
    num[++tot] = y; nxt[tot] = head[x]; head[x] = tot;
}

int cnt[N], h[N], nx[N], nu[N], id[N], tot2;
void add2(int x, int y, int ID) {
    cnt[x]++;
    nu[++tot2] = y; id[tot2] = ID; nx[tot2] = h[x]; h[x] = tot2;
}

queue<int> q;
int n, dis[N], vis[N];
void bfs(int S) {
    q.push(S);
    rep(i,n) dis[i] = inf;
    dis[1] = 0, vis[1] = 1;
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = head[now]; i; i = nxt[i]) {
            if (dis[now] + 1 <= dis[num[i]]) {
                dis[num[i]] = dis[now] + 1;
                add2(num[i], now, (i+1)/2);
                if (vis[num[i]] == 0) {
                    vis[num[i]] = 1;
                    q.push(num[i]);
                }
            }
        }
    }
}

int k;
int calc() {
    int now = 1; cnt[1] = 1;
    rep(i,n) {
        if (now >= k) return k;
        now *= cnt[i];
    }
    return now;
}

int flg, m, b[N], ac;
void dfs(int now) {
    if (flg) return;
    if (now == n+1) {
        rep(i,m) cout << b[i];
        cout << '\n';
        ac++;
        if (ac == k) flg = 1;
        return;
    }
    for (int i = h[now]; i; i = nx[i]) {
        b[id[i]] = 1;
        dfs(now+1);
        if (flg) return;
        b[id[i]] = 0;
    }
}

int x, y;
int main() {
    fast;
    cin >> n >> m >> k;
    rep(i,m) { cin >> x >> y; add(x, y); add(y, x); }
    bfs(1);
    cout << calc() << '\n';
    dfs(2);
    return 0;
}