//
// Created by Psy.C on 2026/2/4.
//
/**
* n：数组长度
t：阈值
c：连续元素个数
*e：窗口右端点
cnt：当前连续满足条件的元素个数
ans：满足条件的子序列数量
 *
*当前元素满足条件（≤ t）
连续计数未达到c
没有超出数组边界
 *
*--cnt：移除窗口最左边的元素
++ans：增加有效序列计数
*++e：跳过不满足条件的元素
cnt = 0：重置连续计数
 *
*时间复杂度：O(n)
空间复杂度：O(n)，数组存储
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200015
using namespace std;


int main() {
    fast;
    int n, t, c, a[N]{}; cin >> n >> t >> c;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int e = 0, cnt = 0, ans = 0;
    while (e < n) {
        while (a[e] <= t && cnt < c && e < n) ++cnt, ++e;
        //移除窗口最左边的元素
        if (cnt == c) { --cnt; ++ans; }//找到了一个有效序列
        else { ++e; cnt = 0; }//重置，跳过不满足的元素
    }
    cout << ans << '\n';
    return 0;
}