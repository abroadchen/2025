//
// Created by Psy.C on 2025/12/17.
//
/*
*当前窗口有效：
如果a[i] * 2 >= a[j]，说明窗口[i,j]内的元素满足某种条件
计算当前窗口大小：j - i + 1
需要删除的元素数：n - (j - i + 1)
更新最小删除数：ans = min(ans, n - (j - i + 1))
右指针j右移
*当前窗口无效：
如果a[i] * 2 < a[j]，说明窗口不满足条件
左指针i右移，缩小窗口
 *
 *时间复杂度：O(n log n)（主要是排序） 空间复杂度：O(1)（不考虑输入数组）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100000
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    ll n, a[N], i, j; cin>>n;
    for (i = 0; i < n; ++i) cin>>a[i];
    sort(a, a+n);
    if (a[0] * 2 == a[n - 1]) { cout << 0 << '\n'; return 0; }//最小元素的2倍是否等于最大元素 只需0次操作
    ll ans = n - 1; i = 0, j = 0;//最坏情况：只保留1个元素 需要删除(n-1)个元素
    while (j < n) {//右指针j未到达数组末尾时继续循环
        if (a[i] * 2 >= a[j]) {
            ans = min(ans, n - (j - i + 1));
            j++;
        } else i++;
    }
    cout << ans << '\n';
    return 0;
}