//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
有 n 个某种学生/物品，其中

2/10 的部分（占比 2）
5/10 的部分（占比 5）
8/10 的部分（占比 8）
每个"部门"都要分成若干组/班，每份最多容纳 k 个，问总共至少需要多少"份"。

答案公式：

ans = ceil(n*2/k) + ceil(n*5/k) + ceil(n*8/k)
即分别把 2n、5n、8n 分成每组最多 k 的数量，各自上取整再相加。

这是一道经典题——通常是"学生分到 2 人间 /5 人间 /8 人间（或按某比例分科室），每间最多 k 人，问最少几间房"。2+5+8 的比例可对应不同的分类。
*/
#include <bits/stdc++.h>
using namespace std;

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

int n, k;
int main() {
    read(n); read(k);
    int ans = ceil(n*2.0/k) + ceil(n*5.0/k) + ceil(n*8.0/k);
    write(ans);
    return 0;
}