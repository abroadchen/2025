//
// Created by Psy.C on 2026/1/8.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    cout << n + m - 1 << '\n';//从左上角(1,1)到右下角(n,m)的最短路径长度
    for (int i = 1; i <= m; ++i) cout << "1 " << i << '\n';//沿着第一行从(1,1)移动到(1,m)
    for (int i = 2; i <= n; ++i) cout << i << " 1" << '\n';//沿着第一列从(2,1)移动到(n,1)
    return 0;
}