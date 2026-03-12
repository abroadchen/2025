//
// Created by Psy.C on 2026/3/12.
//
/**
将输入的数字x反转得到y
y = y*10 + x%10每次取出x的最后一位加到y的末尾
x /= 10去掉x的最后一位
如果反转后的数y等于原数t，则是回文数，返回true

p,q: 输入的比例参数
s1,s2: 累计计数器，s1统计素数个数，s2统计回文数个数
非合数个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e6;

bool pri[N+5];
void get() {
    for (int i = 2; i <= N; ++i) {
        if (pri[i] == 0) continue;
        for (int j = 2; i*j <= N; ++j)
            pri[i*j] = 0;
    }
}

bool get(int x) {
    int y = 0, t = x;
    while (x != 0) {
        y = y*10 + x%10;
        x /= 10;
    }
    if (y == t) return true;
    return false;
}

double p, q, s1, s2;
int ans;
int main() {
    fast;
    cin >> p >> q;
    for (int i = 2; i <= N; ++i) pri[i] = 1; get();
    for (int i = 1; i <= N; ++i) {
        s1 += pri[i]; s2 += get(i);
        if (s1 <= s2*p/q) ans = i;
    }
    cout << ans << '\n';
    return 0;
}