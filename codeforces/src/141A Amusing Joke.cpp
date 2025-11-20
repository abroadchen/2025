//
// Created by Psy.C on 2025/11/20.
//
/*
 *判断前两个字符串合并后的字符组成是否与第三个字符串相同
 *继续累加到s1数组中，即将两个字符串的字符统计合并
 */
#include <iostream>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

const int N = 26;
char s1[N], s2[N];

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    getline(cin, s); rep(i,s.size()) s1[s[i] - 'A']++;
    getline(cin, s); rep(i,s.size()) s1[s[i] - 'A']++;
    getline(cin, s); rep(i,s.size()) s2[s[i] - 'A']++;
    string ans = "YES";
    rep(i,N) if (s1[i] != s2[i]) { ans = "NO"; break; }
    cout << ans << '\n';
    return 0;
}