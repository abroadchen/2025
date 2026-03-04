//
// Created by Psy.C on 2026/3/3.
//
///满足任一条件时Polycarp获胜，否则Vasiliy获胜
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c, d;
int main() {
    fast;
    cin >> a >> b >> c >> d;
    cout << (d >= a+b || c >= a+b || (c >= a && d >= b) ?
        "Polycarp" : "Vasiliy");
    return 0;
}