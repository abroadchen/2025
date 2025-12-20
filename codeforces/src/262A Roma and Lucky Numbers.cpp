//
// Created by Psy.C on 2025/12/20.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, ans = 0; cin >> n >> k;
    string s;
    while (n--) {//循环n次，每次处理一个字符串
        int cnt = 0; cin >> s;
        for (const char i : s) { if (i == '4' || i == '7') cnt++; }
        if (cnt <= k) ans++;
    }
    cout << ans << '\n';
    return 0;
}