//
// Created by Psy.C on 2026/3/22.
//
/**
w: 权重
id: 原始索引
f: 起始位置
t: 终止位置
c: 类型标识符（字符）
初始化变量：id=1（当前编号）、l=2（左端点）、r=3（右端点）
遍历排序后的节点：
如果a[i].c为真（非零）：设置起点为1，终点为递增的id
否则：检查是否有足够空间，若不够输出"-1"并退出
设置当前节点的起终点：f=l++, t=r
当l==r时更新指针：r++, l=2
 */
#include <bits/stdc++.h>
using namespace std;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

constexpr int N = 1e5+5;

struct node { int w, id, f, t; char c; } a[N];
int n, m;
int main() {
    rd(n), rd(m);
    for (int i = 1; i <= m; ++i)
        rd(a[i].w), rd(a[i].c), a[i].id = i;
    sort(a + 1, a + m + 1, [](const node &x, const node &y) {
        return x.w < y.w || (x.w == y.w && x.c > y.c);
    });
    for (int i = 1, id = 1, l = 2, r = 3; i <= m; ++i) {
        if (a[i].c) {
            a[i].f = 1; a[i].t = ++id;
            continue;
        }
        if (r > id) return puts("-1"), 0;
        a[i].f = l++, a[i].t = r;
        if (l == r) r++, l = 2;
    }
    sort(a + 1, a + m + 1, [](const node &x, const node &y) {
        return x.id < y.id;//恢复输入顺序
    });
    for (int i = 1; i <= m; ++i)
        printf("%d %d\n", a[i].f, a[i].t);
    return 0;
}