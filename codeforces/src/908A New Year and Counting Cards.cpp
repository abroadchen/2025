//
// Created by Psy.C on 2026/10/11.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
using namespace std;

string s;
int ans;
int main() {
    fast;
    cin >> s;
    rep(i,0,s.size()-1) {
        if (s[i]-'0' >= 0 && s[i]-'0' <= 9) {
            if ((s[i]-'0')%2) ans++;
            continue;
        }
        if (s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u') ans++;
    }
    cout << ans << '\n';
    return 0;
}