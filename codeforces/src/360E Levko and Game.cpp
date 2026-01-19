//
// Created by Psy.C on 2026/1/19.
//
/**
* cnt：边的编号计数器
nxt[i]：链式前向星的下一个节点
head[u]：顶点u的第一条边的编号
fr[i]：第i条边的起点
to[i]：第i条边的终点
el[i]：第i条边的左端点（最小权重）
er[i]：第i条边的右端点（最大权重）
 *
*使用链式前向星添加边(u,v)
边的权重范围为[l,r]
nxt[cnt] = head[u]：新边连接到u的原有边链
head[u] = cnt：更新u的首条边
 *
*从源点s开始，使用er[i]（最大权重）进行松弛
队列操作实现负权边的最短路
 *
*a[N], b[N]：两个距离数组
s1, s2：两个起始点
m：固定边数
k：可变边数
t：目标点
 *
*x=0表示判断是否必胜，x=1表示判断是否平局
flag：循环标志，用于迭代更新边权重
*遍历可变边（编号从m+1到m+k）
如果从s1到达该边起点的距离小于从s2到达该边起点的距离加上x
且该边权重区间不是单点（el[i] != er[i]）
则将该边权重设为最小值el[i]，并设置flag=1继续迭代
*如果从s1到目标点t的距离小于从s2到t的距离加上x
输出相应结果（WIN或DRAW）
输出所有可变边的最终权重
返回true表示找到了解
 *
*前m条边为固定权重边（l=r=z）
后k条边为可变权重边（权重在[l,r]范围内）
*首先尝试判断是否能必胜（x=0）
如果不能必胜，尝试判断是否能平局（x=1）
如果都不能，则输出LOSE
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 10001
using namespace std;

int cnt, nxt[N<<1], head[N], fr[N<<1], to[N<<1];
ll el[N<<1], er[N<<1];
void add(const int u, const int v, const int l, const int r) {
    nxt[++cnt] = head[u]; fr[cnt] = u; to[cnt] = v;
    el[cnt] = l; er[cnt] = r; head[u] = cnt;
}

int q[N*64];
bool vis[N];
void spfa(ll dis[N], const int s) {
    memset(dis, 0x7f, sizeof(ll)*N);
    memset(vis, 0, sizeof(vis));
    int l = 0, r = 0;
    q[r++] = s; dis[s] = 0; vis[s] = true;
    while (l < r) {
        const int u = q[l++];
        for (int i = head[u]; i; i = nxt[i]) {
            if (dis[to[i]] > dis[u] + er[i]) {
                dis[to[i]] = dis[u] + er[i];
                if (!vis[to[i]]) {
                    q[r++] = to[i];
                    vis[to[i]] = true;
                }
            }
        }
        vis[u] = false;
    }
}

ll a[N], b[N];
int s1, s2, m, k, t;
bool ok(const int x) {
    int flag = 1;
    while (flag) {
        flag = 0;
        spfa(a, s1); spfa(b, s2);
        for (int i = m + 1; i <= m + k; ++i) {
            if (a[fr[i]] < b[fr[i]] + x && el[i] != er[i])
                er[i] = el[i], flag = 1;
        }
        if (a[t] < b[t] + x) {
            cout << (x ? "DRAW" : "WIN") << '\n';
            for (int i = m + 1; i <= m + k; ++i) cout << er[i] << ' ';
            return true;
        }
    }
    return false;
}

int main() {
    fast;
    int n, x, y, z, l, r; cin >> n >> m >> k >> s1 >> s2 >> t;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y >> z;
        add(x, y, z, z);
    }
    for (int i = 1; i <= k; ++i) {
        cin >> x >> y >> l >> r;
        add(x, y, l, r);
    }
    if (!ok(0)) if (!ok(1)) cout << "LOSE\n";
    return 0;
}