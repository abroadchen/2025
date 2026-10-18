//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
using namespace std;


int main() {
    char c;
    int n1 = 0, n2 = 0;
    char op = ' '; c = getchar();
    while (c != '\n' && c != EOF) {
        if (c >= '0' && c <= '9' && op == ' ') n1 = n1*10+c-'0';
        else if (c >= '0' && c <= '9') n2 = n2*10+c-'0';
        if (c == '+' && op == '+') { n1 = n1 + n2; n2 = -5; }
        else if (c == '+' && op == '-') { n1 = n1 - n2; n2 = -5; op = '+'; }
        else if (c == '+') { n2 = -5; op = '+'; }
        else if (c == '-' && op == '+') { n1 = n1 + n2; n2 = -3; op = '-'; }
        else if (c == '-' && op == '-') { n1 = n1 - n2; n2 = -3; }
        else if (c == '-') { n2 = -3; op = '-'; }
        c = getchar();
    }
    if (op == '-') n1 -= n2; else n1 += n2;
    printf("%d\n", n1);
    return 0;
}