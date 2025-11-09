//
// Created by Psy.C on 2025/10/12.
//
/*
*N = 500010：最大节点数
n：节点总数
stk[N]：栈，用于寻找环
tp：栈顶指针
loop[N]：存储环上的节点
len：环的长度
vis[N]：访问标记数组
flag：找到环的标志
 *
*Edge结构体包含目标节点v、权重w和下一条边的索引nxt
e[N]：边数组
head[N]：每个节点的第一条边索引
tot：边的计数器
add函数用于添加无向边（实际添加两条有向边）
 *
*使用DFS寻找图中的唯一环：

u：当前节点，f：父边索引
如果已找到环则返回
标记当前节点为已访问并入栈
遍历所有邻接边，避免走回父边（i != (f ^ 1)利用了边成对存储的特性）
如果遇到已访问节点，说明找到了环，从栈中提取环上的节点
递归访问未访问的邻接节点
回溯时出栈
 *
*计算以每个节点为根的子树大小和子树内距离和：

sz[N]：子树大小
tr[N]：子树内所有节点到根节点的距离和
标记节点为已访问，初始化子树大小为1
递归处理所有未访问的子节点
累加子树大小和距离和（包括通过当前边到达子树的贡献）
 *
*通过树形DP的换根技术重新计算每个节点作为根时的答案：

当根从u变为v时，v的子树节点距离减少e[i].w，其余节点距离增加e[i].w
变化量为：e[i].w * (n - sz[e[i].v]) - e[i].w * sz[e[i].v] = e[i].w * (n - 2 * sz[e[i].v])

 *
*处理环：

从节点1开始寻找环
清空访问标记，重新标记环上的节点
对环上每个节点进行DFS计算其子树信息
将环复制一份用于处理环的循环特性
初始化环上节点的答案为子树距离和
 *
*计算环上边的权重和前缀和：

lst：上一条边的索引
e[j].v：第j条边的目标节点
loop[i + 1]：环中下一个节点（由于loop数组已复制，所以可以用i+1）
这个条件是确保找到的是指向下一个环节点的边


提取环上相邻节点间的边权重
将权重数组复制一份，计算总和
计算前缀和数组
 *
*正向处理环上节点，计算通过环连接的其他子树贡献：

维护滑动窗口内的统计信息
对每个节点，计算环上其他节点到它的距离贡献
 *反向处理环上节点，计算反方向的贡献
 *
 *
*最终处理：

重新标记环上节点为已访问
对环上每个节点进行第二次DFS，完成所有节点的答案计算
输出所有节点的答案
这个程序解决的是在"环套树"（unicyclic graph）中计算每个节点到其他所有节点距离和的问题，时间复杂度为O(N)
 *
 *
 */
#include <ios>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 5e5+10;
int n, stk[N], tp, loop[N], len;
bool vis[N], flag;

struct Edge {
    int v, w, nxt;
} e[N];
int head[N], tot;
void add(int u, int v, int w) {
    e[++tot] = { v, w, head[u] };
    head[u] = tot;
}

void find(int u, int f) {
    if (flag) return;
    vis[u] = 1;
    stk[++tp] = u;
    for (int i = head[u]; i; i = e[i].nxt) if (i != (f ^ 1)) {
        if (flag) break;
        if (vis[e[i].v]) {
            while (stk[tp] != e[i].v) loop[++len] = stk[tp--];
            loop[++len] = e[i].v;
            flag = true;
            return;
        } else find(e[i].v, i);
    }
    tp--;
}

ll sz[N], tr[N], ans[N], a[N], pre[N];
void dfs(int u) {
    vis[u] = 1; sz[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) if (!vis[e[i].v]) {
        dfs(e[i].v);
        sz[u] += sz[e[i].v];
        tr[u] += tr[e[i].v] + 1ll * e[i].w * sz[e[i].v];
    }
}

void dfs2(int u) {
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) if (!vis[e[i].v]) {
        ans[e[i].v] = ans[u] + e[i].w * (n - sz[e[i].v] * 2);
        dfs2(e[i].v);
    }
}

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n; tot = 1;
    for (int i = 1, u, v, w; i <= n; ++i) {
        cin>>u>>v>>w;
        add(u, v, w);
        add(v, u, w);
    }
    find(1, 0);
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= len; ++i) vis[loop[i]] = 1;
    for (int i = 1; i <= len; ++i) {
        dfs(loop[i]);
        loop[i + len] = loop[i];
        ans[loop[i]] = tr[loop[i]];
    }
    ll s(0);
    for (int i = 1, lst = 0; i <= len; ++i) {
        for (int j = head[loop[i]]; j; j = e[j].nxt) {
            if (j != (lst ^ 1) && e[j].v == loop[i + 1]) {
                a[i] = e[j].w;
                lst = j;
                break;
            }
        }
    }
    for (int i = 1; i <= len; ++i) a[i + len] = a[i], s += a[i];
    for (int i = 1; i <= len * 2; ++i) pre[i] = pre[i - 1] + a[i];

    int pt(1); ll sum(0), cnt(0), cur(0);
    for (int i = 1; i <= len; ++i) {
        sum += tr[loop[i]];
        cnt += sz[loop[i]];
        cur += pre[i - 1] * sz[loop[i]];
    }
    for (int i = len + 1; i <= len * 2; ++i) {
        while (pt <= i && pre[i - 1] - pre[pt - 1] > s - pre[i - 1] + pre[pt - 1]) {
            sum -= tr[loop[pt]];
            cnt -= sz[loop[pt]];
            cur -= pre[pt - 1] * sz[loop[pt]];
            pt++;
        }
        ans[loop[i]] += sum + cnt * pre[i - 1] - cur;
        sum += tr[loop[i]];
        cnt += sz[loop[i]];
        cur += pre[i - 1] * sz[loop[i]];
    }
    pt = len * 2; cnt = sum = cur = 0;
    for (int i = len * 2; i >= len + 1; --i) {
        sum += tr[loop[i]];
        cnt += sz[loop[i]];
        cur += pre[i - 1] * sz[loop[i]];
    }
    for (int i = len; i >= 1; --i) {
        while (pt >= i && pre[pt - 1] - pre[i - 1] >= s - pre[pt - 1] + pre[i - 1]) {
            sum -= tr[loop[pt]];
            cnt -= sz[loop[pt]];
            cur -= pre[pt - 1] * sz[loop[pt]];
            pt--;
        }
        ans[loop[i]] += sum + cur - cnt * pre[i - 1];
        sum += tr[loop[i]];
        cnt += sz[loop[i]];
        cur += pre[i - 1] * sz[loop[i]];
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= len; ++i) vis[loop[i]] = 1;
    for (int i = 1; i <= len; ++i) dfs2(loop[i]);
    for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
    return 0;
}