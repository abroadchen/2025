//
// Created by Psy.C on 2026/2/3.
//
/**
* 时间复杂度：O(n) - 单次遍历数组
空间复杂度：O(n) - 存储输入数组
 *
 *(y / b) * b = y - (y % b)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;


int main() {
    fast;
    int n; ll a, b, x[N]; cin >> n >> a >> b;
    for (int i = 0; i < n; ++i) cin >> x[i];
    for (int i = 0; i < n; ++i) {
        const ll p = x[i]*a/b;
        cout << x[i] - p*b/a - (p*b%a != 0) << ' ';
    }
    return 0;
}