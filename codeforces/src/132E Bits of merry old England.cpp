//
// Created by Psy.C on 2025/11/19.
//
/*
n,m: 输入参数
t,s: 汇点和源点
图的链式前向星存储结构：
st[]: 边的起点
l: 边的计数器，初始化为1
ed[]: 边的终点
data[]: 边的容量
cost[]: 边的费用
nxt[]: 链式结构的下一个指针
son[]: 每个节点的邻接表头
a[]: 存储输入数据
v[]: 记录匹配关系
d[]: SPFA算法的距离数组
f[]: SPFA的队列数组
pre[]: 记录前驱边
ans: 总费用
cur[]: 当前字符映射
b[]: 布尔标记数组


h=0, x=1：队头和队尾指针
f[1] = s：源点入队
++h：队头指针前移，取出队首元素i
b[i] = 0：取消i的访问标记
p = son[i]：从i的第一个邻接边开始
p; p = nxt[p]：沿着链式结构遍历
if (data[p])：如果边还有容量
j = ed[p]：获取边的终点
松弛操作：如果通过i到j的距离更短，则更新
pre[j] = p：记录前驱边
如果j未在队列中，则加入队列
沿着前驱边更新流量：
从汇点开始回溯到源点
p = pre[p]：获取前驱边
data[p]--：正向边容量减1
data[p^1]++：反向边容量加1(异或1实现配对)


 *
*SPFA算法寻找最小费用增广路径：
初始化距离数组，源点距离为0
使用队列进行SPFA搜索
找到负费用路径则更新答案并调整流量
返回是否找到增广路径
 *
*对每个节点i：
读取数据a[i]
添加i到i+n容量1费用cnt(a[i])的边
添加i+n到i+2*n容量1费用-inf的边
添加i+2*n到汇点t容量1费用0的边
如果不是最后一个节点，添加相关连接边
 *
*对每个节点i，寻找下一个相同值的位置j
如果找到，则添加相应边并记录匹配关系
 *
 *
*输出变量赋值和打印语句：
初始化字符标记数组
对每个节点：
如果没有预分配字符，则分配新字符
输出赋值语句
输出打印语句
根据流量情况决定是否传递字符或释放字符
 */
#include <cstdio>
#include <cstring>
#define rep(i,n) for (int i = 1; i <= (n); ++i)
#define add(x,y,z,c) addedge(x,y,z,c),addedge(y,x,0,-c)
using namespace std;

const int N = 1e5+5, inf = 1e5;
int n, m, t, s,
st[N], l(1), ed[N], data[N], cost[N], nxt[N], son[N],
a[N], v[N], d[N], f[N*5], pre[N], ans, cur[N];
bool b[N];

void addedge(int x, int y, int z, int c) {
    st[++l] = x; ed[l] = y; data[l] = z; cost[l] = c;
    nxt[l] = son[x]; son[x] = l;//：新边指向原来的第一个邻接边，更新头指针
}

int cnt(int x) {//x的二进制表示中1的个数（汉明重量）
    int ret(0);
    while (x) { ret += x & 1; x >>= 1; }
    return ret;
}

bool spfa() {
    memset(d, 6, sizeof d); d[s] = 0;
    int h(0), x(1); f[1] = s; memset(b, 0, sizeof b);
    while (h < x) {
        int i = f[++h]; b[i] = 0;
        for (int p = son[i]; p; p = nxt[p]) if (data[p]) {
            int j = ed[p];
            if (d[i] + cost[p] >= d[j]) continue;
            d[j] = d[i] + cost[p]; pre[j] = p;
            if (!b[j]) b[j] = 1, f[++x] = j;
        }
    }
    if (d[t] > 0) return 0;//如果汇点距离仍为正，说明找不到负费用增广路径
    ans += d[t];//累加总费用
    for (int p = t; p; p = st[p]) p = pre[p], data[p]--, data[p^1]++;
    return 1;
}

int main() {
    scanf("%d%d", &n, &m); t = n * 3 + 1; add(s, 1, m, 0);
    rep(i,n) {
        scanf("%d", &a[i]); add(i,i+n,1,cnt(a[i]));
        add(i+n,i+2*n,1,-inf); add(i+2*n,t,1,0);
        if (i < n) add(i+2*n,i+1,1,0), add(i,i+1,inf,0);
    }
    rep(i,n) {
        int j;
        for (j = i + 1; j <= n && a[i] - a[j]; j++);
        if (j <= n) add(i+2*n,j+n,1,0), v[i] = j;
        else l += 2;
    }
    while (spfa());
    m = n;
    rep(i,n) if (data[n*10+i*2-1]) m--;
    printf("%d %d\n", m + n, (ans%inf+inf)%inf);
    memset(b, 0, sizeof b);
    rep(i,n) {
        int w = cur[i];
        if (!w) {
            for (w = 97; b[w]; w++);
            b[w] = 1;
            printf("%c=%d\n", w, a[i]);
        }
        printf("print(%c)\n", w);
        if (data[n*10+i*2-1]) cur[v[i]] = w;
        else b[w] = 0;
    }
    return 0;
}