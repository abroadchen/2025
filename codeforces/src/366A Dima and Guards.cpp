//
// Created by Psy.C on 2026/1/20.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int mp[5][4], k;//存储4个选项的信息（第0行不使用）k：用于存储找到的选项索引
    for (int i = 1, a, b, c, d; i <= 4; ++i) {
        cin >> a >> b >> c >> d;
        mp[i][1] = min(a, b);
        mp[i][2] = min(c, d);
        mp[i][3] = mp[i][1] + mp[i][2];
    }
    for (k = 1; k <= 4; ++k) if (mp[k][3] <= n) break;//当前选项的和≤n 找到第一个满足条件的选项就跳出循环
    if (k != 5) cout << k << ' ' << mp[k][1] << ' ' << n-mp[k][1] << '\n';
    else cout << "-1\n";
    return 0;
}