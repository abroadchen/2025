//
// Created by Psy.C on 2025/12/10.
//
/*
*n: 序列长度
d: 目标差值
l: 每个元素的最大值限制
*k1 = (n + 1) / 2: 奇数位置的元素个数（第1,3,5,...位置）
k2 = n / 2: 偶数位置的元素个数（第2,4,6,...位置）
 *
*l * k1 - k2 < d: 当奇数位置全取最大值l，偶数位置全取最小值1时，能得到的最大差值
d < k1 - l * k2: 当奇数位置全取最小值1，偶数位置全取最大值l时，能得到的最小差值
如果d超出这个范围，则无解，输出"-1"并退出
 *
*构造数组a：
从左到右依次确定每个位置的值
如果当前d > 0，当前位置取最大值l，然后更新d = l - d
如果当前d ≤ 0，当前位置取最小值1，然后更新d = 1 - d
这种策略是为了逐步逼近目标差值d
*调整最后一个元素：将剩余的差值d从最后一个元素中扣除
这样可以精确达到目标差值
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 105
using namespace std;


int main() {
    fast;
    int n, d, l; cin>>n>>d>>l;
    const int k1 = (n + 1) / 2, k2 = n / 2;
    if (l * k1 - k2 < d || d < k1 - l * k2) return cout << "-1", 0;
    int a[N];
    for (int i = 1; i <= n; ++i) {
        if (d > 0) a[i] = l, d = l - d;
        else a[i] = 1, d = 1 - d;
    }
    a[n] -= d;
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}