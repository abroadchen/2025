//
// Created by Psy.C on 2026/9/27.
//
/**
sz[x]：x 的子树大小。
mx[x]：删掉 x 后，剩余各块中的最大块大小。
满足两个条件（sz[x]*2>=n 且 mx[x]*2<=n）的点标为"候选中心" rt，即树的重心/平衡点（删去后各连通块都不超过 n/2）。
注意：这段代码把满足条件的点都标为 rt，而不只是一个。后面会据此遍历
对一棵子树做后序遍历，把访问顺序压进 st（top 从 1 起）。fa[x] 记录的正是这趟 DFS 里 x 的父节点
以重心 v 为"枢纽"，对它的每一棵子树，用后序序列构造两类三点形——一类沿父子链 (子,父,孙)，一类逆序回绕到子树的另一个顶端。update 把三元组顺序存进 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

struct edge { int t, nxt; } e[N<<1];
int tot, head[N];
void add(int x, int y) {
    e[++tot] = {.t = y, .nxt = head[x]}, head[x] = tot;
}

int sz[N], mx[N], rt[N], n;
void dfs(int x, int fa) {
    sz[x] = 1, mx[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].t != fa) {
            dfs(e[i].t, x);
            sz[x] += sz[e[i].t];
            mx[x] = max(mx[x], sz[e[i].t]);
        }
    }
    if (sz[x]*2 >= n && mx[x]*2 <= n) rt[x] = 1;
}

int ans[N<<2][3], cnt;
void update(int x, int y, int z) {
    ans[++cnt][0] = x; ans[cnt][1] = y; ans[cnt][2] = z;
}

int fa[N], st[N], top;
void solve(int x) {
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].t != fa[x])
            fa[e[i].t] = x, solve(e[i].t);
    }
    st[++top] = x;//后序入栈
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    n = rd();
    for (int i = 1, x, y; i < n; ++i) {
        x = rd(), y = rd();
        add(x, y); add(y, x);
    }
    dfs(1, 0);
    for (int v = 1; v <= n; ++v) {
        if (!rt[v]) continue;//只处理重心
        for (int i = head[v]; i; i = e[i].nxt) {
            if (!rt[e[i].t]) {//对每个"非重心"相邻子树
                fa[e[i].t] = v; st[top=1] = v;//栈底放重心 v
                solve(e[i].t);//后序压入整棵子树，top 指向 `e[i].t` 子树序列
                update(v, e[i].t, st[2]);//第 1 条：重心-子树根-次顶
                for (int j = 2; j < top; ++j)
                    if (st[j+1] != fa[st[j]])
                        update(st[j], fa[st[j]], st[j+1]);//段 1：顺父子链
                for (int j = top-3; j >= 1; --j)
                    update(st[j], st[j+1], st[top-1]);//段 2：回绕到栈底倒数第二
            }
        }
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i)
        cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
    return 0;
}