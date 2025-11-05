//
// Created by Psy.C on 2025/11/5.
//
/*
*清空bit数组
对于每一位i（从1到63）：
比较a和b在第i位上的值是否不同
如果不同，则在bit[i-1]位置标记为1
这个循环的逻辑是：如果a和b在某一位上不同，说明在该位的低一位上可能存在进位
 *
*构造x和y的逻辑：

对于每一位i（从0到63）：
如果b在第i位是1，那么y的第i位设为1
否则（b在第i位是0）：
如果bit[i]被标记（表示需要进位），则x和y的第i位都设为1
这个构造基于异或的性质：如果x^y在某一位是1，那么x和y在该位必须不同；如果x^y在某一位是0，那么x和y在该位必须相同
 *
*如果 x + y = a 且 x ^ y = b，那么：

x & y = (a - b) / 2 （进位部分）
x ^ y = b （异或部分）
 *
*使用 endl 的情况：
需要立即看到输出（如调试信息、进度提示）
程序关键节点的输出
交互式程序中需要立即响应的输出
 *
*使用 "\n" 的情况：
大量输出数据
性能敏感的应用
不需要立即显示的输出
 */
#include <ios>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int N = 70, M = 64;
ull a, b;
int bit[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    while (cin >> a >> b) {
        memset(bit, 0, sizeof(bit));
        for (int i = 1; i < M; ++i) {
            if ((a & (1ll << i)) != (b & (1ll << i))) bit[i - 1] = 1;
        }
        ll x(0), y(0);
        for (int i = 0; i < M; ++i) {
            if (b & (1ll << i)) y |= 1ll << i;
            else {
                if (bit[i]) {
                    x |= 1ll << i;
                    y |= 1ll << i;
                }
            }
        }
        if (x + y == a && (x ^ y) == b) cout << x << " " << y << endl;
        else cout << -1 << endl;
    }
    return 0;
}