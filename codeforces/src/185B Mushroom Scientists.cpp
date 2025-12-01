//
// Created by Psy.C on 2025/12/1.
//

#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

double s, a, b, c;

int main() {
    fast;
    cin >> s >> a >> b >> c;
    if (a + b + c == 0) return cout << fixed << setprecision(8) <<
        s << " 0 0\n", 0;
    cout << fixed << setprecision(12) << s * a / (a + b + c) << ' ' <<
        s * b / (a + b + c) << ' ' << s * c / (a + b + c) << '\n';
    return 0;
}