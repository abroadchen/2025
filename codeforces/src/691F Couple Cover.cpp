//
// Created by Psy.C on 2026/4/16.
//
///时间复杂度约为O(n²)预处理 + O(m)查询
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 3e6+5;
///a存储原始数组，b存储去重后的数组
///n是数组长度，num[i]记录第i个不同元素出现次数，sum[i]记录乘积≤i的对数
int a[N], b[N];
ll n, num[N], sum[N];
void get() {
    sort(a + 1, a + n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == a[i-1]) num[cnt]++;
        else {
            ++cnt;
            b[cnt] = a[i];//存储不同的元素值
            num[cnt] = 1;//存储对应元素的出现次数
        }
    }
    for (int i = 1; i <= cnt; ++i)
        for (int j = 1; j <= i; ++j) {
            if ((ll)b[i]*b[j] >= N-5) break;
            //相同元素，计算C(num[i],2)的组合数
            if (i == j) sum[b[i]*b[j]] += num[i]*(num[i]-1);
            else sum[b[i]*b[j]] += 2*num[i]*num[j];
        }
    //sum[i]现在表示乘积≤i的元素对总数
    for (int i = 1; i <= N-5; ++i) sum[i] += sum[i-1];
}

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
    putchar('\n');
}

int m;
int main() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]); get();
    read(m);
    for (int i = 1, p; i <= m; ++i) {
        read(p);
        write((ll)n*(n-1)-sum[p-1]);//总对数减去乘积<p的对数，即乘积≥p的对数
    }
    return 0;
}