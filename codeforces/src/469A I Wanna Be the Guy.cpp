//
// Created by Psy.C on 2026/2/13.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

int n, vis[N], x, num, y;

int main() {
    fast;
    cin >> n >> x;
    for (int i = 0; i < x; ++i) {
        cin >> num;
        vis[num] = 1;
    }
    cin >> y;
    for (int i = 0; i < y; ++i) {
        cin >> num;
        vis[num] = 1;
    }
    int flag = 1;
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) {
            cout << "Oh, my keyboard!\n";
            flag = 0;
            break;
        }
    if (flag) cout << "I become the guy.\n";
    return 0;
}