//
// Created by Psy.C on 2025/11/2.
//

#include <iostream>
using namespace std;

const int N = 1000003;//这是一个质数，通常用于哈希或防止整数溢出的模运算

int dfs(int n) {
    if (n == 0 || n == 1) return 1;
    return 3 * dfs(n - 1) % N;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int i;
    while (cin >> i) cout << dfs(i) << '\n';
    return 0;
}