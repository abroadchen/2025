//
// Created by Psy.C on 2025/12/11.
//
/*
*从3开始，每次步进2（处理连续的奇数）：
对于每个奇数i，输出"i+1 i"
这样就形成了配对：(2,1), (4,3), (6,5), (8,7).
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    if (n % 2 == 1) cout << -1 << '\n';
    else {
        cout << "2 1";
        for (int i = 3; i < n; i += 2)
            cout << ' ' << i + 1 << ' ' << i;
        cout << '\n';
    }
    return 0;
}