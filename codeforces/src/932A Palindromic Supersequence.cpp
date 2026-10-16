//
// Created by Psy.C on 2026/10/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
using namespace std;

string s;
int main() {
    fast;
    cin >> s; cout << s;
    per(i,s.size()-1,0) cout << s[i];
    return 0;
}