//
// Created by Psy.C on 2025/12/9.
//

#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    map<int, int> mp;//数字及其在数组中的位置索引
    ll x1 = 0, x2 = 0;//正面代价 反面代价
    int n; cin >> n;
    for (int i = 0, y; i < n; ++i) {
        cin >> y;
        mp[y] = i;//数值->索引
    }
    int q; cin >> q;
    for (int i = 0, x; i < q; ++i) {
        cin >> x;//找到x所需的步数
        x1 += mp[x] + 1;//"从左边开始找"的步数
        x2 += n - mp[x];//"从右边开始找"的步数
    }
    cout << x1 << ' ' << x2;
    return 0;
}