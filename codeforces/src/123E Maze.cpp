//
// Created by Psy.C on 2025/11/17.
//
/*
*N = 100100：最大节点数
n：节点总数
u, v：临时变量，用于读取边
a[N], b[N]：每个节点的两种属性值
sa, sb：所有节点a值和b值的总和
s[N]：子树大小数组
e[N]：邻接表，存储树的边
ans：结果累加器
 *
*x：当前节点
f：父节点
初始化当前子树大小为1（包含自己）
*遍历当前节点的所有邻居（除了父节点）
递归处理子节点
更新当前子树大小：s[x] += s[i]
累加子树a值：a[x] += a[i]
关键计算：ans += 1. * b[x] * s[i] * a[i]
这表示节点x与子树i中所有节点的贡献
*节点x与其祖先节点（不在当前子树中的节点）的贡献
n - s[x]：不在当前子树中的节点数
sa - a[x]：不在当前子树中的节点a值之和
 *
 *O(n)：每个节点访问一次
 */
#include <cstdio>
#include <vector>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

const int N = 100100;
int n, u, v, a[N], b[N], sa, sb, s[N];
vector<int> e[N];
double ans;

void dfs(int x, int f) {
    s[x] = 1;
    for (int i : e[x]) if (i != f) {
        dfs(i, x);
        s[x] += s[i];
        a[x] += a[i];
        ans += 1. * b[x] * s[i] * a[i];
    }
    ans += 1. * b[x] * (n - s[x]) * (sa - a[x]);
}


int main() {
    scanf("%d",&n);
    rep(i,n-1) {
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    rep(i,n) {
        scanf("%d%d",&a[i], &b[i]);
        sa += a[i];
        sb += b[i];
    }
    dfs(1, 0);
    printf("%.20f\n",ans / sa / sb);
    return 0;
}