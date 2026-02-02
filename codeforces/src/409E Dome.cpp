//
// Created by Psy.C on 2026/2/2.
//
/**
* 时间复杂度：O(1)（最坏情况O(100)）
空间复杂度：O(1)
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define eps 1e-6
using namespace std;

db get(const db a, const db b) {
    const db d = sqrt(a*a + b*b);
    return a*b/d;//矩形面积与对角线长度的比值
}

int main() {
    fast;
    db x; cin >> x;
    for (int l = 1; l <= 10; ++l) for (int h = 1; h <= 10; ++h) {
        if (abs(x - get(l/2., h)) <= eps) {
            cout << l << ' ' << h << '\n';
            return 0;
        }
    }
    return 0;
}