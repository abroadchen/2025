//
// Created by Psy.C on 2025/12/20.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    const int len = static_cast<int>(s.length());
    vector<int> a(len + 1);//使用1-indexed
    int l = 1, r = len;
    for (int i = 0; i < len; ++i) {//字符串是0-indexed
        if (s[i] == 'l') a[r--] = i + 1;//转换为1-indexed
        else a[l++] = i + 1;
    }
    for (int i = 1; i <= len; ++i) cout << a[i] << '\n';
    return 0;
}