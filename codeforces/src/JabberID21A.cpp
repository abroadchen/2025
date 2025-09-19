//
// Created by Psy.C on 2025/9/18.
//
/*
 *当字符串查找函数没有找到目标时，会返回 string::npos
 *
 */
#include <ios>
#include <iostream>
#include <cstdio>
using namespace std;

bool isTrue(string s) {
    string tmp = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890_";

    for (int i = 0; i < s.length(); ++i) {
        if (tmp.find(s[i]) == string::npos) return false;
    }
    return true;
}

bool doubleDot(string s) {
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '.' && s[i + 1] == '.') return false;
    }
    return true;
}

bool isTrueH(string s) {
    string tmp = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890_.";

    for (int i = 0; i < s.length(); ++i) {
        if (tmp.find(s[i]) == string::npos) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    string s, username, hostname, resource, tmp;
    getline(cin, s);

    username = s.substr(0, s.find('@'));
    if (username.length() > 16 || !isTrue(username) || username.empty()) {
        cout << "NO" << endl;
        return 0;
    }

    hostname = s.substr(s.find('@') + 1, s.find('/') - s.find('@') - 1);
    if (hostname.length() > 32 || !doubleDot(hostname) || !isTrueH(hostname) ||
        hostname.empty() || hostname[0] == '.') {
        cout << "NO" << endl;
        return 0;
    }
    while (hostname.length() > 0) {
        tmp = hostname.substr(0, hostname.find('.'));
        if (hostname.find('.') == string::npos) hostname.clear();
        else {
            hostname.erase(0, hostname.find('.'));
            if (hostname == ".") {
                cout << "NO" << endl;
                return 0;
            }
            hostname.erase(0, 1);
        }
        if (tmp.length() > 16) {
            cout << "NO" << endl;
            return 0;
        }
    }

    if (s.find('/') != string::npos) {
        resource = s.substr(s.find('/') + 1);

        if (resource.length() > 16 || !isTrue(resource) || resource.empty()) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    return 0;
}