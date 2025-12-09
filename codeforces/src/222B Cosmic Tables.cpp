//
// Created by Psy.C on 2025/12/8.
//
/*
 *
*n：矩阵行数
m：矩阵列数
k：操作次数
*r[i] = i：初始时第i行对应实际第i行
c[i] = i：初始时第i列对应实际第i列
 *
*'r'操作：交换行映射swap(r[x], r[y])
不直接交换矩阵数据，而是交换行索引映射
'c'操作：交换列映射swap(c[x], c[y])
不直接交换矩阵数据，而是交换列索引映射
'g'操作：获取元素值cout << p[r[x]][c[y]] << '\n'
通过映射数组获取实际位置的元素值
default：默认情况，不执行任何操作
 *
 *交换操作只需O(1)时间，不需要移动大量数据
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1001
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

int r[N], c[N], p[N][N];

int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    rep(i,n) r[i] = i;
    rep(i,m) c[i] = i;
    rep(i,n) rep(j,m) cin >> p[i][j];
    while (k--) {
        char s[2]; int x, y;
        cin >> s >> x >> y;
        switch (s[0]) {
            case 'r':
                swap(r[x], r[y]);
                break;
            case 'c':
                swap(c[x], c[y]);
                break;
            case 'g':
                cout << p[r[x]][c[y]] << '\n';
                break;
            default:
                break;
        }
    }
    return 0;
}