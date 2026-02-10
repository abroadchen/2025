//
// Created by Psy.C on 2026/2/10.
//
/**
第一行有n/2个*，0个D，n/2个*（当n为偶数时）
或者(n/2+1)个*，1个D，(n/2+1)个*（当n为奇数时）
中间行有n个D（当n为偶数时）或(n-1)个D（当n为奇数时）
形成对称的菱形图案

***D***
**DDD**
*DDDDD*
DDDDDDD
*DDDDD*
**DDD**
***D***
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
void out(const int i) {
    for (int j = 0; j < i; ++j) cout << '*';
    for (int j = 0; j < n-2*i; ++j) cout << 'D';
    for (int j = 0; j < i; ++j) cout << '*';
    cout << '\n';
}

int main() {
    fast;
    cin >> n;
    for (int i = n/2; i >= 0; --i) out(i);
    for (int i = 1; i <= n/2; ++i) out(i);
    return 0;
}