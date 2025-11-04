//
// Created by Psy.C on 2025/11/4.
//
/*
 *N=1000000（节点最大数量），M=100000（缓冲区大小)
 *定义快速输入宏tc()：实现自定义的字符输入函数，用于优化读取速度
*n: 节点数
m: 边数
k: 每个连通分量最多能连接的边数
f[]: 并查集父节点数组
g[]: 每个连通分量的节点计数数组
 *
*并查集的查找函数，带路径压缩优化
如果f[x]不为0，则递归查找父节点并进行路径压缩，否则返回x本身
 *
*oc: 当前读取的字符
t[]: 输入缓冲区
a, b: 缓冲区指针，用于实现快速读取
*模板函数read：快速读取整数
第一个while循环：跳过非数字字符，找到第一个数字字符
第二个while循环：将连续的数字字符转换为整数，使用位运算优化(x<<3)+(x<<1)=x*10
 *可变参数模板函数：支持同时读取多个变量
 *使用register关键字提示编译器优化
 *
*读取n(节点数)、m(边数)、k(每个连通分量最大连接数)
遍历所有边，进行并查集合并操作：
读取边的两个端点x和y
找到x和y的根节点
如果根节点不同，则合并两个集合
 *
*初始化计数器：c(连通分量数)、u(度数为1的连通分量数)、v(总度数)
统计每个连通分量的节点数量
 *
*遍历所有节点，统计连通分量信息：
如果f[i]为0，说明i是某个连通分量的根节点
增加连通分量计数c
如果该连通分量只有一个节点(g[i]==1)，增加u计数
累加每个连通分量的度数v，度数不超过k
 *
*初始化操作次数s
当总度数不足以连接所有连通分量时，进行操作：
增加操作次数
减少连通分量数(合并两个连通分量)
调整度数相关的计数器
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cctype>
#define N 1000000
#define M 100000
#define tc() (a==b&&(b=(a=t)+fread(t,1,M,stdin),a==b)?EOF:*a++)
using namespace std;

int n, m, k, f[N+5], g[N+5];

int fa(const int& x) { return f[x] ? f[x] = fa(f[x]) : x; }

char oc, t[M], *a = t, *b = t;
template<typename T>
void read(T& x) {
    x = 0;
    while (!isdigit(oc=tc()));
    while (x = (x << 3) + (x << 1) + (oc&15), isdigit(oc=tc()));//只适用于数字字符 '0' 到 '9'
}

template<typename T, typename... Args>
void read(T& x, Args&... args) { read(x); read(args...); }

int main() {


    register int i, x, y;
    for (read(n, m, k), i = 1; i <= m; ++i) {
        read(x, y);
        (x = fa(x)) ^ (y = fa(y)) && (f[x] = y);
    }
    register int c(0), u(0), v(0);
    for (i = 1; i <= n; ++i) ++g[fa(i)];
    for (i = 1; i <= n; ++i) {
        !f[i] && (++c, g[i] == 1 && ++u, v += min(g[i], k));
    }
    register int s(0);
    while (v < 2 * (c - 1)) {
        ++s;
        --c;
        u -= 2;
        v -= 2;
        v += min(2, k);
    }
    return printf("%d\n", s), 0;
}