//
// Created by Psy.C on 2026/3/2.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, h[26];///小写字母出现次数
string s;
int main() {
    fast;
    cin >> n >> s;
    int ans = 0;
    for (const char i : s) {
        if (islower(i)) h[i-'a']++;
        else {
            if (h[i-'A']) h[i-'A']--;//消耗一个小写字母
            else ans++;//无法匹配的大写字母计数
        }
    }
    cout << ans << '\n';
    return 0;
}