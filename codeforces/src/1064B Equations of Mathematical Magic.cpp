//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
通过不断右移并检查最低位，逐位统计二进制表示中 1 的数量。
例如 a = 5（101₂），循环三次得 cnt = 2
读入测试次数 t。
每次循环读入 a。
用 calc(a) 求出 a 中 1 的个数 x。
用 pow(2.0, x) 计算 2^x，转成 int 输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int calc(int x) {
    int cnt = 0;
    while (x) {
        if (x&1) cnt++;
        x >>= 1;
    }
    return cnt;
}

int t, a;
int main() {
    fast;
    cin >> t;
    while (t--) {
        cin >> a;
        int x = calc(a);
        cout << (int)pow(2.0, x) << '\n';
    }
    return 0;
}