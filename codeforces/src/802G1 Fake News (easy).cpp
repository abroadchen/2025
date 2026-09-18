//
// Created by Psy.C on 2026/9/18.
//
///k表示c数组的指针
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char c[] = {'h', 'e', 'i', 'd', 'i'};
string s;
int main() {
    fast;
    cin >> s;
    int k = 0, sum = 0;
    for (int i = 0; i < s.length(); ++i)
        if (s[i] == c[k]) { sum++; k++; }//总量加1 指针往后挪一位
    //总量为heidi的长度，说明存在
    if (sum == 5) cout << "YES\n"; else cout << "NO\n";
    return 0;
}