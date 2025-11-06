//
// Created by Psy.C on 2025/11/6.
//
/*
*N：最大节点数
n：节点总数
fa[N]：父节点数组
s[N]：节点状态数组
nxt[N]、son[N]：邻接表相关数组，用于构建树结构
v[N]：访问标记数组
r：根节点标记
g[N]：最优子节点记录数组
w：临时边计数器
len：匹配边计数器
f[N][2]：动态规划状态数组
e[N]：临时边数组
ans：最终结果
o[N]：输出边数组
 *
*深度优先搜索函数，实现树形动态规划：
f[x][0]：节点x不被选中的最优解
f[x][1]：节点x被选中的最优解
对每个子节点递归计算，更新当前节点的状态
s[x]^s[i]：异或运算计算权重
 *
*收集最优匹配的边：
根据flag标志和最优子节点g[x]决定是否选择当前边
将选中的边存储到e数组中
 *
*匹配函数，寻找最优匹配方案：
找到环并标记访问
尝试两种情况（断开环的不同位置），选择更优解
累加结果并保存匹配边
 *
 *f[i][0]：子节点i不被匹配时的收益
+ make_pair(1, s[x]^s[i])：加上选择边(x,i)带来的收益
- f[i][1]：减去子节点i原本被匹配的收益
 *
处理环状结构：在一个环中尝试两个不同的"断点"
比较两种不同的解决方案，选择更优的一种
因为在环状图中，选择不同的起始点可能会得到不同的匹配结果*
 *
 */
#include <cstdio>
#include <utility>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

int read() {
    int x(0); char ch(getchar()); bool f(1);
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = 0;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    return f ? x : -x;
}

typedef pair<int,int> pii;
const int N = 100005;
int n, fa[N], s[N], nxt[N], son[N], v[N], r, g[N], w, len;
pii f[N][2], e[N], ans, o[N];

pii operator+(pii a, pii b) { return {a.first + b.first, a.second + b.second}; }
pii operator-(pii a, pii b) { return {a.first - b.first, a.second - b.second}; }

void dfs(int x) {
    v[x] = 1; f[x][1] = f[x][0] = {0, 0}; g[x] = 0;
    for (int i = son[x]; i; i = nxt[i]) if (i != r) {
        dfs(i); f[x][0] = f[x][0] + f[i][1];
        pii t = f[i][0] + make_pair(1, s[x]^s[i]) - f[i][1];
        if (t > f[x][1]) f[x][1] = t, g[x] = i;
    }
    f[x][1] = f[x][1] + f[x][0];
}

void get(int x, int flag) {
    for (int i = son[x]; i; i = nxt[i]) if (i != r) {
        if (flag && g[x] == i) e[w++] = {x, i}, get(i, 0);
        else get(i, 1);
    }
}


void match(int x) {
    for (; !v[x]; x = fa[x]) v[x] = 1;
    pii res(0, 0);
    for (int i = 2; i; --i, x = fa[x]) {
        r = x, dfs(x);
        if (f[x][1] > res) {
            res = f[x][1];
            w = 0;
            get(x, 1);
        }
    }
    ans = ans + res;
    for (int i = 0; i < w; ++i) o[len++] = e[i];
}


int main() {
    n = read();
    rep(i,n) {
        fa[i] = read();
        s[i] = read() - 1;
        nxt[i] = son[fa[i]];
        son[fa[i]] = i;
    }
    rep(i,n) if (!v[i]) match(i);
    printf("%d %d\n", ans.first, ans.second);
    for (int i = 0; i < len; ++i) printf("%d %d\n", o[i].first, o[i].second);
    return 0;
}