//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

char a, b, c;
int main() {
    fast;
    cin >> a >> b;
    for (int i = 0; i < 5; i++) {
        cin >> c;
        if (c == a) { cout << "YES"; return 0; }
        cin >> c;
        if (c == b) { cout << "YES"; return 0; }
    }
    cout << "NO"; 
    return 0;
}