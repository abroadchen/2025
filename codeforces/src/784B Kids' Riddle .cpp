//
// Created by Psy.C on 2026/9/13.
//
/**
a[]：用来临时存 n 的十六进制每一位数字。
k[]：长 16 的表，下标 0-15 对应十六进制数字 0-F 的"权值"。每次取一个十六进制数字 d，就加 k[d]
反复对 16 取模、除以 16，把 n 转成十六进制表示，从低位到高位依次存进 a[0..x-1]
对每一位十六进制数字查 k 表求和，输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+1;
int a[N], k[] = {
    1,0,0,0,1,0,1,0,2,1,1,2,0,1,0,0
};
int main() {
    fast;
    int n, x = 0, ans = 0; cin >> n;
    if (n == 0) { cout << 1; return 0; }
    while (n > 0) {//取最低一位十六进制数字 去掉这一位
        a[x] = n % 16; n /= 16; x++;
    }
    for (int i = 0; i < x; ++i) ans += k[a[i]];
    cout << ans;
    return 0;
}