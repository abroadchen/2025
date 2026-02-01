//
// Created by Psy.C on 2026/2/1.
//
/**
* 预处理阶段：O(n²) - 读入矩阵并计算主对角线
查询阶段：O(q) - 每次查询O(1)时间
总体复杂度：O(n² + q)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1002
using namespace std;


int main() {
    fast;
    int n; cin >> n;//主对角线异或值累加器
    int a[N][N], A = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        cin >> a[i][j];
        if (i == j) A ^= a[i][j];
    }
    int q, x; cin >> q;
    while (q--) {
        cin >> x;
        if (x == 3) cout << A;
        else { cin >> x; A ^= 1; }//修改矩阵并影响A的值
    }
    return 0;
}