//
// Created by Psy.C on 2026/2/7.
//

#include <cstring>
#include <iostream>
int l[4];//每个字符串的长度（以字母A-D作为索引0-3）
char str[105];//输入的临时缓冲区

//字符串x是否是所有字符串中最长的
bool judgeLonger (int x) {
    for (int i = 0; i < 4; i++) {
        if (i == x)
            continue;
        //它的长度至少是其他每个字符串长度的两倍
        if (l[i] * 2 > l[x])
            return false;
    }
    return true;
}

bool judgeShorter(int x) {
    for (int i = 0; i < 4; i++) {
        if (i == x)
            continue;

        if (l[i] < l[x] * 2)
            return false;
    }
    return true;
}

int main () {
    for (int i = 0; i < 4; i++) {
        scanf("%s", str);
        //将字母(A/B/C/D)转换为索引(0/1/2/3)
        l[str[0]-'A'] = strlen(str+2);//忽略前2个字符("A=")
    }

    int cnt = 0, ans = 0;

    for (int i = 0; i < 4; i++) {
        if (judgeLonger(i) || judgeShorter(i)) {
            cnt++;
            ans = i;
        }
    }

    if (cnt == 1)
        printf("%c\n", ans + 'A');
    else
        printf("C\n");
    return 0;
}