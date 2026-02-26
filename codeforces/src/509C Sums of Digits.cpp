//
// Created by Psy.C on 2026/2/26.
//
/**
len: 记录当前数字的长度
d[10000]: 存储数字的各位数字（倒序存储，索引1是个位）

将值r加到当前由数组d表示的数字上
从最低位（索引1）向高位处理
对于每个位置i，增加d[i]直到r变为0或d[i]达到9
更新len以维护数字的实际长度

当x <= 0时，我们需要确保结果仍比前一个大
从右到左清空数字位，将它们加到x上
当找到可以递增的位置（数字<9）时，进行递增
然后用剩余值调用get()确保适当的增量

从最高位到最低位输出构造的数字
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 301;

int len, d[10000];
void get(int r) {
    for (int i = 1; r; ++i) {
        if (len < i) len = i;
        while (r && d[i] < 9) {
            r--;
            d[i]++;
        }
    }
}

int n, b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) {
        if (int x = b[i] - b[i-1]; x > 0) get(x);
        else {
            for (int j = 1; ; ++j) {
                if (j > len) len = j;
                if (x > 0 && d[j] < 9) {
                    x--; d[j]++; get(x);
                    break;
                }
                x += d[j];
                d[j] = 0;
            }
        }
        for (int j = len; j >= 1; --j) cout << d[j];
        cout << '\n';
    }
    return 0;
}