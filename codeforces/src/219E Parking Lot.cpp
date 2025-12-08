//
// Created by Psy.C on 2025/12/8.
//
/*
*n：范围大小
m：操作次数
*mx：最大值对（first为值，second为位置）
cnt：计数器
L：左边界
R：右边界
 *
*重载加法运算符，用于合并两个线段树节点：
cnt：两个节点计数器相加
mx：取两个节点mx的最大值
L：取两个节点左边界最小值
R：取两个节点右边界最大值
如果两个节点都有元素且中间有空隙，则计算中间位置的最大值
 *
*递归构建左右子树
叶子节点初始化为空状态
非叶子节点通过合并子节点构建
*p：位置
op：操作类型（1为插入，-1为删除）
在对应位置更新节点状态并向上合并
 *
*tot：临时计数器
pos[M]：位置数组
g[3]：临时数组
 *
*读取操作类型op和参数x
如果是插入操作(op=1)：
收集可能的最优位置
排序后选择最佳位置
记录位置并更新线段树
输出选择的位置
如果是删除操作：
从线段树中删除对应位置
 *
 *
*a[1].mx.second：线段树根节点存储的最大值对应的位置
如果位置不为0（有效），则将这个最大值对存入数组g
tot++：计数器加1
*a[1].L != 1：当前最左元素不是位置1
a[1].cnt：当前有元素存在
如果条件满足，将候选位置{a[1].L - 1, -1}加入数组g
这表示在最左边元素的前面插入
*a[1].R != n：当前最右元素不是位置n
a[1].cnt：当前有元素存在
如果条件满足，将候选位置{n - a[1].R, -n}加入数组g
这表示在最右边元素的后面插入
*如果没有找到任何候选位置（tot仍为0）：
添加默认候选位置{inf, -1}
这种情况可能发生在初始状态（没有任何元素时）
*sort(g, g + tot)：按升序排列
reverse(g, g + tot)：反转为降序排列
这样g[0]就是最优（最大）的候选位置
*g[0].second：最优候选位置的标识
取负值作为实际位置并存储在pos[x]中
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define N 200007
#define inf 0x3f3f3f3f
using namespace std;

constexpr int M = 1e6+1;
int n, m;
struct node { ii mx; int cnt{}, L{}, R{}; } a[N<<2];
node operator+(const node& a1, const node& b) {
    node c;
    c.cnt = a1.cnt + b.cnt;
    c.mx = max(a1.mx, b.mx);
    c.L = min(a1.L, b.L); c.R = max(a1.R, b.R);
    if (a1.cnt && b.cnt && a1.R + 1 < b.L) {
        const int p = (b.L + a1.R) >> 1;
        c.mx = max(c.mx, {min(b.L - p, p - a1.R), -p});
    }
    return c;
}

void build(const int l, const int r, const int rt) {
    if (l == r) {
        a[rt].cnt = 0; a[rt].L = inf; a[rt].R = -inf;
        a[rt].mx = {0, 0}; return;
    }
    const int mid = (l + r) >> 1;
    build(l, mid, rt<<1);
    build(mid + 1, r, rt<<1|1);
    a[rt] = a[rt<<1] + a[rt<<1|1];
}

void update(const int p, const int op, const int l, const int r, const int rt) {
    if (l == r) {
        if (op == 1) {
            a[rt].cnt = 1;
            a[rt].L = a[rt].R = p;
            a[rt].mx = {0, 0};
        } else {
            a[rt].cnt = 0;
            a[rt].L = inf; a[rt].R = -inf;
            a[rt].mx = {0, 0};
        }
        return;
    }
    const int mid = (l + r) >> 1;
    if (p <= mid) update(p, op, l, mid, rt<<1);
    else update(p, op, mid+1, r, rt<<1|1);
    a[rt] = a[rt<<1] + a[rt<<1|1];
}

int tot, pos[M];
ii g[3];
int main() {
    fast;
    cin >> n >> m; build(1, n, 1);
    while (m--) {
        int op, x; cin >> op >> x;
        if (op == 1) {
            tot = 0;//候选位置的数量
            if (a[1].mx.second) g[tot++] = a[1].mx;
            if (a[1].L != 1 && a[1].cnt) g[tot++] = {a[1].L - 1, -1};
            if (a[1].R != n && a[1].cnt) g[tot++] = {n - a[1].R, -n};
            if (!tot) g[tot++] = {inf, -1};
            sort(g, g + tot); reverse(g, g + tot);
            pos[x] = -g[0].second;
            update(-g[0].second, 1, 1, n, 1);
            cout << -g[0].second << '\n';
        } else update(pos[x], -1, 1, n, 1);
    }
    return 0;
}