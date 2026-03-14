//
// Created by Psy.C on 2026/3/13.
//
/**
N: 最大价格范围
n: 订单总数
s: 输出限制数量
p: 价格
q: 数量
b[N]: 买单数组（Buy orders），b[i]表示价格为i的买单总量
S[N]: 卖单数组（Sell orders），S[i]表示价格为i的卖单总量
d: 订单类型（'B'或'S'）

如果是买单('B')，在对应价格累加买入数量
如果是卖单('S')，在对应价格累加卖出数量
从价格0开始统计有订单的卖单价格数量
当达到输出限制s或扫描完所有价格时停止
从最高价格向下输出所有有卖单的价格（保证输出s个最低价卖单）
从最高价格开始统计有订单的买单价格数量
当达到输出限制s或扫描完所有价格时停止
从最高价格向下输出买单（保证输出s个最高价买单）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, s, p, q, b[N], S[N];
char d;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) {
        cin >> d >> p >> q;
        if (d == 'B') b[p] += q;
        else S[p] += q;
    }
    int c = 0, i = 0;
    for (; i <= N-5 && c < s; ++i)
        if (S[i] > 0) c++;
    for (int j = i-1; j >= 0; --j)
        if (S[j] > 0)
            cout << "S " << j << ' ' << S[j] << '\n';
    i = N-5, c = 0;
    for (; i >= 0 && c < s; --i)
        if (b[i] > 0) c++;
    for (int j = N-5; j >= i+1; --j)
        if (b[j] > 0)
            cout << "B " << j << ' ' << b[j] << '\n';
    return 0;
}