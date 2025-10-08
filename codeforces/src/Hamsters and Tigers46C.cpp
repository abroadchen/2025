//
// Created by Psy.C on 2025/9/30.
//

#include <cstdio>
#include <iostream>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long n; cin >> n;
    string s; cin >> s;

    long m(0);
    for (int i = 0; i < n; ++i) m += (s[i] == 'H');
    long cnt(n + 1);
    for (int i = 0; i < n; ++i) {
        long tot(0);
        for (int j = 0; j < m; ++j) {//检查从位置i开始的连续m个字符
            tot += (s[(i + j) % n] == 'T');//实现环形访问，当索引超出n-1时会回到字符串开头
        }
        cnt = (cnt < tot) ? cnt : tot;//更新cnt为当前最小值
    }
    printf("%ld\n", cnt);
    return 0;
}