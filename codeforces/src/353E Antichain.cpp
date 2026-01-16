//
// Created by Psy.C on 2026/1/16.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    const int n = static_cast<int>(s.size());
    int ans = 0;
    //当前字符与下一个字符是否不同（%n实现环形访问）
    for (int i = 0; i < n; ++i) if (s[i] != s[(i+1)%n]) {
        if (s[i] != s[(i+2)%n]) ans++;//当前字符与隔一个位置的字符是否不同
        else if (s[i] != s[(i+3)%n]) ans++, i++;//当前字符与隔两个位置的字符是否不同
        //i增加1（跳过下一个位置）
    }
    cout << ans << '\n';
    return 0;
}