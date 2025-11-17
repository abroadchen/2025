//
// Created by Psy.C on 2025/11/17.
//
/*
*tot = ⌊(n + 1) / 3⌋ （向下取整除法）
输出 ⌊tot / 12⌋ 和 tot mod 12
 *12 × quotient + remainder 的形式
 */
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    int tot = (n + 1) / 3;
    cout << tot / 12 << " " << tot % 12 << '\n';
    return 0;
}