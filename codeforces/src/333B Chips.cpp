//
// Created by Psy.C on 2026/1/10.
//
/**
* n：网格大小
m：操作次数
x, y：坐标
*row + 1：指向 row[1] 的指针
row + n + 1：指向 row[n+1] 的指针（不包含）
1：填充值
将 row[1] 到 row[n] 全部初始化为 1
 *
*从 row[2] 到 row[n-1] 求和（注意是 row + n，不包含 row[n]）
初始值为 0
 *
*n >= 3：n 至少为3
n % 2 == 1：n 是奇数
row[n/2+1] == 1：中间行标记为1
col[n/2+1] == 1：中间列标记为1
 */
#include <iostream>
#include <numeric>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1001
using namespace std;


int main() {
    fast;
    int n, m, x, y, row[N], col[N]; cin >> n >> m;
    fill(row + 1, row + n + 1, 1);
    fill(col + 1, col + n + 1, 1);
    while (m--) {
        cin >> x >> y;
        row[x] = 0;
        col[y] = 0;
    }
    int ans = accumulate(row + 2, row + n, 0) +
        accumulate(col + 2, col + n, 0);
    if (n >= 3 && n % 2 == 1 && row[n/2+1] == 1 && col[n/2+1] == 1) --ans;
    cout << ans << '\n';
    return 0;
}