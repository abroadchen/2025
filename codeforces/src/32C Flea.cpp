//
// Created by Psy.C on 2025/9/21.
//时间复杂度：O(1)每次计算 空间复杂度：O(1)


#include <iosfwd>
#include <iostream>
using namespace std;
typedef long long int ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll n, m, s;
    while (cin >> n >> m >> s) {// 循环读取输入直到文件结束
        ll x = (n - 1) / s + 1;// n除以s向上取整
        long int y = (m - 1) / s + 1;
        ll x1 = (n - 1) % s;
        ll y1 = (m - 1) % s;
        ll ans = x * y;
        // 如果x1不为0，将结果乘以(x1+1)
        if (x1 != 0) ans = ans * (x1 + 1);
        if (y1 != 0) ans = ans * (y1 + 1);
        cout << ans << endl;
    }

    return 0;
}