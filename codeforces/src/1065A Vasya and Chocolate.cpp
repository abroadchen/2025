//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
先用原价买，能买 s/c 块。
每买 a 块就送 b 块，送的这部分又能凑成"满 a 赠 b"继续循环？
实际该公式的做法是：(s/c)/a * b 表示"最初买的 s/c 块中，每 a 块换得 b 块赠品"。
总块数 = 原价买的 + 送的 = s/c + (s/c)/a * b
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int T;
ll s, a, b, c;
int main() {
    fast;
    cin >> T;
    while (T--) {
        cin >> s >> a >> b >> c;
        cout << s/c+s/c/a*b << '\n';
    }
    return 0;
}