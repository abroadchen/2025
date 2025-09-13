//
// Created by Psy.C on 2025/9/12.
//


#include <map>
#include <cstring>
#include <string>
#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

string s2, s3;
map<string, int> mp;

int judge(string s, int l, int r) {
    int add = 0, x, y, f = 0;
    string ss;
    for (int i = r; i >= l; i--) {
        if (s[i] == '(') add++;
        else if (s[i] == ')') add--;
        else if (add == 0 && f == 0 && (s[i] == '*' || s[i] == '/')) f = i;
        else if (add == 0 && (s[i] == '+' || s[i] == '-')) {
            x = judge(s, l, i - 1);
            y = judge(s, i + 1, r);
            if (x == 2 || y == 2) return 2;
            if (s[i] == '+') return 3;
            else if (s[i] == '-') {
                if (y == 3) return 2;
                else return 3;
            }
        }
    }
    if (f != 0) {
        x = judge(s, l, f - 1);
        y = judge(s, f + 1, r);
        if (x == 2 || y == 2) return 2;
        if (s[f] == '*') {
            if (x == 3 || y == 3) return 2;
            else return 4;
        }
        else if (s[f] == '/') {
            if (x == 3 || y == 3 || y == 4) return 2;
            else return 4;
        }
    }
    else if (s[l] == '(' && s[r] == ')') {
        if (judge(s, l + 1, r - 1) == 2) return 2;
        else return 1;
    }
    else {
        ss = "";
        for (int i = l; i <= r; i++) ss += s[i];
        if (mp[ss] != 0) return mp[ss];
        else return 1;
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s[s.length()-1] == '#') cin >> s;
        cin >> s;
        getline(cin, s2);
        s3 = "";
        for (int j = 0; j < s2.length(); j++) {
            if (s2[j] != ' ') s3 += s2[j];
        }
        mp[s] = judge(s3, 0, s3.length() - 1);
    }
    getline(cin, s2);
    s3 = "";
    for (int j = 0; j < s2.length(); j++) {
        if (s2[j] != ' ') s3 += s2[j];
    }
    if (judge(s3, 0, s3.length() - 1) != 2) cout << "OK" << endl;
    else cout << "Suspicious" << endl;

    return 0;
}