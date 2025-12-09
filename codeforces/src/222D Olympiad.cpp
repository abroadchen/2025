//
// Created by Psy.C on 2025/12/8.
//
/*
*cnt = n - 1：初始化cnt为数组最后一个元素的索引
ans = 0：初始化答案为0
遍历数组a，对于每个a[i]：
如果a[i] + b[cnt] >= x（当前配对满足条件）
则cnt--（移动到下一个较小的b元素）
ans = n - 1 - cnt：计算满足条件的配对数
重新设置cnt = n - 1为下一轮准备
 *
*遍历数组b，对于每个b[i]：
如果b[i] + a[cnt] >= x（当前配对满足条件）
则cnt--（移动到下一个较小的a元素）
ans = max(ans, n - cnt - 1)：取两次计算结果的最大值
 *
*时间复杂度：O(n log n)（主要是排序）
空间复杂度：O(n)
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int a[N], b[N];

int main() {
    fast;
    int n, x; cin >> n >> x;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    sort(a, a + n);
    sort(b, b + n);
    int cnt = n - 1, ans = 0;
    for (int i = 0; i < n; ++i) if (a[i] + b[cnt] >= x) cnt--;
    ans = n - 1 - cnt; cnt = n - 1;
    for (int i = 0; i < n; ++i) if (b[i] + a[cnt] >= x) cnt--;
    ans = max(ans, n - cnt - 1);
    cout << "1 " << ans << '\n';
    return 0;
}