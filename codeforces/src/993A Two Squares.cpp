//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
node{ x, y } 存点坐标。
cmp：按 x 升序，x 相同再按 y 升序。
输入的点排序后，方便推导矩形边界和菱形对称中心
排序后：a[0] 是 x 最小的，a[2] 是 x 第二或第四（具体看 y）。对轴对齐矩形：
x 范围：a[0].x 到 a[2].x（最小值到最大值）。
y 范围：a[0].y 到 a[1].y（最小值到最大值）。
双重循环把矩形覆盖的所有整数格子标记为 1。
+100 是偏移，因为坐标可能是负数，把索引平移到非负区间（N=205 足够装下正负 100 的范围）。
换句话说：矩形是闭合的，包括边界，范围 [a[0].x, a[2].x] × [a[0].y, a[1].y]
b[0] 是菱形的最左顶点，b[1]x 是菱形上边界（排序后 b[] 的特殊排布）。
cnt 从 0 开始，每行 +1，表示当前行的半宽。
对每一行 i（从菱形最左顶点行走到 b[1].x），横坐标范围是 [b[0].y − cnt, b[0].y + cnt]。
只要某格在矩形中（vis==1）→ flg=1。
这就是菱形的上半描边（宽度线性增长）
从 b[1].x 走到 b[3].x（菱形最右端），cnt 每行 −1（半宽线性减小）。
同样逐格检查是否落入矩形。
两个循环合起来，完整描出了菱形（旋转 45° 正方形）内部的所有整数格子
只要菱形的任一格子与矩形重叠（flg==1）→ 输出 YES；否则 NO
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(i=0;i<n;i++)
#define rpe(i,j,k) for(i=j;i<=k;i++)
using namespace std;

constexpr int N = 205;
struct node { int x, y; } a[5], b[5];
bool cmp(node p, node q) {
    if (p.x == q.x) return p.y < q.y;
    return p.x < q.x;
}

int vis[N][N], i, j;
int main() {
    fast;
    rep(i,4) cin >> a[i].x >> a[i].y;
    rep(i,4) cin >> b[i].x >> b[i].y;
    sort(a, a+4, cmp);
    sort(b, b+4, cmp);
    rpe(i,a[0].x,a[2].x) rpe(j,a[0].y,a[1].y) vis[i+100][j+100] = 1;
    int cnt = 0, flg = 0;
    for (i = b[0].x; i < b[1].x; i++, cnt++)
        for (j = b[0].y-cnt; j <= b[0].y+cnt; j++)
            if (vis[i+100][j+100]) flg = 1;
    for (i = b[1].x; i <= b[3].x; i++, cnt--)
        for (j = b[0].y-cnt; j <= b[0].y+cnt; j++)
            if (vis[i+100][j+100]) flg = 1;
    if (flg == 0) cout << "NO\n"; else cout << "YES\n";
    return 0;
}