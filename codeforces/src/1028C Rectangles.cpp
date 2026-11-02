//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
矩形：左下(x1,y1)、右上(x2,y2)
node a[N];     // 原始 n 个矩形
node pre[N];   // 前缀：前 i 个矩形的交集
node suf[N];   // 后缀：i..n 个矩形的交集
node ans;      // 待输出的答案点
初始化：空交汇边界 (-inf,-inf, inf,inf)。
pre[i] 表示前 i 个矩形的交集（x1 取所有左下角的最大，x2 取所有右上角的最小）
对称地，suf[i] 表示从第 i 个到第 n 个矩形的交集
删掉第 i 个矩形后，剩余矩形的交集 = 前缀 pre[i-1] 与后缀 suf[i+1] 的交集。
判断交集非空的条件：x2 >= x1 && y2 >= y1。
找到第一个使剩余交集非空的 i，输出该交集左下角一点 (ans.x1, ans.y1)，然后 break
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define per(i,n) for (int i=n; i>=1; i--)
using namespace std;

constexpr int N = 2e5+5, inf = 0x3f3f3f3f;

struct node { int x1, y1, x2, y2; } a[N], pre[N], suf[N], ans;

int n;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
    pre[0].x1 = pre[0].y1 = -inf;
    pre[0].x2 = pre[0].y2 = inf;
    rep(i,n) {
        pre[i].x1 = max(pre[i-1].x1, a[i].x1);
        pre[i].y1 = max(pre[i-1].y1, a[i].y1);
        pre[i].x2 = min(pre[i-1].x2, a[i].x2);
        pre[i].y2 = min(pre[i-1].y2, a[i].y2);
    }
    suf[n+1].x1 = suf[n+1].y1 = -inf;
    suf[n+1].x2 = suf[n+1].y2 = inf;
    per(i,n) {
        suf[i].x1 = max(suf[i+1].x1, a[i].x1);
        suf[i].y1 = max(suf[i+1].y1, a[i].y1);
        suf[i].x2 = min(suf[i+1].x2, a[i].x2);
        suf[i].y2 = min(suf[i+1].y2, a[i].y2);
    }
    rep(i,n) {
        ans.x1 = max(pre[i-1].x1, suf[i+1].x1);
        ans.y1 = max(pre[i-1].y1, suf[i+1].y1);
        ans.x2 = min(pre[i-1].x2, suf[i+1].x2);
        ans.y2 = min(pre[i-1].y2, suf[i+1].y2);
        if (ans.x2 >= ans.x1 && ans.y2 >= ans.y1) {
            cout << ans.x1 << ' ' << ans.y1;
            break;
        }
    }
    return 0;
}