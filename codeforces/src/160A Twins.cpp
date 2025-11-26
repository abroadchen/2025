//
// Created by Psy.C on 2025/11/25.
//
/*
*tot：所有元素的总和
ans1：需要选取的元素个数
ans2：已选取元素的和
 *
*循环条件：已选取元素的和不超过总和的一半
每次循环：
增加选取元素个数ans1
从大到小选取元素（因为数组已排序），累加到ans2
v[n - ans1] 表示从末尾开始第ans1个元素（即第ans1大的元素）
 *
*排序：O(n log n)
选取过程：O(k)，k为选取元素个数
总体：O(n log n)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<int> v(n);
    int tot = 0, ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; ++i) { cin >> v[i]; tot += v[i]; }
    sort(v.begin(), v.end());
    while (ans2 <= tot / 2) {
        ++ans1;
        ans2 += v[n - ans1];
    }
    cout << ans1 << '\n';
    return 0;
}