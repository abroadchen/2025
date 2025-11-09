//
// Created by Psy.C on 2025/9/13.
//

#include <ios>
#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b > 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int y, w; cin >> y >> w;
    int max_yw = max(y, w);
    int favorable = 6 - max_yw + 1;
    int total = 6;

    int g = gcd(favorable, total);
    cout << favorable / g << "/" << total / g << endl;
    return 0;
}