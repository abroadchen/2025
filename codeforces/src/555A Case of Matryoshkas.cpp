//
// Created by Psy.C on 2026/3/10.
//
/**
cnt: 计数器，统计满足条件的元素数量
外层循环：处理k个序列
c: 当前序列的长度
内层循环：处理当前序列中的每个元素
x: 当前读入的元素值
if (x == j) cnt++;: 如果元素值等于其在序列中的位置（从1开始计数），则计数器加1

时间复杂度：O(total_elements)，其中total_elements是所有序列中元素的总数
空间复杂度：O(1)，只使用了常数额外空间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
int n, k;
int main() {
    fast;
    cin >> n >> k;
    int cnt = 0;
    for (int i = 1, c; i <= k; ++i) {
        cin >> c;
        for (int j = 1, x; j <= c; ++j) {
            cin >> x;
            if (x == j) cnt++;
        }
    }
    int ans = 2*(n - cnt) - k + 1;
    cout << ans << '\n';
    return 0;
}