//
// Created by Psy.C on 2025/11/28.
//
/*
*i != inv(i)：i不等于自己的反转数（排除回文数）
isPrime(i)：i本身是质数
isPrime(inv(i))：i的反转数也是质数
*如果三个条件都满足：
计数器k增加1
如果k等于n，输出结果并跳出循环
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool isPrime(const int x) {
    for (int i = 2; i * i <= x; ++i) if (x % i == 0) return false;
    return true;
}

int inv(int x) {
    int r = 0;
    for (; x; x /= 10) r = r * 10 + x % 10;
    return r;
}

int main() {
    fast;
    int n; cin>>n;
    for (int i = 0, k = 0; ; ++i) {
        if (i != inv(i) && isPrime(inv(i)) && isPrime(i)) {
            if (++k == n) { cout << i; break; }
        }
    }
    return 0;
}