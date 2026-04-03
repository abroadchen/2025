//
// Created by Psy.C on 2026/4/2.
//
/**
x, y: 坐标
val: 值
n, m: 矩阵行列数
l[N], r[N]: 每列/每行的第一个元素（按值分组）
ans[N]: 最终答案
ml[N], mr[N]: 每列/每行的最大答案值

读入矩阵大小
读入矩阵值，同时记录坐标
将二维坐标转换为一维索引：(i-1)*m+j
按值从小到大排序

按相同值分组处理
k: 下一个不同值的起始位置
对于每行：如果该行还没有元素，记录第一个；否则合并
对于每列：如果该列还没有元素，记录第一个；否则合并
这样将同行同列的相同值连接起来
对于每个连通块，更新其答案
max(mr[b[j].x], ml[b[j].y]) + 1: 取该位置行列的最大值加1
将连通块的统一答案赋给每个元素
更新行列的最大答案值
重置r和l数组
移动到下一组
时间复杂度：O(nm log(nm))，主要是排序的复杂度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

struct node {
    int x, y, val;
    bool operator<(const node &o) const {
        return val < o.val;
    }
} b[N];

int fa[N];
int find(int x) {
    if (x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}
void join(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) fa[fx] = fy;
}

int n, m, l[N], r[N], ans[N], ml[N], mr[N];
int main() {
    fast;
    cin >> n >> m;
    int cnt = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> b[(i-1)*m+j].val;
            b[cnt].x = i, b[cnt++].y = j;
        }
    sort(b + 1, b+n*m+1);
    for (int i = 1; i <= n*m; ++i) fa[i] = i;
    int i = 1, k;
    while (i <= n*m) {
        for (k = i; k <= n*m; ++k)
            if (b[k].val != b[i].val) break;
        for (int j = i; j < k; ++j) {
            if (!r[b[j].x]) r[b[j].x] = (b[j].x - 1)*m + b[j].y;
            else join(r[b[j].x], (b[j].x - 1)*m + b[j].y);
            if (!l[b[j].y]) l[b[j].y] = (b[j].x - 1)*m + b[j].y;
            else join(l[b[j].y], (b[j].x - 1)*m + b[j].y);
        }
        for (int j = i; j < k; ++j) {
            int s = find((b[j].x - 1)*m + b[j].y);
            ans[s] = max(ans[s], max(mr[b[j].x], ml[b[j].y]) + 1);
        }
        for (int j = i; j < k; ++j) {
            int s = find((b[j].x - 1)*m + b[j].y);
            ans[(b[j].x - 1)*m + b[j].y] = ans[s];
            mr[b[j].x] = ans[s];
            ml[b[j].y] = ans[s];
            r[b[j].x] = 0; l[b[j].y] = 0;
        }
        i = k;
    }
    for (i = 1; i <= n*m; ++i) {
        if (i%m == 0) cout << ans[i] << '\n';
        else cout << ans[i] << ' ';
    }
    return 0;
}