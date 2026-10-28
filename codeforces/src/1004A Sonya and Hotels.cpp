//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
n：物体个数，d：最大覆盖半径/间隔限制，a[]：各物体坐标，cnt(2)：从 2 个端点开始计数
读入 n 个坐标。题目保证已排好序（递增）
对每一对相邻物 x：
若间距 > 2d：两个本在间距 d 内的物体间无法靠单个中继覆盖，必须塞 2 个新点，让整段连续。
若间距 == 2d：中间差正好放 1 个点填满。
若 x < 2d（即 ≤ d 或介于 d 和 2d 之间，代码里不满足上面两个分支）：不加点，即相邻两物自身就能连续覆盖（间距在 d 内），跳过
输出总共需要的点数 = 初始 2 个端点 + 各段加上的中间点
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 0; i < n; ++i)
using namespace std;

constexpr int N = 105;

int n, d, i, a[N], cnt(2);
int main() {
    fast;
    cin >> n >> d;
    rep(i,n) cin >> a[i];
    rep(i,n-1) {
        int x = a[i+1] - a[i];
        if (x > 2*d) cnt += 2;
        else if (x == 2*d) cnt++;
    }
    cout << cnt;
    return 0;
}