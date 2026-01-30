//
// Created by Psy.C on 2026/1/30.
//
/**
* now = a[1] + (i-1)*x：理想等差数列的第i项
b[i] = a[i] - now：实际值与理想值的差距
 *
 *归一化处理
 *将所有差值平移，使最小值为0
 *计算最大差值
 *
 *调整首项
 *返回 (最大差值+1)/2
 *
*get(step) 评估步长为 step 时的"好坏程度"
值越小越好
*寻找最佳等差数列：start, start+step, start+2*step, ...
使原数组与等差数列的偏差最小

目标：最小化 max(|a[i] - (s + (i-1)*x)|)
get(x) 计算在固定步长 x 下的最小可能偏差
通过调整起始值 s 来优化
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define N 1010
#define inf 1e9
using namespace std;

int b[N], a[N], n;//辅助数组 输入数组 数组长度
int get(const int x) {//步长参数
    b[1] = 0;//设置第一个元素为0
    int mn = 0, mx = 0;
    //循环计算 b[i] = a[i] - (a[1] + (i-1)*x)
    for (int i = 2, now = a[1] + x; i <= n; ++i, now += x) {
        b[i] = a[i] - now; mn = min(mn, b[i]);
    }
    for (int i = 1; i <= n; ++i) {//将所有 b[i] 减去最小值，使其非负
        b[i] -= mn; mx = max(mx, b[i]);
    }
    b[1] -= (mx+1)>>1;//调整 b[1]
    return (mx+1)>>1;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int ans = inf; ii an;//最优解的参数对
    for (int step = 0; step <= 30000; ++step) {
        if (const int t = get(step); ans > t) { ans = t; an.first = a[1] - b[1]; an.second = step; }
        else if (ans == t) an = min(an, {a[1] - b[1], step});//结果相同，选择字典序较小的
    }
    cout << ans << '\n';
    cout << an.first << ' ' << an.second << '\n';
    return 0;
}