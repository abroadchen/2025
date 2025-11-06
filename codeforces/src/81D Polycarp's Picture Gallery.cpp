//
// Created by Psy.C on 2025/11/6.
//
/*
*n：总位置数
m：任务类型数
n_ord：排序后的位置数量
ord[N]：重新排序后的位置序列
ans[N]：每个位置分配的任务类型结果
a[M]：存储每种任务类型的信息（数量和类型编号）
 *
*当任务总数超过位置数时，需要减少任务数量
每次对任务数组排序，减少数量最多的那种任务的一个单位
重复直到任务总数等于位置数
 *
 *检查每种任务类型是否超过位置数的一半
*重新排列位置顺序：先放偶数位置（0,2,4...），再放奇数位置（1,3,5...）
这样可以确保相同任务类型不会相邻
 *
*从数量最多的任务开始，按重新排列的位置顺序进行分配
这样可以避免某种任务集中在一段位置上
 *
 */
#include <algorithm>
#include <cstdio>
#include <utility>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

typedef pair<int,int> pii;
const int N = 1005, M = 45;
int n, m, n_ord, ord[N], ans[N];
pii a[M];

int main() {
    scanf("%d %d", &n, &m);
    rep(i,m) { scanf("%d",&a[i].first); a[i].second = i; }
    int sum(0);
    rep(i,m) sum += a[i].first;
    if (sum < n) { printf("-1\n"); return 0; }
    while (sum > n) {
        sort(a, a+m);
        a[m - 1].first--;
        sum--;
    }
    rep(i,m) if (a[i].first * 2 > n) { printf("-1\n"); return 0; }
    n_ord = 0;
    rep(i,n) if (i % 2 == 0) ord[n_ord++] = i;
    rep(i,n) if (i % 2 == 1) ord[n_ord++] = i;
    sort(a, a + m);
    for (int i = m - 1, k = 0; i >= 0; --i) {
        while (a[i].first > 0) {
            ans[ord[k++]] = a[i].second;
            a[i].first--;
        }
    }
    rep(i,n) {
        if (i > 0) printf(" ");
        printf("%d", ans[i] + 1);
    }
    printf("\n");
    return 0;
}