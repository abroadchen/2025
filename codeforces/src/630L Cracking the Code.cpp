//
// Created by Psy.C on 2026/3/29.
//
/**
n = 第2位 + 第4位*10 + 第5位*100 + 第3位*1000 + 第1位*10000
ans = n⁵ % 100000
输出至少5位数，不足的前面补0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

char s[6];
ll ans = 1, n;
int main() {
    fast;
    scanf("%s", s);
    n = s[1] - '0' + (s[3] - '0')*10 + (s[4] - '0')*100 + (s[2] - '0')*1000 + (s[0] - '0')*10000;
    for (int i = 0; i < 5; ++i) ans = ans*n%100000;
    printf("%05lld\n", ans);
    return 0;
}