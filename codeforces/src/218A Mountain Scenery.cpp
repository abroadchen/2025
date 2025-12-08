//
// Created by Psy.C on 2025/12/8.
//
/*
*n：大小参数
k：允许的操作次数
r[N]：存储数字序列的数组
从输入读取n、k和第一个元素r[0]
 *
*k > 0：还有剩余操作次数
r[i] > r[i-1] + 1：当前元素比左邻居大超过1
r[i] > r[i+1] + 1：当前元素比右邻居大超过1
如果满足所有条件：
减少k（使用一次操作）
将r[i]减1
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 201
using namespace std;


int main() {
    fast;
    int n, k, r[N];
    cin >> n >> k >> r[0];
    for (int i = 1; i <= n * 2; i += 2) {//读取数字对
        cin >> r[i] >> r[i + 1];
        if (k > 0 && r[i] > r[i-1] + 1 && r[i] > r[i+1] + 1) {
            k -= 1;
            r[i] -= 1;
        }
    }
    cout << r[0];
    for (int i = 1; i <= n * 2; ++i) cout << ' ' << r[i];
    cout << '\n';
    return 0;
}