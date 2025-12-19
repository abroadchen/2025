//
// Created by Psy.C on 2025/12/19.
//

#include <iostream>
#include <string>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    const int c = static_cast<int>(s.find('0'));//第一个'0'字符的位置
    if (c == -1) cout << s.substr(1) << '\n';//第二个字符开始的子串
    else cout << s.substr(0, c) << s.substr(c + 1) << '\n';//'0'之前的部分 '0'之后的部分
    return 0;
}