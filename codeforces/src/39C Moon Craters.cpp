//
// Created by Psy.C on 2025/9/24.
//
/*
*n：区间数量
R[N]：所有右端点的排序数组
rid[N]：将每个区间映射到其右端点在排序数组中的索引
nxt[N]：对于每个区间，存储下一个不重叠区间的索引
dp[N][N]：动态规划表
Node：表示一个区间，包含左边界l、右边界r和原始索引id
排序规则：按左边界升序排列，如果左边界相等则按右边界降序排列
 *
*递归输出选中的区间
如果当前状态等于下一状态，跳过当前区间
否则选择当前区间，并递归处理剩余部分
 *
 *每个区间以中心点o和半径x的形式给出，转换为[o-x, o+x]
 *
*dp[i][j]表示从区间i到结束可以选取的最大区间数，其中j表示右边界约束
状态转移：要么跳过当前区间，要么选择它(加1)并求解子问题
 *
 *
 */
#include <algorithm>
#include <cstdio>
#define rep(i,a,b) for(signed i=(a);i<(b);++i)
using namespace std;
const int N = 2001;


inline int read() {
    char c(getchar()); int x(0), f(1);
    for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = -f;
    for (; '0' <= c && c <= '9'; c = getchar()) x = (x << 3) + (x << 1) + (c - '0');
    return x * f;
}



template<class T>void getMax(T& x, T y) { if (x < y) x = y; }

int n, R[N], rid[N], nxt[N], dp[N][N];

struct Node {
    int l, r, id;
    bool operator<(const Node& o) const {
        if (l != o.l) return l < o.l;
        return r > o.r;
    }
} a[N];

void output(int i, int j) {
    if (i == n) return;
    if (dp[i][j] == dp[i + 1][j]) return output(i + 1, j);
    printf("%d ", a[i].id + 1);
    output(i + 1, rid[i]);
    output(nxt[i], j);
}


int main() {
    n = read();
    rep (i, 0, n) {
        int o = read(), x = read();
        a[i].l = o - x, a[i].r = o + x;
        a[i].id = i, R[i] = a[i].r;
    }
    sort(a, a + n);
    sort(R, R + n);
    rep (i, 0, n) rep (j, 0, n) if (a[i].r == R[j]) rid[i] = j;//构建从区间到其右端点索引的映射
    rep (i, 0, n) {
        nxt[i] = n;
        rep (j, 0, n) if (a[i].r <= a[j].l) {
            nxt[i] = j;//对于每个区间，找到第一个在其结束后开始的区间
            break;
        }
    }
    for (int i = n - 1; ~i; --i) {
        rep (j, 0, n) {
            dp[i][j] = dp[i + 1][j];
            if (a[i].r <= R[j])
                getMax(dp[i][j],
                    dp[i + 1][rid[i]] + dp[nxt[i]][j] + 1);
        }
    }
    printf("%d\n", dp[0][n - 1]);
    output(0, n - 1);
    return 0;
}