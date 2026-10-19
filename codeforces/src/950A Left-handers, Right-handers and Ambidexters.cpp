//
// Created by Psy.C on 2026/10/18.
//
/**
输入 a, b, c（三个整数，k = c 的副本）。分三种情况
情况1：a < b
k = c - (b-a)，把 c 的一部分拿去补 a 和 b 的差
若补完还有剩，答案 = 2*(b + k/2)
若不够补，答案 = 2*(a+c)
情况2：b < a（对称）
情况3：a == b
注意：三个 if 之间没有 return/else if，但三种情况互斥（a<b、b<a、a==b），所以只有一个分支会执行，正好输出一次。逻辑上等同于多分支
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b, c, k;
int main() {
    fast;
    cin >> a >> b >> c; k = c;
    if (a < b) {
        k -= b - a;
        if (k >= 0) cout << 2*(b+k/2);
        else cout << 2*(a+c);
    }
    if (b < a) {
        k -= a - b;
        if (k >= 0) cout << 2*(a+k/2);
        else cout << 2*(b+c);
    }
    if (a == b) cout << 2*(a+c/2);
    return 0;
}