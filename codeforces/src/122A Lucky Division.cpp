//
// Created by Psy.C on 2025/11/17.
//

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    vector<int> v = {4, 7, 44, 47, 74, 77, 444, 447, 474, 477, 744, 774, 777};
    for (int i : v) { if (n % i == 0) { cout << "YES" << '\n'; return 0; } }
    cout << "NO" << '\n';
    return 0;
}