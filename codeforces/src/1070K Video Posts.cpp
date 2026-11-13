//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
sum 是数组总和，sum/k 是每一段的目标和
用一个 s 累积当前段和，len 计数当前段元素个数；
一旦 s 撞到 sum/k，立即把这一段封口（记录长度、重置计数），继续下一段；
关键检查：如果已经切满 k 段（ans[0]==k）但还没到数组末尾（i != n），说明剩余还有元素却已用完段数 → 输出 No 直接结束。
最后：段数不足 k → No；恰好 k 段 → Yes + 各段长度。
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;
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

int n, k, a[N], sum, len, s, ans[N];
int main() {
    read(n); read(k);
    rep(i,n) read(a[i]), sum += a[i];
    rep(i,n) {
        len++; s += a[i];//累计当前这段的元素个数和总和
        if (s == sum/k) {//当前段和恰好等于目标
            //记录本段长度
            ans[++ans[0]] = len; len = s = 0;//重置，开新段
            //已经是第 k 段但数组还没走完 → 无解
            if (ans[0] == k && i != n) return cout << "No", 0;
        }
    }
    if (ans[0] < k) cout << "No";//切完数组后段数不足 k → 无解
    else {
        cout << "Yes\n";// 恰好切出 k 段 → 有解
        rep(i,ans[0]) write(ans[i]), putchar(' ');
    }
    return 0;
}