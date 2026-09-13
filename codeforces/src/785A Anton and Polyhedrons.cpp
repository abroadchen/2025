//
// Created by Psy.C on 2026/9/13.
//
/**
Tetrahedron（正四面体）‍：4 个面
Cube（正方体）‍：6 个面
Octahedron（正八面体）‍：8 个面
Dodecahedron（正十二面体）‍：12 个面
Icosahedron（正二十面体）‍：20 个面
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; string str;
    while (cin >> n) {
        int s = 0;
        while (n--) {
            cin >> str;
            if (str == "Tetrahedron") s += 4;
            else if (str == "Cube") s += 6;
            else if (str == "Octahedron") s += 8;
            else if (str == "Dodecahedron") s += 12;
            else if (str == "Icosahedron") s += 20;
        }
        cout << s << '\n';
    }
    return 0;
}