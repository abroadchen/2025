//
// Created by Psy.C on 2026/1/18.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, a[105], sum = 0, x, y, ans = 0;
    cin >> n;
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i]; sum += a[i];
    }
    cin >> x >> y;//[x,y]范围内
    for (ll i = 1, g1 = 0, g2 = 0; i <= n; ++i) {//遍历分割点i
        g1 += a[i]; g2 = sum - g1;//g1:前i个元素的和，g2:剩余元素的和
        if (g1 >= x && g1 <= y && g2 >= x && g2 <= y) {
            ans = i + 1;
            break;//找到第一个满足条件的分割点就退出循环
        }
    }
    cout << ans << '\n';
    return 0;
}