//
// Created by Psy.C on 2025/11/16.
//

#include <cstdio>
using namespace std;

char y[] = "aoyeui";
int flag;

int main() {
    while (1) {
        char ch = getchar();
        if (ch == '\n') break;
        if (ch >= 'A' && ch <= 'Z') ch = ch - 'A' + 'a';//转换为小写字母
        for (int i = 0; i < 6; ++i) if (ch == y[i]) flag = 1;
        if (!flag) printf(".%c", ch);
        flag = 0;
    }
    printf("\n");
    return 0;
}