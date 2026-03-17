//
// Created by Psy.C on 2026/3/18.
//
/**
从a[i]中减去它的奇偶性标记
如果a[i]原来是奇数，现在变为偶数（减1）
如果a[i]原来是偶数，保持不变
这样处理后，a[i]一定是偶数

a[i]>>1是将a[i]右移1位，相当于a[i]/2
将a[i]的一半加到a[i+1]上
这类似于进位操作，当a[i]有偶数个元素时，每两个可以"合并"成一个更高位的元素
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+1000;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0, w; i < n; ++i) {
        cin >> w; a[w]++;
    }
    int ans = 0;
    for (int i = 0; i < N-1; ++i) {//遍历数组a的所有有效位置
        ans += a[i]&1;
        a[i] -= a[i]&1; //a[i]一定是偶数
        a[i+1] += a[i]>>1;//类似于进位操作
    }
    cout << ans << '\n';
    return 0;
}