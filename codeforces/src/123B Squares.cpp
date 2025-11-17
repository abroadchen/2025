//
// Created by Psy.C on 2025/11/17.
//
/*
 *⌈x/y⌉（x除以y向上取整）
 *(x + y - 1) / y
 *(x + C * y) / y  其中C是一个足够大的常数
 */
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const ll N = 1e9+100;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n, m, a, b, c, d, t = N;
    cin>>n>>m>>a>>b>>c>>d; n *= 2; m *= 2;
    cout << max(abs((a + b + t * n) / n - (c + d + t * n) / n),
        abs((a - b + t * m) / m - (c - d + t * m) / m));
    return 0;
}