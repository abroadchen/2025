//
// Created by Psy.C on 2026/10/16.
//
/**
若 n > 36，输出 -1（无解）。因为数字 6 是各位和的上限主力（6+6+... 每次 +6），n 最大到 36（6 张全 6：6×6=36）
n 偶：输出 n/2 个 8（如 n=8 → "8888"，4 个 8）。
n 奇：输出 1 个 6 再接 (n-1)/2 个 8
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int main() {
    fast;
    int n; cin >> n;
    if (n > 36) cout << -1 << '\n';
    else {
        if (n%2) { cout << 6; n--; }
        while (n) { cout << 8; n -= 2; }
        cout << '\n';
    }
    return 0;
}