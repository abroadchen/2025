//
// Created by Psy.C on 2025/11/15.
//
/*
*N = 20：最大节点数
n：实际节点数
e[N][N]：邻接矩阵，表示节点间的禁止关系
cnt(0)：当前找到的最大团的大小
ans[N]：存储最大团的节点
a[N]：临时存储当前正在构建的团
c[N][N]：存储节点名称字符串
 *
*定义read()函数用于将输入的字符串转换为对应的节点索引
读入一个字符串t
遍历所有节点名称，找到匹配的字符串并返回其索引
 *
*定义深度优先搜索函数，参数：
id：当前考虑的节点索引
x：当前团的大小
如果已经考虑完所有节点(id == n)：
如果当前团比之前找到的最大团更大，更新最大团
将当前团a复制到结果ans中
更新最大团大小cnt
 *
*检查当前节点id是否与团中所有节点都相连：
遍历当前团中的每个节点a[i]
如果存在不相连的情况(e[a[i]][id] == 0)，直接返回（剪枝）
 *
*读入m对禁止连接的节点
使用read()函数将节点名称转换为索引
在邻接矩阵中标记这些节点对不能同时出现在团中
 */
#include <cstring>
#include <algorithm>
#include <iostream>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

const int N = 20;
int n, e[N][N], cnt(0), ans[N], a[N];
char c[N][N];

int read() {
    char t[20]; scanf("%s", t);
    rep(i,n) if (strcmp(c[i], t) == 0) return i;
}

void dfs(int id, int x) {
    if (id == n) {
        if (cnt < x) {
            rep(i,x) ans[i] = a[i];
            cnt = x;
        }
        return;
    }
    dfs(id + 1, x);//不选择当前节点id，继续搜索下一个节点
    rep(i,x) if (e[a[i]][id] == 0) return;
    a[x] = id;//选择当前节点id加入团中
    dfs(id + 1, x + 1);//递归搜索下一个节点，团大小增加1
}
//按字典序对节点名称排序
bool cmp(int a, int b) { return strcmp(c[a], c[b]) < 0; }

int main() {
    int m; scanf("%d%d",&n, &m);
    rep(i,n) rep(j,n) e[i][j] = 1;//假设所有节点间都可以连接(1)
    rep(i,n) scanf("%s",c[i]);//读入n个节点的名称字符串
    rep(i,m) {
        int x = read(), y = read();
        e[x][y] = e[y][x] = 0;
    }
    dfs(0, 0);
    sort(ans, ans + cnt, cmp);
    printf("%d\n", cnt);
    rep(i,cnt) printf("%s\n",c[ans[i]]);
    return 0;
}