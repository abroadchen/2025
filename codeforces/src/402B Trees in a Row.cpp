//
// Created by Psy.C on 2026/1/31.
//
/**
* cnt[1024]：统计数组，初始化为0
a[1024]：存储输入数组，初始化为0
1<<10 = 1024，所以数组大小为1024
 *
*x - (i-1)*k：计算每个数减去理论位置增长量后的值
如果结果大于0，就在cnt数组中对应位置计数加1
 *如果数组应该按规律递增k，则a[i]应该接近(i-1)*k
 *
*找到cnt数组中计数值最大的那个值
ans：最大计数值
b：对应的数值
ans个元素已经是正确的，所以需要修改n-ans个
 *
*循环处理每个位置
如果当前值a[i]不等于期望值b：
如果b < a[i]，输出'-'（需要减少）
否则输出'+'（需要增加）
输出位置i和需要改变的量abs(b - a[i])
b += k：下次期望值应该增加k

当前值 x 和位置 i，我们可以计算出基础值：
current_value = base_value + (i-1) * k
=> base_value = current_value - (i-1) * k
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;//n（数组长度）和k（增量）
    int cnt[1<<10]={}, a[1<<10]={};
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; a[i] = x;
        if (x - (i-1)*k > 0) ++cnt[x - (i-1)*k];//目标形式：[x, x+k, x+2k, x+3k, ...]
    }
    int ans = 0, b = -1;
    for (int i = 0; i < 1<<10; ++i) if (cnt[i] > ans) {
        ans = cnt[i]; b = i;
    }
    cout << n - ans << '\n';
    for (int i = 1; i <= n; ++i) {
        if (b != a[i]) {
            if (b < a[i]) cout << '-'; else cout << '+';
            cout << ' ' << i << ' ' << abs(b - a[i]) << '\n';
        }
        b += k;
    }
    return 0;
}