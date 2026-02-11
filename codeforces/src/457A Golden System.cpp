//
// Created by Psy.C on 2026/2/11.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200200
using namespace std;

void get(string& s) {
    //最低位变成最高位（便于从高位开始处理）
    reverse(s.begin(), s.end());
    s.resize(N, '0');//扩展到长度N，不足部分补'0'
    for (ll i = N-1; i > 0; --i)
        //遇到"11"就将其变为"00"，并在更高一位放置'1'
        while (i < N-1 && s[i] == '1' && s[i-1] == '1')
            s[i] = s[i-1] = '0', s[i+1] = '1', i++, i++;//跳过已处理的位置
    reverse(s.begin(), s.end());//恢复正常的高低位顺序
}


int main() {
    fast;
    string s1; cin >> s1; get(s1);
    string s2; cin >> s2; get(s2);
    if (s1 == s2) cout << '=';
    if (s1 > s2) cout << '>';
    if (s1 < s2) cout << '<';
    return 0;
}