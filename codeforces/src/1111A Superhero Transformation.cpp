//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
读入两个字符串 a、b。
若长度不同，直接输出 NO 结束。
逐位比较：
f1 = a[i] 是否元音，f2 = b[i] 是否元音。
若 f1 == f2（同为元音或同为辅音）→ 继续下一位。
否则（一个是元音、一个是辅音）→ 输出 NO 结束。
所有位都通过 → 输出 YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

char s[] = {'a','e','i','o','u'};
bool check(char k) {
    for (char i : s) if (k == i) return 1;
    return 0;
}

string a, b;
bool f1, f2;
int main() {
    fast;
    cin >> a >> b;
    int l1 = a.length(), l2 = b.length();
    if (l1 != l2) { cout << "NO\n"; return 0; }
    rep(i, l1) {
        f1 = check(a[i]); f2 = check(b[i]);
        if (f1 == f2) continue;
        cout << "NO\n"; return 0;
    }
    cout << "YES\n";
    return 0;
}