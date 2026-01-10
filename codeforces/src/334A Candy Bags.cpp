//
// Created by Psy.C on 2026/1/10.
//
/**
* 第0列（第一个数字）：i + 1
第 j 列（j > 0）：n*j + (i+j)%n + 1
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << i + 1;//从1到n的数字 每一行的第一个数字
        for (int j = 1; j < n; ++j) cout << ' ' << n*j+(i+j)%n+1;
        cout << '\n';
    }
    return 0;
}