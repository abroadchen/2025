//
// Created by Psy.C on 2026/3/9.
//
/**
计算每行的最长连续1序列：

mx = -1：初始化最大值
遍历每一行k
ans = 0：当前连续1的计数
遍历每一列j：
如果a[k][j] == 0：连续中断，ans = 0
否则：ans++（连续1的长度增加）
更新最大连续长度mx
时间复杂度：O(q×n×m)，对于每次查询都需要O(n×m)时间重新计算
线段树维护最长连续序列

l：从左端点开始的最长连续1序列长度
r：从右端点开始的最长连续1序列长度
mx：区间内的最长连续1序列长度
tr[N][N<<2]：二维线段树数组，每行一个线段树

fa.l：如果左子树全为1，可以延伸到右子树
fa.r：如果右子树全为1，可以延伸到左子树
fa.mx：左右子树的最大值或跨越中点的连续序列

更新第i行的第pos列的值
递归更新到叶子节点，然后向上更新
维护所有行中最长连续序列的线段树
mx[id]：所有行中最长连续序列的最大值


读入初始矩阵
对于每个值为1的位置，更新对应的线段树
初始化行间线段树

更新第i行的线段树
更新行间线段树
输出全局最长连续1序列长度
时间复杂度：O(q×log²m)

mid - L + 1 = (L + R) / 2 - L + 1 = (R - L + 2) / 2
R - mid = R - (L + R) / 2 = (2R - L - R) / 2 = (R - L) / 2

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 505;

struct node { int l, r, mx; } tr[N][N<<2];

void init(int i, int id) {
    node& now = tr[i][id];
    if (now.mx) now.l = now.r = now.mx = 0;
    else now.l = now.r = now.mx = 1;
}

void push_up(int i, int id, int L, int R) {
    node& fa = tr[i][id], &l = tr[i][id<<1], &r = tr[i][id<<1|1];
    fa.l = l.l == (R-L+2)>>1 ? l.l + r.l : l.l;
    fa.r = r.r == (R-L+1)>>1 ? r.r + l.r : r.r;
    fa.mx = max(max(l.mx, r.mx), l.r + r.l);
}

void update(int i, int id, int L, int R, int pos) {
    if (L == R) { init(i, id); return; }
    int mid = (L + R) >> 1;
    if (pos <= mid) update(i, id<<1, L, mid, pos);
    else update(i, id<<1|1, mid+1, R, pos);
    push_up(i, id, L, R);
}

int mx[N<<2];
void dfs(int id, int L, int R, int pos, int val) {
    if (L == R) { mx[id] = val; return; }
    int mid = (L + R) >> 1;
    if (pos <= mid) dfs(id<<1, L, mid, pos, val);
    else dfs(id<<1|1, mid+1, R, pos, val);
    mx[id] = max(mx[id<<1], mx[id<<1|1]);
}

int n, m, q;
int main() {
    fast;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, a; j <= m; ++j)
            if (cin >> a, a) update(i, 1, 1, m, j);
        dfs(1, 1, n, i, tr[i][1].mx);
    }
    int i, j;
    while (q--) {
        cin >> i >> j;
        update(i, 1, 1, m, j);
        dfs(1, 1, n, i, tr[i][1].mx);
        cout << mx[1] << '\n';
    }
    return 0;
}