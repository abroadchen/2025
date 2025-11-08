//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, x0; cin >> n >> x0;
    int left_bound = 0, right_bound = 1000;

    for (int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        int left = min(a, b);
        int right = max(a, b);

        left_bound = max(left, left_bound);
        right_bound = min(right, right_bound);
    }

    if (left_bound > right_bound) cout << "-1\n";
    else {
        if (x0 >= left_bound && x0 <= right_bound) cout << "0\n";
        else if (x0 < left_bound) cout << (left_bound - x0) << "\n";
        else cout << (x0 - right_bound) << "\n";
    }
    
    return 0;
}