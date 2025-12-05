//
// Created by Psy.C on 2025/12/4.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[] = {
    1, 5, 13, 25, 41, 61, 85, 113
}, b[] = {
    1, 3, 5, 7, 9, 11, 13, 15
};

int main() {
    fast;
    int x; cin >> x;
    int i = 0;
    if (x == 3) { cout << "5" << '\n'; return 0; }
    while (a[i] < x) i++;
    cout << b[i] << '\n';
    return 0;
}