//
// Created by Psy.C on 2026/4/13.
//
/**
将字符映射到数字（Base64编码风格）：
'0'-'9' → 0-9
'A'-'Z' → 10-35
'a'-'z' → 36-61
'-' → 62
'_' → 63
统计的是6位二进制表示中0的个数，因为：
当x%2 == 0时（即当前位为0），num++
当x%2 == 1时（即当前位为1），不增加
计算 3^y mod mod

check(i): 将字符转换为对应的数字
get(x): 计算该数字的6位二进制表示中0的个数
累加到sum
计算 3^sum mod (10^9+7)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, mod = 1e9+7;

char s[N];
int check(int x) {
    if (s[x] >= '0' && s[x] <= '9') return s[x] - '0';
    if (s[x] >= 'a' && s[x] <= 'z') return s[x] - 'a' + 36;
    if (s[x] >= 'A' && s[x] <= 'Z') return s[x] - 'A' + 10;
    if (s[x] == '-') return 62;
    if (s[x] == '_') return 63;
}

int get(int x) {
    int num = 0, cnt = 6;
    while (cnt--) {
        if (x%2 == 0) num++;
        x >>= 1;
    }
    return num;
}

ll ksm(int y) {
    ll ans = 1, base = 3;
    while (y) {
        if (y&1) { ans *= base; ans %= mod; }
        base *= base; base %= mod;
        y >>= 1;
    }
    return ans;
}

int main() {
    fast;
    cin >> s; int len = strlen(s), sum = 0;
    for (int i = 0; i < len; ++i) {
        int x = check(i);
        sum += get(x);
    }
    cout << ksm(sum) << '\n';
    return 0;
}