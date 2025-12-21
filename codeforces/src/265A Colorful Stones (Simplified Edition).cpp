//
// Created by Psy.C on 2025/12/21.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s, t; cin>>s>>t;
    int p = 0;//匹配的字符数量
    for (int i = 0; i < t.length(); ++i) {
        if (t[i] == s[p]) p++;//字符串s中位置p的字符
    }
    cout << p + 1 << '\n';
    return 0;
}