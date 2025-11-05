//
// Created by Psy.C on 2025/11/6.
//

#include <cstdio>
#include <iostream>
using namespace std;

long int x, y;
bool w(1);

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> x >> y;
    while (x * 10 + y >= 22 && y >= 2) {
        if (w || y < 12) {
            x -= 2;
            y -= 2;
        } else if (y < 22) {
            x--;
            y -= 12;
        } else y -= 22;
        w = !w;
    }
    if (w) cout << "Hanako";
    else cout << "Ciel";
    return 0;
}