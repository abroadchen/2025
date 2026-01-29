//
// Created by Psy.C on 2026/1/28.
//
/**
* ev：记录偶数长度连续字符组的数量，初始为 0
cnt：记录当前连续相同字符的计数，初始为 1（重要！）
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; getline(cin,s);
    int ev = 0, cnt = 1;
    for (int k = 1; k < s.size(); ++k) {
        if (s[k] == s[k-1]) ++cnt; else {
            if (cnt % 2 == 0) ++ev;//当前连续段长度为偶数，ev 加1
            cnt = 1;
        }
    }
    if (cnt % 2 == 0) ++ev;
    cout << ev << '\n';
    return 0;
}