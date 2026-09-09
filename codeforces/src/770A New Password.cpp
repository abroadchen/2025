//
// Created by Psy.C on 2026/9/8.
//
/**
'a'+n%k 得到 'a' 加上 n mod k 的偏移量。当 n%k 取 0,1,...,k-1 时，得到的字符是 'a','b',...,'a'+(k-1)。
由于取模 %k，所以输出只在前 k 个小写字母（'a' 到 'a'+(k-1)）之间循环。
注意循环内 n 是递减的，所以 n%k 每次取到的是递减序列对 k 取模
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    while (n--) cout << (char)('a'+n%k);
    cout << '\n';
    return 0;
}