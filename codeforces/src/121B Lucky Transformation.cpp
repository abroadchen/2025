//
// Created by Psy.C on 2025/11/17.
//
/*
*n：字符串长度
k：操作次数
d：输入的字符串
 *
 *循环遍历字符串，当索引i小于n且还有操作次数k时继续循环
*检查是否存在模式"477"：
当前字符是'4'
下一字符是'7'
下下字符是'7'
并且当前位置i是偶数（!(i & 1)等价于i % 2 == 0）
如果满足条件，将k对2取模（k %= 2）
 *如果还有操作次数k，并且当前字符是'4'，下一字符是'7'
*根据当前位置i的奇偶性决定如何修改：
如果i是奇数（i & 1为真），将d[i]改为d[i+1]的值（即把'4'改成'7'）
如果i是偶数，将d[i+1]改为d[i]的值（即把'7'改成'4'）
*将循环索引i减2（回到前面重新检查）
操作次数k减1
 *输出修改后的字符串d
 */
#include <iostream>
using namespace std;

int n, k;
string d;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> d;
    for (int i = 0; i < n && k; ++i) {
        if (d[i] == '4' && d[i + 1] == '7' &&
            d[i + 2] == '7' && !(i & 1)) k %= 2;
        if (k && d[i] == '4' && d[i + 1] == '7') {
            if (i & 1) d[i] = d[i + 1];
            else d[i + 1] = d[i];
            i -= 2;
            k--;
        }
    }
    cout << d;
    return 0;
}