//
// Created by Psy.C on 2026/1/26.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int m; cin >> m;
    vector<int> b(m+1);
    int ans = m, mx = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
        mx = max(mx, b[i]);
    }
    sort(b.begin() + 1, b.begin() + m + 1);
    for (int i = 1; i <= m; ++i) {
        //当前元素等于后两个位置的元素
        if (b[i] == b[i + 2]) b[i] = 0, ans--;
        if (b[i] == mx) {
            //从当前位置之后的所有元素都设置为 0
            for (int j = i + 1; j <= m; ++j) b[j] = 0, ans--;
            break;
        }
    }
    cout << ans << '\n';
    sort(b.begin() + 1, b.begin() + m + 1, [](const int x, const int y) {
        return x > y;
    });
    for (int i = ans; i >= 1; --i) if (b[i] != b[i - 1]) {//当前元素不等于前一个元素
        cout << b[i] << ' ';
        b[i] = 0;
    }
    for (int i = 1; i <= ans; ++i) if (b[i] != 0) cout << b[i] << ' ';
    return 0;
}