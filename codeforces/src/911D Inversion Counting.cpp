//
// Created by Psy.C on 2026/10/12.
//
/**
用两层循环数所有 i < j 且 a[i] > a[j] 的对数 num，即逆序对总数
f = 1 表示当前逆序对是偶数，f = 0 表示奇数
每次查询读入区间 [l,r]，长度 len = r-l+1。
区间内部元素对数量 cnt = C(len,2) = len*(len-1)/2。
若 cnt 为奇数，那么翻转后逆序对奇偶性取反（f = !f）；若 cnt 为偶数，奇偶性不变。
输出当前 f 对应的 even / odd
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1510;

int n, m, a[N];
int main() {
    fast;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) cin >> a[i];
        int num = 0, f, l, r, len;
        for (int i = 1; i < n; ++i)
            for (int j = i+1; j <= n; ++j)
                if (a[i] > a[j]) num++;
        if (num%2 == 0) f = 1; else f = 0;
        cin >> m;
        while (m--) {
            cin >> l >> r; len = r-l+1;
            if ((len*(len-1)/2)%2 == 1) f = !f;
            if (f) cout << "even\n"; else cout << "odd\n";
        }
    }
    return 0;
}