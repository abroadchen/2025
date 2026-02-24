//
// Created by Psy.C on 2026/2/24.
//
/**
n：区间数量
l[i], r[i]：第i个区间的左右端点
m：查询数量
top：栈顶指针
st[N]：单调栈，存储区间编号
sum[N]：前缀和数组
ans[N]：答案数组

x：右端点坐标
id：查询编号
q[i]存储所有左端点为i的查询

x：区间起始位置
y：区间长度
l[i] = x：左端点
r[i] = x + y：右端点
L：查询区间左端点
R：查询区间右端点
将查询按左端点分组存储到q[L]中

从后往前处理每个区间（逆序处理）
当前处理的区间编号
维护单调栈，合并可以合并的区间：
当栈顶区间的左端点小于等于当前区间的右端点时，说明可以合并
更新当前区间的右端点为两者的最大值
在并查集中合并区间：将栈顶区间的根节点指向当前区间，并弹出栈顶
如果栈不为空，当前区间的前缀和 = 栈顶区间的前缀和 + 栈顶区间的左端点 - 当前区间的右端点
将当前区间压入栈中
 */
#include <bits/stdc++.h>
#define mxx(a,b) ((a) > (b) ? (a) : (b))
#define ll long long
using namespace std;
template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

#define int ll
constexpr int N = 2e5+1;
int fa[N];
inline int find(const int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}



int n, l[N], r[N], m, top, st[N], sum[N], ans[N];
struct node { int x, id; };
vector<node> q[N];


signed main() {
    read(n);
    for (int i = 1, x, y; i <= n; ++i)
        read(x), read(y), l[i] = x, r[i] = x + y;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    read(m);
    for (int i = 1, L, R; i <= m; ++i)
        read(L), read(R), q[L].push_back({R, i});
    for (int i = n; i >= 1; --i) {
        const int x = i;
        while (top && l[st[top]] <= r[x]) {
            r[x] = mxx(r[x], r[st[top]]);
            fa[find(st[top])] = x, top--;
        }
        if (top) sum[x] = sum[st[top]] + l[st[top]] - r[x];
        st[++top] = x;
        for (auto &[xx, idx] : q[i]) {
            const int id = idx, y = xx;
            ans[id] = sum[find(x)] - sum[find(y)];
        }
    }
    for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
    return 0;
}