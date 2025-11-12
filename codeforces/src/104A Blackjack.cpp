//
// Created by Psy.C on 2025/11/12.
//

#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    if (n <= 10 || n > 21) cout << 0 << '\n';
    else if (n == 20) cout << 15 << '\n';
    else cout << 4 << '\n';
    return 0;
}