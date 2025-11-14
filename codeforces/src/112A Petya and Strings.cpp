//
// Created by Psy.C on 2025/11/14.
//

#include <iostream>
#include <cctype>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s1; getline(cin,s1);
    string s2; getline(cin,s2);
    int c = 0;
    for (int i = 0; i < s1.size(); ++i) {
        if (tolower(s1[i]) < tolower(s2[i])) { c = -1; break; }
        if (tolower(s1[i]) > tolower(s2[i])) { c = 1; break; }
    }
    printf("%d\n",c);
    return 0;
}