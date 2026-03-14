//
// Created by Psy.C on 2026/3/14.
//
/**
n: 区间数量
x: 初始位置
l, r: 当前可行区间的左右边界（初始化为[x,x]）
ans: 总移动距离
循环处理n个区间[y1, y2]
情况1: 新区间完全在右侧
y1 > r: 新区间左端点在当前右边界右侧
l = r: 左边界移到右边界
ans += y1 - r: 累加移动距离
r = y1: 右边界设为新区间左端点
新区间完全在左侧
y2 < l: 新区间右端点在当前左边界左侧
r = l: 右边界移到左边界
ans += l - y2: 累加移动距离
l = y2: 左边界设为新区间右端点
区间有重叠
l = max(l, y1): 左边界更新为较大值
r = min(r, y2): 右边界更新为较小值

时间复杂度: O(n) 空间复杂度: O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n, x;
int main() {
    fast;
    cin >> n >> x;
    int l = x, r = x; ll ans = 0;
    for (int i = 0, y1, y2; i < n; ++i) {
        cin >> y1 >> y2;
        if (y1 > r) { l = r; ans += y1 - r; r = y1; }
        else if (y2 < l) { r = l; ans += l - y2; l = y2; }
        else { l = max(l, y1); r = min(r, y2); }
    }
    cout << ans << '\n';
    return 0;
}