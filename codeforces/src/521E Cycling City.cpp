//
// Created by Psy.C on 2026/3/1.
//
/**
up[N]：记录回到祖先节点的路径 记录每个节点的回边

参数：now 当前节点，pre 父边编号（用于避免走回头路）
标记访问：vis[now] = true
遍历邻接边：for (int i = head[now]; i; i = e[i].nxt)
未访问过的边：if (i != pre && !vis[e[i].to])
标记边被访问：e[i].vis = true
更新深度：dep[e[i].to] = dep[now] + 1
记录父节点：fa[e[i].to] = now
递归DFS：dfs(e[i].to, i^1)，注意i^1是反向边
回边情况：dep[e[i].to] < dep[now] 表示找到回边形成环
第一次发现回边：up[now] = e[i].to
第二次发现回边：找到两个简单环的情况
u ^= v ^= u ^= v：交换u和v的值
构造并输出第一个环
输出第二个环
exit(0)：直接退出程序

在已构建的DFS树中寻找第二个环
int res = up[now] ? now : 0：如果当前节点有回边，则res为当前节点，否则为0
遍历已访问的边：if (e[i].vis)
递归处理子节点：int t = dfs(e[i].to)
if (up[t] == now) t = 0：如果子节点的回边指向当前节点，则重置t
if (res && t)：如果找到了两个连接到祖先的节点，则找到两个共享一个节点的环
构造并输出三个路径


对每个未访问的连通块进行DFS
if (!dep[i])：如果节点i未被访问过
dep[i] = 1：设置深度为1
dfs(i, 0)：从节点i开始DFS
对每个DFS树根节点再次DFS，寻找共享节点的两个环


 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+1;
struct node { int to, nxt; bool vis; } e[N<<1];

bool vis[N];
int head[N], dep[N], fa[N], up[N];
vector<int> ans;

///输出ans数组中的路径并清空
void out() {
    printf("%d", ans.size());
    for (const int an : ans) printf(" %d", an);
    putchar('\n');
    ans.clear();
}

///从当前节点到目标节点获取路径
///从当前节点向上递归到目标节点，然后将路径压入ans数组
void get(const int now, const int& ed) {
    if (now != ed) get(fa[now], ed);
    ans.push_back(now);
}

void dfs(const int now, const int pre) {
    vis[now] = true;
    for (int i = head[now]; i; i = e[i].nxt) {
        if (i != pre && !vis[e[i].to]) {
            e[i].vis = true;//标记边为已访问
            dep[e[i].to] = dep[now] + 1;//设置目标节点深度
            fa[e[i].to] = now;//设置目标节点的父节点
            dfs(e[i].to, i^1);//递归访问目标节点
        } else {//处理的是已经访问过的节点，即回边
            //确保是向上回溯的边（祖先节点）排除直接回边
            if (dep[e[i].to] < dep[now] && i != pre) {
                //从节点now能直接回到的最近祖先节点
                if (!up[now]) up[now] = e[i].to;//该回边指向的祖先节点
                else {
                    puts("YES");
                    //第一次回边指向的祖先 第二次回边指向的祖先
                    int u = up[now], v = e[i].to;
                    if (dep[u] < dep[v]) u ^= v ^= u ^= v;//使u的深度更浅
                    //从now经过父节点路径到u，形成一个简单环
                    ans.push_back(now);
                    for (int s = now; s != u; s = fa[s])
                        ans.push_back(fa[s]);
                    out();
                    printf("2 %d %d\n", now, u);
                    ans.push_back(now);
                    get(u, v);//获取从u到v的路径
                    out();
                    exit(0);
                }
            }
        }
    }
}

int dfs(const int now) {
    int res = up[now] ? now : 0;
    //只遍历在第一个DFS中被标记为已访问的边（树边）
    for (int i = head[now]; i; i = e[i].nxt) if (e[i].vis) {
        int t = dfs(e[i].to);//子树中具有回边的节点
        if (up[t] == now) t = 0;//子节点t的回边直接指向当前节点
        //res：当前子树中具有回边的节点
        //t：另一子树中具有回边的节点
        if (res && t) {
            int u = up[res], v = up[t];//回边指向的祖先
            if (dep[u] < dep[v]) u ^= v ^= u ^= v, res ^= t ^= res ^= t;
            puts("YES");
            get(res, now), ans.push_back(u);//从res到now再到u
            out();
            ans.push_back(now);
            for (int s = now; s != u; s = fa[s])//从now沿着父节点路径回到u
                ans.push_back(fa[s]);
            out();
            get(t, now), get(u, v);//从t到now再到v
            out();
            exit(0);
        }
        if (t) res = t;
    }
    return res;
}

int n, m, cnt=1;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        e[++cnt] = {v, head[u]}, head[u] = cnt;
        e[++cnt] = {u, head[v]}, head[v] = cnt;
    }
    for (int i = 1; i <= n; ++i)
        if (!dep[i]) dep[i] = 1, dfs(i, 0);
    for (int i = 1; i <= n; ++i)
        if (dep[i] == 1) dfs(i);
    puts("NO");
    return 0;
}