//
// Created by Psy.C on 2025/12/7.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b, c; cin>>a>>b>>c;
    cout << a * b + b * c + c * a - a - b - c + 1 << '\n';
    return 0;
}