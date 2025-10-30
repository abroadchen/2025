//
// Created by Psy.C on 2025/10/30.
//
/*
*n, m: 节点数和边数
fi[N]: 邻接表头指针数组
cnt: 边计数器
fa[N]: 并查集父节点数组
du[N]: 度数数组
t, f, O, ID: 标志和临时变量
jd[N]: 边标记数组
dfn[N<<2]: DFS序列数组(大小为N*4)
tim: 时间戳计数器
tot: 边总数计数器
ans[N]: 答案数组
num: 答案计数器
 *
*链式前向星节点结构体：to表示目标节点，nxt指向下一条边
p[N<<1]数组存储所有边(大小为2*N)
*边结构体：x,y表示两个端点，id为边的编号
e[N]数组存储所有原始边
 *
*DFS主函数，参数x为当前访问节点
记录DFS序，标记节点已访问
*遍历x的所有邻接点
跳过已标记的边(jd[i] == 1)
i^1是异或操作，用于获取反向边索引
*递归访问邻接点to
回溯时再次记录当前节点
*如果还有未处理的孤立组件且当前不是特殊边
从s1或s2中取出一个节点o
在DFS序列中插入0作为分隔符
记录新边信息并递归访问o
 *
*遍历DFS序列
非零元素加入答案数组
遇到0时输出当前段并打印对应边信息
 *特殊情况处理：如果f为真，在开始处添加额外信息
 *
 *
*读入所有边信息
统计各节点度数
使用并查集检测环，如果有环则标记t为当前边号
*如果节点1度数为0(孤立点)
设置标志f=1
如果存在环，则将环中某条边连接到节点1
否则寻找一条合适的边连接到节点1
 *
*重新初始化度数数组和并查集
构建无向图的邻接表表示
更新度数和并查集
标记特殊边
*遍历所有节点
找出与节点1不连通的连通分量
有度数的放入s1，无度数的放入s2
 *
*从节点1开始深度优先搜索
如果仍有未处理的孤立组件则输出"NO"
否则调用print函数输出结果
 *
 */
#include <cstdio>
#include <vector>
#include <cstring>
#include <set>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

typedef long long ll;
const int N = 4e5+100;
int n, m, fi[N], cnt, fa[N], du[N], t, f, O, ID, jd[N],
dfn[N<<2], tim, tot,
ans[N], num;
set<int> s1, s2;//两个整数集合，用于存储特殊节点
bool vis[N];

ll read() {
    ll x(0), f(0), c = getchar();
    for (; c > '9' || c < '0'; f = c == '-', c = getchar());
    for (; c >= '0' && c <= '9'; x = (x<<1)+(x<<3)+(c^'0'), c = getchar());
    return f ? -x : x;
}

struct Node { int to, nxt; } p[N<<1];
struct Edge { int x, y, id; } e[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void addline(int x, int y) { p[++cnt] = {y, fi[x]}; fi[x] = cnt; }//将节点y添加到x的邻接表中

void dfs(int x) {
    dfn[++tim] = x; vis[x] = 1;
    for (int i = fi[x]; ~i; i = p[i].nxt) {
        if (jd[i] == 1) continue;
        t = jd[i];
        jd[i] = jd[i^1] = 1;
        int to = p[i].to;
        dfs(to);
        dfn[++tim] = x;
        if ((!s1.empty() || !s2.empty()) && !t) {
            int o;
            if (!s1.empty()) o = (*s1.begin()), s1.erase(o);
            else o = (*s2.begin()), s2.erase(o);
            dfn[++tim] = 0; e[++tot] = {x, o, i / 2 + 1};
            dfs(o);
            dfn[++tim] = x;
        }
    }
}

void print() {
    int pl(1);//pl为边索引指针
    if (!O) f = 0;
    printf("YES\n%d\n", tot+f);
    rep(i,tim+1) {
        if (dfn[i]) ans[++num] = dfn[i];
        else {
            printf("%d ", num);
            rep(j,num) printf("%d ", ans[j]);
            putchar('\n');
            num = 0;
            if (pl <= tot) {
                printf("%d %d %d\n", e[pl].id, e[pl].x, e[pl].y);
                ++pl;
            }
        }
        if (i == 1 && f) {
            printf("1 1\n%d %d 1\n", ID, O);
            num = 0;
        }
    }
}

int main() {
    memset(fi, -1, sizeof(fi)); cnt = -1;
    n = read(); m = read();
    rep(i,n) fa[i] = i;
    rep(i,m) {
        e[i].x = read(), e[i].y = read();
        ++du[e[i].x]; ++du[e[i].y];
        if (find(e[i].x) == find(e[i].y)) t = i;
        else fa[find(e[i].x)] = find(e[i].y);
    }
    if (du[1] == 0) {
        f = 1;
        if (t) { e[t].y = 1; O = e[t].x; ID = t; }
        else {
            rep(i,m) {
                if (du[e[i].x] <= 1) swap(e[i].x, e[i].y);
                if (du[e[i].x] > 1) {
                    e[i].id = 1; O = e[i].x; ID = i;
                    e[i].y = 1;
                    break;
                }
            }
        }
    }
    memset(du, 0, sizeof(du));
    rep(i, n) fa[i] = i;
    rep(i, m) {
        int u = e[i].x, v = e[i].y;
        addline(u, v); addline(v, u);
        fa[find(u)] = find(v);
        ++du[u]; ++du[v];
        if (e[i].id) jd[cnt] = jd[cnt^1] = 2;
    }

    for (int i = 2; i <= n; ++i) {
        if (i == find(i) && find(1) != i) {
            if (du[i]) s1.insert(i);
            else s2.insert(i);
        }
    }
    dfs(1);
    if (!s1.empty() || !s2.empty()) printf("NO\n");
    else print();
    return 0;
}