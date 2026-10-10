//
// Created by Psy.C on 2026/10/10.
//
/**
前向星链式邻接表：num 邻居点、id 边的编号、nxt 下一条边。无向边 (x,y) 拆成两条有向边，都记原边编号 i
t[i]=1 表示边 i 是生成树边；非树边（回边）t 保持 0。
每次进入未访问邻居就 DFS，后序遍历返回时：
把当前点 now 的"盈余流量" c[now] 记到通往父节点的树边上 w[id[x]]；
父节点吸收掉这份流量：c[fa] -= c[now]；
当前点清零。
含义：在树上做"下放/归并"，把每个非根点的需求 c 通过树边逐级汇总到根（1号点）。最终 c[1] = 所有点流量沿树边汇总到根后的总不平衡量。若 c[1]==0，则只用树边就能平衡所有点（无需回边），输出 YES 和每条边流量
先跑一次 DFS 树边归并。
若 c[1]==0：所有点已平衡，输出各树边流量 w[i]。
若 c[1] 为奇：无解 NO（因为一条回边会改变两端点的奇偶，无法凑成整数分配）。
若 c[1] 为偶：尝试用一条合适的回边（非树边）‍来兜住根的剩余流量
遍历每条非树边，条件 (dep[x]+dep[y])%2==0：回边两端深度差为偶数（保证这条边是"连接同奇偶层的点"，能在不改变整体奇偶性的前提下承载流量）。
把该回边赋流量 ±c[1]/2（根剩余量的一半），在两端抵消一部分，然后重新 DFS 归并。
若此时能平衡（c[1]==0）则 YES 并输出各边流量；否则 NO。
关键思路：非树回边提供额外的"循环"自由度，用于消除根上剩余的、树边无法消掉的那部分不平衡量；而奇偶条件保证整数可行性
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 4e5+5;

int head[N], tot, num[N], id[N], nxt[N];
void add(int x, int y, int z) {
    num[++tot] = y; id[tot] = z; nxt[tot] = head[x]; head[x] = tot;
}

int dep[N], v[N], f[N], t[N], w[N], c[N];
void dfs(int now, int fa, int h) {
    dep[now] = h; v[now] = 1;
    int x = -1; f[now] = fa;
    for (int i = head[now]; i; i = nxt[i]) {
        if (num[i] == fa) x = i;//记录连向父节点的"树边"位置
        else {
            if (v[num[i]] == 0)//树边标记 t=1，递归
                t[id[i]] = 1, dfs(num[i], now, h+1);
        }
    }
    if (x != -1) {//处理完子树后，沿树边向父节点"推"流量
        w[id[x]] += c[now];
        c[fa] -= c[now];
        c[now] = 0;
    }
}

int x[N], y[N];
signed main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= m; ++i) {
        cin >> x[i] >> y[i];
        add(x[i], y[i], i); add(y[i], x[i], i);
    }
    dfs(1, 0, 0);
    if (c[1] == 0) {
        cout << "YES\n";
        for (int i = 1; i <= m; ++i) cout << w[i] << '\n';
        return 0;
    }
    if (c[1]%2 == 0) {
        int flg = 0;
        for (int i = 1; i <= m; ++i) {
            if (t[i] == 1) continue;//只看非树边
            if ((dep[x[i]]+dep[y[i]])%2 == 0) {//奇偶校验：该回边是否"奇偶合适"
                if (dep[x[i]]%2 == 0) w[i] = c[1]/2; else w[i] = -c[1]/2;
                c[x[i]] -= w[i]; c[y[i]] -= w[i];
                memset(v, 0, sizeof(v));
                dfs(1, 0, 0);//重跑归并
                flg = 1;
                break;
            }
        }
        if (flg) {
            cout << "YES\n";
            for (int i = 1; i <= m; ++i) cout << w[i] << '\n';
        } else cout << "NO\n";
    } else cout << "NO\n";
    return 0;
}