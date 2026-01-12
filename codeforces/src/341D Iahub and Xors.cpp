//
// Created by Psy.C on 2026/1/12.
//
/**
* 第1维：x%2（奇偶性）
第2维：y%2（奇偶性）
第3维：x坐标
第4维：y坐标
 *
*在位置(x,y)更新值val（异或操作）
外层循环：从x开始，按lowbit规律向上更新
内层循环：从y开始，按lowbit规律向右更新
t[x%2][y%2][i][j] ^= val：将val异或到对应位置
 *
*查询从(1,1)到(x,y)的前缀异或和
外层循环：从x开始，按lowbit规律向下
内层循环：从y开始，按lowbit规律向左
res ^= t[x%2][y%2][i][j]：累加异或值
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 1005
#define low_bit(x) (x&(-x))
using namespace std;

int n, t[2][2][N<<1][N<<1];
void update(const int x, const int y, const int val) {
    for (int i = x; i <= n; i += low_bit(i))
        for (int j = y; j <= n; j += low_bit(j))
            t[x%2][y%2][i][j] ^= val;
}

int query(const int x, const int y) {
    int res = 0;
    for (int i = x; i; i -= low_bit(i))
        for (int j = y; j; j -= low_bit(j))
            res ^= t[x%2][y%2][i][j];
    return res;
}

signed main() {
    fast;
    int q; cin >> n >> q;
    while (q--) {
        int op, x1, y1, x2, y2; cin >> op;
        if (op == 1) {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << (query(x1-1, y1-1)^query(x1-1, y2)^
                query(x2, y1-1)^query(x2, y2)) << '\n';
        } else {
            int k;
            cin >> x1 >> y1 >> x2 >> y2 >> k;
            update(x1, y1, k);
            update(x1, y2+1, k);
            update(x2+1, y1, k);
            update(x2+1, y2+1, k);
        }
    }
    return 0;
}