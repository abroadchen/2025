//
// Created by Psy.C on 2026/1/19.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

void out(int x) {
    if (x < 5) cout << "O-"; else cout << "-O";
    cout << '|';
    x %= 5;
    for (int i = 0; i < x; ++i) cout << 'O';
    cout << '-';
    for (int i = 0; i < 4 - x; ++i) cout << 'O';
    cout << '\n';
}

int main() {
    fast;
    char s[15]; cin >> s;
    const int len = static_cast<int>(strlen(s));
    for (int i = len - 1; i >= 0; --i) out(s[i] - '0');
    return 0;
}