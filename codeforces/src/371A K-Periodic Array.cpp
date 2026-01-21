//
// Created by Psy.C on 2026/1/21.
//
/**
* 将数组分成k个组：{a[1], a[1+k], a[1+2k], ...}、{a[2], a[2+k], a[2+2k], ...} 等
每组包含 x = n/k 个元素（假设n能被k整除）
 *
*外层 (i): 遍历k个起始位置（第i组）
中层 (j): 遍历第i组中的每个元素
内层 (l): 统计与 a[j] 相同值的元素个数
 *
*m: 第i组中最频繁值的出现次数
x - m: 第i组需要修改的元素个数（使所有元素都变成最频繁的那个值）
 *
*三层嵌套循环：O(k × (n/k) × (n/k)) = O(n²/k)
在最坏情况下为 O(n²)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    int a[105];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int ans = 0;
    const int x = n / k;
    for (int i = 1, m; i <= k; ++i) {
        m = 0;
        for (int j = i, cnt; j <= n; j += k) {
            cnt = 0;
            for (int l = j; l <= n; l += k) {
                if (a[j] == a[l]) cnt++;
                if (cnt > m) m = cnt;
            }
        }
        ans += x - m;
    }
    cout << ans << '\n';
    return 0;
}