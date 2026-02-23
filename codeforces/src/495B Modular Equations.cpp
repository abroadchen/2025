//
// Created by Psy.C on 2026/2/20.
//
/**
如果 a mod x = b，那么：
a = k*x + b，其中 k ≥ 0
a - b = k*x
所以 x 是 (a-b) 的因子
并且 x > b（因为模运算的结果必须小于除数）

O(√(a-b))，因为只需要遍历到平方根
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b;
int main() {
    fast;
    cin >> a >> b;
    if (a < b) cout << "0\n";
    else if (a == b) cout << "infinity\n";
    else {
        int ans = 0;
        for (int i = 1, m = a-b; i <= sqrt(m); ++i) {
            if (m%i == 0) {
                if (i*i != m) {//是否是完全平方数
                    if (i > b) ans++;
                    if (m/i > b) ans++;
                } else {
                    if (i > b) ans++;//i = sqrt(m)，只计算一次
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}