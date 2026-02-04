//
// Created by Psy.C on 2026/2/4.
//
/**
* 时间复杂度：O(n + a + b)
空间复杂度：O(1)（固定大小数组）
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, a, b; cin >> n >> a >> b;
    int f[101], m, i;
    memset(f, 1, sizeof(f));
    for (i = 1; i <= a; ++i) {
        cin >> m;
        f[m] = 1;//将对应位置标记为1
    }
    for (i = 1; i <= b; ++i) {
        cin >> m;
        f[m] = 2;//这会覆盖之前可能的值（1变成2）
    }
    for (i = 1; i <= n; ++i) cout << f[i] << ' ';
    return 0;
}