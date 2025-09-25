//
// Created by Psy.C on 2025/9/25.
//
/*
 *
*如果n是偶数：有n/2个奇数和n/2个偶数，总配对数为(n/2) * (n/2) = n²/4
如果n是奇数：有(n+1)/2个奇数和(n-1)/2个偶数，总配对数约为n²/4
 *
 *
 */
#include <ios>
#include <iosfwd>
#include <iostream>
using namespace std;

int main() {

    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n, i, j; cin >> n; cout << n * n / 4;//奇数与偶数配对的组合数

    for (i = 1; i <= n; i += 2)//遍历所有奇数
        for (j = 2; j <= n; j += 2)//遍历所有偶数
            cout << '\n' << i << ' ' << j;//对于每一对(奇数i, 偶数j)，输出换行符和这对数字
    return 0;
}