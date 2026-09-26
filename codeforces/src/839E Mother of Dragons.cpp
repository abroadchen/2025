//
// Created by Psy.C on 2026/9/26.
//
/**
N = 42：节点（顶点）数量上限。
mx：记录找到的最大团的顶点数。
s[st][e]：搜索到第 st 层时，当前待选（未定）可加入团的候选顶点列表。
nv[i][j]：邻接矩阵。nv[i][j] = 1 表示 i 与 j 之间有边（相邻），0 表示无边。
no[st][i]：搜索到第 st 层时，已经被排除（确定不加入团）的顶点列表
dfs(st, all, sc, nc)：
st：当前递归层数 / 级数。
all：当前已经选入团的顶点数。
sc：候选顶点集合 s[st] 的大小（还剩多少候选可加入）。
nc：被排出的顶点集合 no[st] 的大小。
基线条件：当 sc == 0（候选顶点用完了）时：

如果 nc == 0（没有剩下的待排除顶点），说明这是个"完整"的团，更新 mx = max(mx, all)。
这个判断逻辑对应 "Bron–Kerbosch" 变体：当候选集（P）为空时，如果排除集（排出的 X）也为空，则当前集合就是一个最大团（极大且极大）。
u = s[st][1]：取候选集合的第一个顶点作为枢轴（pivot）‍。
循环遍历候选集中的每个顶点 v。
if (nv[u][v]) continue;：如果 u 与 v 相邻（有边）则跳过。
这是 Bron–Kerbosch 的枢轴优化思想 / 一种剪枝技巧：凡是和枢轴 u 相邻的顶点 v，最终要么已经被其它路径处理，可以跳过，避免重复搜索。这里选择"跳过与 u 相邻的顶点"，只处理与 u 不相邻的 v。
构建下一层的候选集合 s[st+1] = 所有"与 v 相邻"的候选顶点：

第一个循环：处理候选集中下标小于 e 的顶点 s[st][i]。要求它既与 u 相邻又与 v 相邻（nv[u][·] && nv[v][·]）才加入新候选。
第二个循环：处理候选集中下标大于 e 的顶点 s[st][i]。要求它与 v 相邻（nv[v][·]）即可加入。
这样做的原因：当把一个顶点 v 加入团后，新的候选集只能是从"与 v 相邻"的顶点中选。而它同时还要满足之前 u 的约束（对于已在前面处理过的候选）。这是复用枢轴 u 的信息对候选集进一步压缩，属于正确但较"偏门"的该剪枝实现细节。
构建下一层的排除集合 no[st+1]：从当前被排除的顶点里，挑出那些与 v 相邻的，作为下一层的排除集。
因为如果某个被排除顶点不与 v 相邻，那么在加入了 v 的这条分支里，它还能留在后面考虑；只有与 v 相邻的排除顶点，才会真正"卡住"这条分支的扩展
递归下一层：st+1，顶点数 all+1，候选 nsc，排除 nnc。
递归返回后，把当前顶点 v 从候选移动到排除集（no[st][++nc] = v），继续处理候选集中的下一个顶点（即"不选 v，改为尝试别的顶点"的分支）。
这完整实现了 Bron–Kerbosch 搜索：

每次选一个顶点 v 加入团（分支），并更新候选集（与 v 相邻者）与排除集。
回退时把 v 放入排除集，避免它再被选。
通过不断枚举，最终 mx 存下最大团的顶点数（即图中最大的完全子图的点数）。

读入 n（顶点数）和 k（题目给的另一个输入，通常是一个人数/上限）。
读入 n×n 的邻接矩阵 nv。
初始候选集 s[0] = 所有顶点（1..n）。
从第 0 层开始 DFS：dfs(0, 0, n, 0)。
mx 得到最大团大小
计算最终答案：
先 k/mx。
再 ans = ans * ans * mx * (mx-1) / 2.0。
展开：ans = (k/mx) * (k/mx) * mx*(mx-1)/2 = k² * (mx-1) / (2*mx)。

这个公式通常是某道题的结论式（比如 "SSH/网络团内互相安全通信的对数乘法"：在一个大小为 mx 的最大团内，任取两个节点有 mx*(mx-1)/2 条边，每条边相关的某种概率/计数是 (k/mx)²，于是总期望 = 边数 × 概率）。
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 42;

int mx, s[N][N], nv[N][N], no[N][N];
void dfs(int st, int all, int sc, int nc) {
    if (!sc) {
        if (!nc) mx = max(mx, all);
        return;
    }
    int u = s[st][1];
    for (int e = 1; e <= sc; ++e) {
        int v = s[st][e];
        if (nv[u][v]) continue;
        int nsc = 0, nnc = 0;
        for (int i = 1; i < e; ++i)
            if (nv[u][s[st][i]] && nv[v][s[st][i]])
                s[st+1][++nsc] = s[st][i];
        for (int i = e+1; i <= sc; ++i)
            if (nv[v][s[st][i]])
                s[st+1][++nsc] = s[st][i];
        for (int i = 1; i <= nc; ++i)
            if (nv[v][no[st][i]])
                no[st+1][++nnc] = no[st][i];
        dfs(st+1, all+1, nsc, nnc);
        no[st][++nc] = v;
    }
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, k;
int main() {
    rd(n); rd(k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) rd(nv[i][j]);
    for (int i = 1; i <= n; ++i) s[0][i] = i;
    dfs(0, 0, n, 0);
    long double ans = (long double)k/mx;
    ans = ans*ans*mx*(mx-1)/2.0;
    printf("%.10f", (double)ans);
    return 0;
}