//
// Created by Psy.C on 2025/11/21.
//

#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string a, b; cin >> a >> b;
    int p(0), q(0);
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == '4' && b[i] == '7') ++p;
        else if (a[i] == '7' && b[i] == '4') ++q;
    }
    printf("%d\n", p > q ? p : q);
}