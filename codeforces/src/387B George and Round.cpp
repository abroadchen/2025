//
// Created by Psy.C on 2026/1/28.
//
/*
* 时间复杂度
O(n × m)，在最坏情况下需要检查所有配对
如果数组 b 中大部分元素都被使用，实际运行时间可能接近 O(n × m)
空间复杂度
O(n + m)，用于存储两个输入数组
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100006
using namespace std;


int main() {
    fast;
    int n, m, a[N], b[N], cnt = 0; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    for (int i = 0, j; i < n; ++i) {
        for (j = 0; j < m; ++j) if (b[j] != 0) {//跳过已使用的元素
            if (b[j] >= a[i]) { b[j] = 0; break; }//标记 b[j] 为已使用
        }
        if (j == m) cnt++;//内层循环完整执行（没找到匹配），说明 a[i] 无法匹配，计数器加1
    }
    cout << cnt << '\n';
    return 0;
}