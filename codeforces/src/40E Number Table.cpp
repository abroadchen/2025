//
// Created by Psy.C on 2025/9/25.
//
/*
*n, m - 两个整数参数
fl - 标志位，用于记录是否交换了n和m
p[N] - 存储每个位置的乘积值的数组
K - 操作次数
M - 模数
c[N] - 计数数组，记录每个位置被操作的次数
fg - 标志位
rs(1) - 结果变量，初始化为1
 *
*读入三个值x, y, v
如果之前交换过n和m，则也交换x和y
将位置x的乘积p[x]乘以v
增加位置x的操作计数c[x]
 *
 *
*如果fg为0且位置i没有被操作过，则设置fg=1
如果位置i被操作了m次且乘积为正，则将结果rs设为0
否则，进行循环计算：将rs乘以2的(m-c[i]-1)次方并对M取模
 *
 *
 *如果n+m是奇数，则将结果rs设为0
 *
 *
 */
#include <iosfwd>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1111;
int n, m, fl, p[N], K, M, c[N], fg, rs(1);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;

    if (n < m) swap(n, m), fl = 1;
    memset(p, 1, sizeof(p));

    cin >> K;
    for (int x, y, v; K--;) {
        cin >> x >> y >> v;
        if (fl) swap(x, y);
        p[x] *= v;
        c[x]++;
    }

    cin >> M;
    for (int i = 1; i <= n; ++i) {
        if (!fg && !c[i]) fg = 1;
        else if (c[i] == m && p[i] > 0) rs = 0;
        else {
            for (int j = 1; j <= m - c[i] - 1; ++j)
                (rs *= 2) %= M;
        }
    }
    if ((n + m) & 1) rs = 0;
    cout << rs << endl;
    return 0;
}