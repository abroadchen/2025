//
// Created by Psy.C on 2025/12/19.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int cnt = 0, n = 8;
    string s;
    while (n--) {
        cin >> s;
        if (s == "WBWBWBWB" || s == "BWBWBWBW") cnt++;
    }
    if (cnt == 8) cout << "YES"; else cout << "NO";
    return 0;
}