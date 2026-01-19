//
// Created by Psy.C on 2026/1/19.
//
///O(q × 64) = O(64q)，其中q是测试用例数量
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;


int main() {
    fast;
    int q; char ch; cin >> q;
    while (q--) {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        rep(i,8) rep(j,8) {
            cin >> ch;
            if (ch == 'K') {
                if (x1) x2 = i, y2 = j;//记录第二个'K'的位置
                else x1 = i, y1 = j;
            }
        }
        if ((x1 - x2) % 4 == 0 && (y1 - y2) % 4 == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}