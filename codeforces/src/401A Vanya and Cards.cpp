//
// Created by Psy.C on 2026/1/31.
//

#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, x; cin >> n >> x;
    int sum = 0;
    for (int i = 1, m; i <= n; ++i) {
        cin >> m; sum += m;//存储当前读入的数
    }
    int ans = static_cast<int>(fabs(sum)/x);//|sum|/x
    if (sum%x != 0) ans++;//相当于向上取整操作 不能被x整除（余数不为0）
    cout << ans << '\n';
    return 0;
}