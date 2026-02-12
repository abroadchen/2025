//
// Created by Psy.C on 2026/2/12.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, s;

int main() {
    fast;
    cin >> n >> s;//n（数据总数）和s（目标值）
    int res = -1;//最大值
    for (int i = 0, d, c; i < n; ++i) {
        cin >> d >> c;//距离和代价
        if (d > s || (d  == s && c > 0)) continue;
        int ans = -1;//当前答案
        const int p = 100*d + c;//d作为百位，c作为个位
        ans = (100*s - p) % 100;
        res = max(res, ans);
    }
    cout << res;
    return 0;
}