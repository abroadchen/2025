//
// Created by Psy.C on 2025/12/21.
//
/*
*n：字符串长度
t：变换次数
s：待处理的字符串
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, t; string s; cin >> n >> t >> s;
    while (t--) {
        for (int i = 1; i < n; ++i) if (s[i] == 'G' && s[i-1] == 'B') {
            s[i] = 'B'; s[i-1] = 'G'; ++i;//跳过下一个位置
        }
    }
    cout << s << '\n';
    return 0;
}