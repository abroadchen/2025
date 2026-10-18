//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 2e5+10;

int len;
map<int, int> mp;
char s[N];
vector<int> v;
bool check() {
    per(i,len-1,0) {
        int t;
        if (i == 0) t = 1; else t = 0;
        --mp[s[i]-'0'];
        per(j,s[i]-'0'-1,t) {
            ++mp[j]; v.clear();
            rep(k,10) if (mp[k]&1) v.push_back(k);
            int l = v.size();
            if (l <= len-i-1) {
                rep(k,i) cout << s[k];
                cout << j;
                rep(k,len-i-1-l) cout << "9";
                ranges::sort(v);
                per(k,l-1,0) cout << v[k];
                cout << '\n';
                return true;
            }
            --mp[j];
        }
    }
    return false;
}


int main() {
    fast;
    int t; cin >> t;
    while(t--) {
        mp.clear(); cin >> s; len = strlen(s);
        rep(i,len) ++mp[s[i]-'0'];
        if (!check()) {
            rep(i,len-2) cout << "9";
            cout << '\n';
        }
    }
    return 0;
}