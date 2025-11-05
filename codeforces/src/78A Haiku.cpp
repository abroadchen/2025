//
// Created by Psy.C on 2025/11/5.
//

#include <iostream>
using namespace std;

bool check(char c) {
    return c == 'a' || c == 'e' || c == 'i' ||
        c == 'o' || c == 'u';
}

int main() {

    string s;
    int a, b, c;//存储每行的元音数
    for (int i = 1; i <= 3; ++i) {
        getline(cin, s);
        int len = s.size(), cnt = 0;
        for (int j = 0; j < len; ++j) if (check(s[j])) ++cnt;
        if (i == 1) a = cnt;//第1次循环(i==1)：将元音数存储在a中
        else if (i == 2) b = cnt;
        else c = cnt;
    }
    if (a == 5 && b == 7 && c == 5) puts("YES");
    else puts("NO");
    return 0;
}