//
// Created by Psy.C on 2026/1/8.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10000000
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    for (int i = N - n; i < N; ++i) cout << i << ' ';//输出连续的n个整数
    return 0;
}