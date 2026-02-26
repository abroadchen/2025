//
// Created by Psy.C on 2026/2/26.
//
/**
a[len]包括从1到len的所有调和值
a[len-i-1]移除在位置i之后开始的过长子串的贡献
a[i]移除在位置i之前结束的过长子串的贡献
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+1;

bool ok(const char c) {//是否为元音字母
    return c == 'I' || c == 'E' || c == 'A' ||
        c == 'O' || c == 'U' || c == 'Y';
}

string str;
double a[N];
int main() {
    fast;
    cin >> str;
    int len = str.length();
    double ans = 0., sum = 0.; a[0] = 0.;
    for (int i = 1; i <= len; ++i) {
        sum += 1./i;//1/1 + 1/2 + ... + 1/i
        a[i] = a[i-1] + sum;//前缀和
    }
    for (int i = 0; i < len; ++i)
        if (ok(str[i]))
            ans += a[len] - a[len-i-1] - a[i];//位置i的元音字母在所有可能子串中的贡献
    printf("%.9lf\n", ans);
    return 0;
}