//
// Created by Psy.C on 2026/2/9.
//

#ifndef CODEFORCES_RD_H
#define CODEFORCES_RD_H

inline char gc() {
    static char now[1<<16], *s, *t;
    if (t == s) {
        t = (s = now) + fread(now, 1, 1<<16, stdin);
        if (t == s) return EOF;
    }
    return *s++;
}

inline int read() {
    int x = 0, f = 1;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = gc();
    }
    while (ch <= '9' && ch >= '0') {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return x * f;
}


#endif //CODEFORCES_RD_H