//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
s[i][j]：原矩阵。
r[i]：第 i 行排序后的元素（用于行内排名）。
c[j]：第 j 列排序后的元素（用于列内排名）。
x[i]：第 i 行去重后的不同值个数。
y[j]：第 j 列去重后的不同值个数。
读入矩阵，同时把每一行复制进 r，把每一列转置复制进 c（c[j][i] 即第 j 列的第 i 个元素），方便后续按列排序
对每行排序并 unique，x[i] = 该行互不相同的元素个数（排名上限）
对每列排序去重，y[i] = 该列互不相同的元素个数
对每个格子 s[i][j]：

a：该值在行去重有序序列中的下标（即"比它小的有多少个不同值"）。
b：该值在列去重有序序列中的下标（即"比它小的有多少个不同值"）。
即：答案 = 向下所需排名 + 向上所需余量，其中向下取行列最大值，向上也取行列最大值。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1005;
int n, m, s[N][N], r[N][N], c[N][N], x[N], y[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) { cin >> s[i][j]; r[i][j] = s[i][j]; c[j][i] = s[i][j]; }
    rep(i,n) {
        sort(r[i]+1,r[i]+m+1);
        x[i] = unique(r[i]+1,r[i]+m+1)-r[i]-1;
    }
    rep(i,m) {
        sort(c[i]+1,c[i]+n+1);//列内排序 (转置后的行)
        y[i] = unique(c[i]+1,c[i]+n+1)-c[i]-1;
    }
    int a, b;
    rep(i,n) {
        rep(j,m) {
            a = lower_bound(r[i],r[i]+x[i],s[i][j])-r[i];
            b = lower_bound(c[j],c[j]+y[j],s[i][j])-c[j];
            cout << max(a,b)+max(x[i]-a,y[j]-b) << ' ';
        }
        cout << '\n';
    }
    return 0;
}