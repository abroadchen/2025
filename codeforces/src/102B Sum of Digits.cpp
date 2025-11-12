//
// Created by Psy.C on 2025/11/12.
//
/*
*x % 10 取出 x 的个位数字，并加到 ans 中。
x /= 10 将 x 除以 10（去掉个位数字）。
这个循环的作用是计算 x 的所有数位的数字之和。
 *
*s[i] - '0'：将字符转换为对应的数字（例如 '5' 转换为 5）。
将每个数字累加到 cur 中，得到初始数字和
 *
*当 cur 大于 9 时继续循环：
cur = f(cur)：调用函数 f 计算 cur 的各位数字之和，并更新 cur。
++t：增加变换次数
 *循环直到 cur 变成个位数（小于等于 9）
 */
#include <iostream>
using namespace std;


int f(int x) {
    int ans(0);
    while (x > 0) ans += x % 10, x /= 10;
    return ans;
}


int main() {
    string s; getline(cin, s);
    if (s.length() == 1) puts("0");
    else {
        int cur(0), t(1);
        for (int i = 0; i < s.length(); ++i) {
            cur += s[i] - '0';
        }
        while (cur > 9) cur = f(cur), ++t;
        printf("%d\n", t);
    }
    return 0;
}