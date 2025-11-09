//
// Created by Psy.C on 2025/11/9.
//
/*
 *t用于临时字符串存储，s用于以一维数组形式存储整个网格
 *
*c：存储该单元格的字符（'L', 'R', 'U', 'D', 或 '.'）
l, r, d, u：分别表示左、右、下、上相邻单元格的索引
构造函数将所有邻居索引初始化为-1（表示无邻居）
声明了两个这样的节点数组：p（工作副本）和q（原始副本）
 *
*从双向链接结构中移除索引为x的单元格：
~是按位取反运算符；~(-1)等于0，所以~val用来检查val != -1
对于每个存在的邻居，更新该邻居的指针以跳过被移除的单元格
这有效地将索引为x的单元格从其邻居中断开连接
 *
*循环构建网格并建立相邻单元格之间的连接：
读取每一行到临时数组t中
将行数据复制到一维数组s中
对于位置(i,j)的每个单元格：
设置字符值
如果不在第一行，则与上方单元格连接
如果不在第一列，则与左侧单元格连接
 *
 *计算单元格总数，并移除所有'.'单元格，因为它们不参与路径遍历
 *初始化变量来跟踪最大路径长度(mx)和具有该长度的路径数量(num)。然后将当前状态保存到数组q中
 *
*对于每个非'.'单元格，模拟一条路径：
从备份q恢复原始结构
从当前单元格开始遍历
根据方向(L/R/U/D)移动，同时计数步数
使用cov()移除已访问的单元格，确保每次模拟中每个单元格只能访问一次
 *
*如果当前路径比之前的最长路径更长，则更新最大值并重置计数
如果当前路径长度等于最大长度，则增加计数
 *
 */
#include <cstdio>
#include <cstring>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

const int N = 5e3+3;
char t[N], s[N];

struct node {
    char c;
    int l, r, d, u;
    node() { l = r = d = u = -1; }
} p[N], q[N];

void cov(int x) {
    if (~p[x].l) p[p[x].l].r = p[x].r;
    if (~p[x].r) p[p[x].r].l = p[x].l;
    if (~p[x].u) p[p[x].u].d = p[x].d;
    if (~p[x].d) p[p[x].d].u = p[x].u;
}


int main() {
    int n, m; scanf("%d%d", &n, &m);
    rep(i,n) {
        scanf("%s", t);
        memcpy(s+i*m, t, sizeof(char)*m);
        rep(j,m) {
            int id = i*m+j; p[id].c = t[j];
            if (i) { p[id].u = id - m; p[id-m].d = id; }
            if (j) { p[id].l = id - 1; p[id-1].r = id; }
        }
    }
    int len = n*m;
    rep(i,len) if (s[i] == '.') cov(i);
    int mx(0), num(0);
    memcpy(q, p, sizeof(node)*len);
    rep(i,len) if (s[i] != '.') {
        memcpy(p, q, sizeof(node)*len);
        int nw = i, st = 0;
        while (~nw) {
            st++;
            cov(nw);
            if (p[nw].c == 'L') nw = p[nw].l;
            else if (p[nw].c == 'R') nw = p[nw].r;
            else if (p[nw].c == 'U') nw = p[nw].u;
            else nw = p[nw].d;
        }
        if (mx < st) { mx = st; num = 1; }
        else if (mx == st) num++;
    }
    printf("%d %d\n", mx, num);
    return 0;
}