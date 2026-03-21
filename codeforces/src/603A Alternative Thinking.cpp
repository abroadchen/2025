//
// Created by Psy.C on 2026/3/21.
//

#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5+5;
int n, a, b;
char s[N];
int main() {
    scanf("%d%s", &n, s+1);
    if (s[n] == '0') s[n+1] = 1; else s[n+1] = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == s[i+1]) a++;
        else b++;
    }
    printf("%d\n", b + min(2, a));
    return 0;
}