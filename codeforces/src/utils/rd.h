//
// Created by Psy.C on 2026/2/9.
//

#ifndef CODEFORCES_RD_H
#define CODEFORCES_RD_H
#include "../bits/stdc++.h"
inline char gc() {
    static char now[1<<16], *s, *t;
    if (t == s) {
        t = (s = now) + fread(now, 1, 1<<16, stdin);
        if (t == s) return EOF;
    }
    return *s++;
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


#endif //CODEFORCES_RD_H