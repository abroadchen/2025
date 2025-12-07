//
// Created by Psy.C on 2025/12/6.
//
/*
*N = 1000100：最大节点数
d[N]：存储每个节点的度数
fq[N]：标记自环节点
vis[N]：DFS访问标记
flag：标记连通分量中是否存在奇度数节点
cnt：当前连通分量的节点数
n1, n2：分别统计不同类型的连通分量数量
*ver[]：边的目标节点
nxt[]：下一条边的索引
head[]：每个节点的第一条边
tot：边的计数器
 *
*d[x] & 1：检查节点x的度数是否为奇数
如果是奇度数节点：n3++（统计总的奇度数节点数），flag = 1（标记该连通分量有奇度数节点）
标记节点已访问，增加节点计数
递归访问所有未访问的邻居节点
 *
*读取节点数n和边数m
对于每条边：
如果不是自环：增加两个端点的度数，添加双向边
如果是自环：标记该节点有自环
 *
*处理每个连通分量：
如果节点未访问，开始新的DFS
重置flag和cnt
DFS遍历整个连通分量
根据条件分类连通分量：
cnt > 1：节点数大于1
fq[i]：有自环
i == 1：包含节点1
根据是否有奇度数节点分类：
flag = 1：有奇度数节点 → n1++
flag = 0：无奇度数节点 → n2++
 *
*如果只有一个有效连通分量：需要n3/2条边（每对奇度数节点需要一条边连接）
否则：需要连接所有连通分量并处理奇度数节点
 *
*n1 * 2：每个含有奇度数节点的连通分量至少有2个奇度数节点（根据图论定理）
n3 - n1 * 2：超出最小配对需求的奇度数节点数量
(n3 - n1 * 2) / 2：需要额外添加的边来配对这些多余的奇度数节点
 *
 *时间复杂度为O(n+m)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 1000100
using namespace std;

int n, m;
int d[N], fq[N], vis[N], flag, cnt, n1, n2;

int ver[N*3], nxt[N*3], head[N], tot;
void add(const int x, const int y) {
    ver[++tot] = y; nxt[tot] = head[x]; head[x] = tot;
}

int n3;
void dfs(const int x) {
    if (d[x] & 1) { n3++; flag = 1; }
    vis[x] = 1; cnt++;
    for (int i = head[x]; i; i = nxt[i]) {
        const int y = ver[i];
        if (!vis[y]) dfs(y);
    }
}

signed main() {
    fast;
    cin >> n >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        if (x != y) {
            d[x]++, d[y]++;
            add(x, y); add(y, x);
        } else fq[x] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            flag = cnt = 0;
            dfs(i);
            if (cnt > 1 || fq[i] || i == 1) {
                if (flag) n1++;
                else n2++;
            }
        }
    }
    if (n1 + n2 == 1) cout << n3 / 2 << '\n';
    else cout << (n3 - n1 * 2) / 2 + n1 + n2 << '\n';
    return 0;
}