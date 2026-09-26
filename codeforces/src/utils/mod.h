//
// Created by Psy.C on 2026/9/26.
//

#ifndef CODEFORCES_MOD_H
#define CODEFORCES_MOD_H

inline int add(const int& x, const int& y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
inline int sub(const int& x, const int& y) { return (x - y < 0) ? (x - y + mod) : (x - y); }
inline int mul(const int& x, const int& y) { return 1ll*x*y%mod; }

int ksm(int x, int y) {
    int ret = 1;
    while (y) {
        if (y&1) ret = mul(ret, x);
        x = mul(x, x);
        y >>= 1;
    }
    return ret;
}



#endif //CODEFORCES_MOD_H
