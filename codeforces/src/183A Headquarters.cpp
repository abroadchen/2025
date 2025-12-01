//
// Created by Psy.C on 2025/12/1.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    string s; ll a = 1, b = 1;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        if (s == "UL" || s == "DR") a++;
        else if (s == "UR" || s == "DL") b++;
        else a++, b++;//同时影响两个维度
    }
    cout << a * b << '\n';//两个方向可能性的乘积
    return 0;
}