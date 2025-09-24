//
// Created by Psy.C on 2025/9/24.
//
/*
*buf是读取缓冲区，p1和p2是缓冲区指针
ot是输出缓冲区位置，t是临时变量，c是字符缓存
 *
*定义gc宏用于快速读取字符
当缓冲区用完时从stdin读取新数据到缓冲区
 *
 *read()函数用于快速读取整数
*ob是输出缓冲区，stk是栈用于数字转字符串
fls()函数将缓冲区内容写入stdout
*write()函数快速输出长整数和一个字符
处理负数，将数字转换为字符并写入缓冲区
 *
*n: 元素个数
i: 循环变量
a[N]: 存储输入的数值
nw: 当前插入位置
rt: 树根节点
t[N][2]: 每个节点的左右子节点
mx[N]: 每个子树中的最大值
sz[N]: 每个子树的大小
d[N]: 节点深度
 *
 *定义宏ls和rs分别表示节点x的左子树和右子树
*qry()函数查询当前元素应该插入的位置排名
如果当前节点为空，返回0
如果当前元素小于等于节点值，在右子树查找
如果当前元素大于右子树最大值，说明应该插入到左子树并加上右子树大小和当前节点
否则在右子树继续查找
 *
*pp()函数更新节点信息
更新子树大小、深度和子树最大值
 *
*rot()函数执行树旋转操作
k表示旋转方向，0为左旋，1为右旋
 *
*Ins()函数插入新节点
如果当前节点为空，插入新节点
根据插入位置决定在左子树还是右子树插入
维护平衡树性质，必要时进行旋转
 *
 *putans()函数中序遍历输出结果
 *
 *
 */
#include <ios>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;

namespace fast_io {
    char buf[N + 5], *p1, *p2;
    int ot, t, c;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2)?EOF:*p1++)
    inline int read() {
        int an(0),f(1);while (!isdigit(c=gc)) if (c=='-') f=-f;
        do an=10*an+c-'0';while (isdigit(c=gc)); return an * f;
    }
    char ob[N+20],stk[20];
    inline void fls() { fwrite(ob,1,ot,stdout), ot = 0; }
    inline void write(ll x, char c=' ') {
        if (x < 0) ob[ot++] = '-', x = -x;
        while (x > 9) stk[++t]=48^(x % 10), x /= 10;
        for (ob[ot++]=48^x;t;ob[ot++]=stk[t--]);
        ob[ot++]=c; if (ot > N) fls();
    }
}
using fast_io::read;
using fast_io::write;

int n, i, a[N], nw, rt, t[N][2], mx[N], sz[N], d[N];
#define ls t[x][0]
#define rs t[x][1]

int qry(int x=rt) {
    if (!x) return 0;
    if (a[i] <= a[x]) return qry(rs);
    if (a[i] > mx[rs]) return sz[rs] + 1 + qry(ls);
    else return qry(rs);
}

inline void pp(int x) {
    sz[x] = sz[ls] + sz[rs] + 1;
    d[x] = max(d[ls], d[rs]) + 1;
    mx[x] = max({mx[ls], mx[rs], a[x]});
}

inline void rot(int& x, int k) {
    int y = t[x][k];
    t[x][k] = t[y][!k];
    pp(t[y][!k]=x), pp(x=y);
}

void Ins(int& x=rt) {
    if (!x) { pp(x=i); return; }
    int k;
    if (nw > sz[rs]) nw -= sz[rs] + 1, k = 0;
    else k = 1;
    int& y = t[x][k];
    Ins(y);
    if (d[y] > d[t[x][!k]] + 1) {
        if (d[t[y][!k]] > d[t[y][k]])
            rot(y, !k);
        rot(x, k);
    } else pp(x);
}

void putans(int x=rt) {
    if (x) {
        putans(ls);
        write(x);
        putans(rs);
    }
}

int main() {
    n = read();
    for (i = 1; i <= n; ++i) {
        a[i] = read();
        nw = min(read(), qry());
        Ins(rt);
    }
    putans();
    fast_io::fls();
    return 0;
}