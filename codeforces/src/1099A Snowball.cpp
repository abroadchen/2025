//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
w 是某种生命值或收集量；
h 从高逐层下降，每层 w += h（高度贡献）；
v[h] 记录在高度 h 处遇到的障碍/惩罚值，若该高度有记录则扣除。
读 w、h。
读两组 (u[i], a[i])，把 "高度 a[i] 处放 u[i]" 记录进 v。i 只到 2，说明题目固定有 2 个这样的特殊高度
从高度 h 一路降到 1。
每一层：先 w += h（本层高度带来的收益/加成）。
再 w -= v[h]，但用 max(0,...) 保证不小于 0（若该高度有障碍扣值，则扣除，且不扣成负数）。
结束后输出最终 w
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 107;
template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int w, h, u[3], a[3], v[N];
int main() {
    read(w), read(h);
    for (int i = 1; i <= 2; i++) {
        read(u[i]), read(a[i]);
        v[a[i]] = u[i];//"高度→惩罚/物体值"的映射表
    }
    while (h) {
        w += h, w = max(0,w-v[h]);
        h--;
    }
    write(w);
    return 0;
}