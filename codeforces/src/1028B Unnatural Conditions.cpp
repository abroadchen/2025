//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
444...444                (300 个 '4')
555...556                (299 个 '5' + 1 个 '6')
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); i++)
using namespace std;

constexpr int N = 3e2;

int main() {
    fast;
    rep(i,N) putchar('4');
    putchar('\n');
    rep(i,N-1) putchar('5');
    putchar('6');
    putchar('\n');
    return 0;
}