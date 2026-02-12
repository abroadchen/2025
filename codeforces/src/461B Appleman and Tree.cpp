//
// Created by Psy.C on 2026/2/12.
//
/**
f[u][0] = 以u为根的子树中，节点u不被选择的分配方式数量
f[u][1] = 以u为根的子树中，节点u被选择的分配方式数量

如果 w[u] 为1（节点必须被选择）：只有 f[u][1] = 1 有效
如果 w[u] 为0（节点不能被选择）：只有 f[u][0] = 1 有效

f[u][1]: u被选择的方法数
u原本被允许选择 (f[u][1]) 并且子节点v可以被选择或不被选择 (f[v][0]+f[v][1])
或者 u原本不允许但现在可以 (f[u][0]) 并且子节点v必须被选择 (f[v][1])
f[u][0]: u不被选择的方法数
父节点u不被选择 (f[u][0]) 并且子节点v可以被选择或不被选择 (f[v][0]+f[v][1])
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
#define mod 1000000007
using namespace std;
//目标节点 v 和指向下一条边的指针
struct node { int v, nxt; } e[N<<1];

int cnt=0, head[N];//从顶点u出发的第一条边
inline void add(const int u, const int v) {
    cnt++;
    e[cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
    cnt++;
    e[cnt].v = u; e[cnt].nxt = head[v]; head[v] = cnt;
}

int w[N];
ll f[N][2];
void dfs(const int u, const int fa) {
    if (w[u]) f[u][1] = 1; else f[u][0] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        const int v = e[i].v;
        if (v == fa) continue;
        dfs(v, u);
        f[u][1] = (f[u][1]*(f[v][0]+f[v][1])+f[u][0]*f[v][1])%mod;
        f[u][0] = f[u][0]*(f[v][0]+f[v][1])%mod;
    }
}

int n;
int main() {
    fast;
    cin>>n;
    for (int i = 1, x; i <= n-1; ++i) cin >> x, add(x, i);//从x到i的边（父子关系）
    for (int i = 0; i < n; ++i) cin >> w[i];
    dfs(0, -1);
    cout << f[0][1];
    return 0;
}