//
// Created by Psy.C on 2026/2/2.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    if (const int x = n>>1; x == 0 && k == 0) cout << '1';
    else if (x > k || x == 0) cout << "-1";
    else {
        int l = k - x + 1;
        cout << l << ' ' << (l<<1);
        l = l<<1|1;//从 2*l + 1 开始的连续 n-2 个数字
        n -= 2;//已经输出了2个数
        while (n--) cout << ' ' << l++;//输出剩余的连续数字
    }
    return 0;
}