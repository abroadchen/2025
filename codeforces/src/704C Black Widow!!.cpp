//
// Created by Psy.C on 2026/4/19.
//
/**
ctx: 当前深度
col[N]: 节点颜色/访问标记
cnt: 连通分量计数
f[N][2][2]: DP状态数组，f[depth][var_value][result_value]
val[N][2]: 每个节点的初始值

每个节点代表一个布尔变量
每条边代表一个布尔运算
计算有多少种变量赋值方式使得整个表达式结果为1
时间复杂度：O(m)，空间复杂度：O(m)

++ctx: 增加当前深度（DFS序）
col[x] = cnt: 标记节点x属于第cnt个连通分量
当x是起始节点时，初始化DP状态
f[ctx][0][val[x][0]] = 1: 变量值为0，结果为val[x][0]的方案数为1
f[ctx][1][val[x][1]] = 1: 变量值为1，结果为val[x][1]的方案数为1
遍历节点x的所有邻接节点
if (col[p.to]) continue: 避免回头访问已访问的节点
j: 当前节点的变量值（0或1）
k: 当前累积的结果值
l: 下一节点的变量值
j^p.a: 当前节点值与边参数a的异或（表示是否取反）
l^p.b: 下一节点值与边参数b的异或
(j^p.a)|(l^p.b): 两者按位或运算
k^...^val[p.to][l]: 整个布尔运算结果
从状态f[ctx][j][k]转移到f[ctx+1][l][new_result]
new_result = k^((j^p.a)|(l^p.b))^val[p.to][l]
继续DFS遍历下一节点

与第一个DFS类似，但状态初始化依赖于参数c
bo[c][id]: 避免重复访问同一条边（按c分类）
bo[c][id] = 1: 标记边id在当前c值下已访问
to == st: 发现回到起始节点，形成了环
int op = k^((j^a)|(c^b)): 计算环闭合时的最终结果
add(g[cnt][op], f[ctx][j][k]): 将结果累加到该连通分量的最终答案
与第一个DFS类似的状态转移
递归处理非环路径


类型1操作: 单变量操作，修改某个节点的初始值
x < 0: 修改节点-x的val[0]（对应负值）
x > 0: 修改节点x的val[1]（对应正值）
如果x和y指向同一节点（自环）
根据符号设置相应的val值
++tot: 边编号递增
e[abs(x)].push_back({...}): 添加边
abs(y): 目标节点
x<0, y<0: 布尔参数，表示是否取反
tot: 边ID
deg[...]++: 度数统计
找到未访问且度数≤1的节点（树形结构）
dfs(i, i): 使用第一个DFS处理
g[cnt][0] = (f[ctx][0][0] + f[ctx][1][0]) % mod: 计算该连通分量结果为0的方案数
g[cnt][1] = (f[ctx][0][1] + f[ctx][1][1]) % mod: 计算结果为1的方案数
init(): 清空DP数组
处理剩余的连通分量（有环结构）
dfs(i, i, 0) 和 dfs(i, i, 1): 分别以0和1为起始条件处理
两次DFS确保考虑所有可能的环闭合情况
h[0][0] = 1: 初始状态，0个连通分量结果为0的方案数为1
h[i][j]: 前i个连通分量，最终结果为j的方案数
h[i-1][k]*g[i][j^k]: 前i-1个结果为k，第i个结果为j^k，整体为j
cout << h[cnt][1] << '\n': 输出最终结果为1的总方案数

时间复杂度：O(n + m)，空间复杂度：O(m)
 */

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 1e5+5, mod = 1e9+7;

struct node { int to, a, b, id; };
vector<node> e[N];

void add(int& x, int y) {
    x = x + y >= mod ? x + y - mod : x + y;
}

int ctx, col[N], cnt, f[N][2][2], val[N][2];
void dfs(int x, int st) {
    ++ctx; col[x] = cnt;
    if (x == st)
        f[ctx][0][val[x][0]] = f[ctx][1][val[x][1]] = 1;
    for (auto p : e[x]) {
        if (col[p.to]) continue;
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                for (int l = 0; l < 2; ++l)
                    add(f[ctx+1][l][k^((j^p.a)|(l^p.b))^val[p.to][l]],
                        f[ctx][j][k]);
        dfs(p.to, st);
    }
}

int bo[2][N], g[N][2];
void dfs(int x, int st, int c) {
    ++ctx; col[x] = cnt;
    if (x == st) f[ctx][c][val[x][c]] = 1;
    for (auto [to, a, b, id] : e[x]) {
        if (bo[c][id]) continue;
        bo[c][id] = 1;
        if (to == st) {
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k) {
                    int op = k^((j^a)|(c^b));
                    add(g[cnt][op], f[ctx][j][k]);
                }
        } else {
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    for (int l = 0; l < 2; ++l)
                        add(f[ctx+1][l][k^((j^a)|(l^b))^val[to][l]],
                            f[ctx][j][k]);
            dfs(to, st, c);
        }
    }
}

void init() {
    for (int i = 1; i <= ctx; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                f[i][j][k] = 0;
}


int n, m, tot, deg[N], h[N][2];
int main() {
    fast;
    n = rd(), m = rd();
    for (int i = 1, k; i <= n; ++i) {
        k = rd();
        if (k == 1) {//单变量操作，更新val值
            int x = rd();
            if (x < 0) val[-x][0] ^= 1;
            else val[x][1] ^= 1;
        } else {// 双变量操作，添加边
            int x = rd(), y = rd();
            if (abs(x) == abs(y)) {
                if (x < 0 && y < 0) val[abs(x)][0] ^= 1;
                else if (x > 0 && y > 0) val[abs(x)][1] ^= 1;
                else val[abs(x)][0] ^= 1, val[abs(x)][1] ^= 1;
                continue;
            }
            ++tot;
            //x<0, y<0: 记录变量是否取反
            e[abs(x)].push_back({abs(y), x<0, y<0, tot});
            e[abs(y)].push_back({abs(x), y<0, x<0, tot});
            deg[abs(x)]++; deg[abs(y)]++;
        }
    }
    for (int i = 1; i <= m; ++i)
        if (!col[i] && deg[i] <= 1) {//先处理树形结构（度数≤1的节点）
            ++cnt; ctx = 0;
            dfs(i, i);
            g[cnt][0] = (f[ctx][0][0] + f[ctx][1][0]) % mod;
            g[cnt][1] = (f[ctx][0][1] + f[ctx][1][1]) % mod;
            init();
        }
    for (int i = 1; i <= m; ++i)
        if (!col[i]) {//处理有环结构
            ++cnt; ctx = 0;
            dfs(i, i, 0);
            init(); ctx = 0;
            dfs(i, i, 1);
            init();
        }
    h[0][0] = 1;//前i个连通分量，结果为j的方案数
    for (int i = 1; i <= cnt; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                add(h[i][j], 1ll*h[i-1][k]*g[i][j^k]%mod);
    cout << h[cnt][1] << '\n';//结果为1的方案数
    return 0;
}