//
// Created by Psy.C on 2026/1/28.
//
/**
* a[N]: 存储输入数组
ha[N]={}: 计数数组 统计每个值的出现次数
 *
*时间复杂度
O(ans × (mx + n))，其中ans是轮数，mx是最大值
在最坏情况下可能达到O(n²)
空间复杂度
O(mx)，用于计数数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 105
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int a[N], ha[N]={}, mx;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
        ha[a[i]]++;
    }
    int ans = 0;
    while (n) {//还有元素未处理时
        int cnt = 0;//当前轮已选择元素数
        for (int i = 0; i <= mx; ++i) {//遍历所有可能的值
            while (ha[i] && i >= cnt) {//值 i 还有剩余且 i >= cnt 时
                ha[i]--;//减少值 i 的计数
                cnt++;//增加当前轮次已选择的元素数
                n--;//减少待处理元素总数
            }
        }
        ans++;//每完成一轮处理，增加计数
    }
    cout << ans << '\n';
    return 0;
}