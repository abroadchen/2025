//
// Created by Psy.C on 2026/2/16.
//
/**
L[N][N]: 左边连续字符长度数组
R[N][N]: 右边连续字符长度数组
q1[N], q2[N]: 单调队列数组 维护L和R数组的最小值
h1,t1,h2,t2: 单调队列的头尾指针
l1,r1: 左右半部分的宽度

m,q: 列数和查询次数
a[N][N]: 地图数组（1表示'.'，0表示'*'）
s[N]: 临时字符串数组

h1, h2: 单调队列的头指针（指向队首）
t1, t2: 单调队列的尾指针（指向队尾）
l1 = mid-l+1: 从左边界到中心列的宽度
r1 = r-mid+1: 从中心列到右边界的宽度
mi = mid: 中间列索引
res: 存储结果的最大值
q1: 存储行索引，按 L[row][mi] 值单调递增排列
q2: 存储行索引，按 R[row][mi] 值单调递增排列
当新元素比队尾元素更小时，弹出队尾（保持单调性）
将当前行 r 加入队尾

L[q1[h1]][mi]: 当前行窗口中，中心列左边连续格子数的最小值
R[q2[h2]][mi]: 当前行窗口中，中心列右边连续格子数的最小值
min(..., l1): 确保不超过左边界限制
min(..., r1): 确保不超过右边界限制
-1: 因为中心格子重复计算了一次
now: 当前行窗口中能形成的最大十字臂长

r - l + 1: 当前行窗口的高度
min(now, r - l + 1): 十字形的实际臂长不能超过高度
mxx(res, ...): 更新全局最大值
当十字臂长 now 小于等于窗口高度 r - l + 1 时，需要收缩窗口：
移除最上面的行（l++）
如果被移除的行在单调队列中，更新队列头指针
重新计算 now 值
继续收缩直到 now > r - l + 1

 */
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;
inline void mxx(int& a, const int b) { a < b ? a = b : 0; }

constexpr int N = 2005;

int n, L[N][N], R[N][N], q1[N], q2[N];
///在指定列范围[l,r]内，以中间列mid为中心能形成的十字形的最大长度
inline int get(int l, int r) {
    int h1 = 1, h2 = 1, t1 = 0, t2 = 0, l1 = mid-l+1, r1 = r-mid+1, mi = mid, res = 0;
    for (l = 1, r = 1; r <= n; ++r) {
        while (h1 <= t1 && L[q1[t1]][mi] >= L[r][mi]) t1--; q1[++t1] = r;
        while (h2 <= t2 && R[q2[t2]][mi] >= R[r][mi]) t2--; q2[++t2] = r;
        int now = min(L[q1[h1]][mi], l1) + min(R[q2[h2]][mi], r1) - 1;
        mxx(res, min(now, r - l + 1));
        while (l <= r && now <= r - l + 1) {
            if (q1[h1] == l) h1++;
            if (q2[h2] == l) h2++;
            l++;
            now = min(L[q1[h1]][mi], l1) + min(R[q2[h2]][mi], r1) - 1;
        }
    }
    return res;
}



int tr[N<<2];
inline void push_up(const int u) {// 向上更新，将子节点的最大值更新到父节点
    mxx(tr[u], max(tr[u<<1], tr[u<<1|1]));
}

inline void build(const int u, const int l, const int r) {
    tr[u] = get(l, r);
    if (l == r) return;
    build(u<<1, l, mid); build(u<<1|1, mid + 1, r);
    push_up(u);
}

///更新位置p后，重新计算包含p的区间
inline void update(const int u, const int l, const int r, const int p) {
    tr[u] = get(l, r);
    if (l == r) return;
    if (p <= mid) update(u<<1, l, mid, p);
    else update(u<<1|1, mid + 1, r, p);
    push_up(u);
}

inline int read() {
    char ch = getchar(); int res = 0, f = 1;
    while (!isdigit(ch)) f ^= ch == '-', ch = getchar();
    while (isdigit(ch)) res = ((res+(res<<2))<<1)+(ch&15), ch = getchar();
    return f ? res : -res;
}

int m, q, a[N][N];
char s[N];
int main() {
    n = read(), m = read(), q = read();
    rep(i,n) {
        scanf("%s", s + 1);
        rep(j,m) a[i][j] = s[j] == '.';
    }
    rep(i,n) rep(j,m) L[i][j] = a[i][j] ? L[i][j-1]+1 : 0;//每个位置向左连续1的个数
    rep(i,n) for (int j = m; j; --j) R[i][j] = a[i][j] ? R[i][j+1]+1 : 0;//每个位置向右连续1的个数
    build(1, 1, m);//每个节点存储对应列区间内的最大十字形
    while (q--) {
        const int x = read(), y = read(); a[x][y] = 0;//障碍
        rep(j,m) L[x][j] = a[x][j] ? L[x][j-1]+1 : 0;
        for (int j = m; j; --j) R[x][j] = a[x][j] ? R[x][j+1]+1 : 0;
        update(1, 1, m, y);//更新线段树中对应列的节点
        cout << tr[1] << '\n';//当前全局最大十字形尺寸
    }
    return 0;
}