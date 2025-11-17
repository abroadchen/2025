//
// Created by Psy.C on 2025/11/17.
//
/*
*计算下界low：
a + 1：大于a的最小整数
n - b：使得与b的和不超过n的最大整数
取两者的最大值作为有效范围的下界
 *
*下界：max(a + 1, n - b)
如果a + 1 > n - b，则无解
否则有效范围是[max(a+1, n-b), n-b]
 *
*如果下界 ≤ n-b：个数 = (n - b) - max(a+1, n-b) + 1
化简得：n - max(a+1, n-b) + 1
 */
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, a, b; cin >> n >> a >> b;
    int low = max(a + 1, n - b);
    cout << n - low + 1 << '\n';
    return 0;
}