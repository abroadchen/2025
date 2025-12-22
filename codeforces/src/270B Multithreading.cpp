//
// Created by Psy.C on 2025/12/22.
//
/*
*n：存储序列的总长度
a0：存储序列的第一个元素
a：临时存储当前读取的元素
 *
 *如果当前元素a大于前一个元素a0，说明序列仍在递增，将计数器cnt加1
 *否则（当前元素不大于前一个元素），重置计数器为1，重新开始计算连续递增序列长度
 *更新a0为当前元素a，为下一次比较做准备
 *n-cnt，表示需要删除的元素个数。
 *O(n)时间复杂度的贪心算法实现
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, a0, a, cnt = 1; cin >> n >> a0;
    for (int i = 1; i < n; ++i) {
        cin >> a;
        if (a > a0) cnt++;
        else cnt = 1;
        a0 = a;
    }
    cout << n - cnt << '\n';
    return 0;
}