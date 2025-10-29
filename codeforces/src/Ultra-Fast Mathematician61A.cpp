//
// Created by Psy.C on 2025/10/28.
//

#include <ios>
#include <iostream>
#include <string>
using namespace std;

string s1, s2;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);
    getline(cin, s1); getline(cin, s2);
    for (int i = 0; i < s1.size(); ++i) {
        cout << ((s1[i] - '0') ^ (s2[i] - '0'));//将字符转换为对应的数字值
    }
    cout << endl;
    return 0;
}