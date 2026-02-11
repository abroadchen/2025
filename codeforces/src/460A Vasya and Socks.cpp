//
// Created by Psy.C on 2026/2/11.
//
/**
第一次循环：计算[1,n]中m的倍数个数 → b = floor(n/m)
第二次循环：从n+1开始，找到足够的非m倍数
每次消耗一个"配额"
遇到m的倍数时，不消耗配额，反而增加结果

需要找到一个数X，使得在[1,X]范围内，不是m的倍数的数恰好有n个
t记录的是[1,X]范围内m的倍数的个数
t + n就是X的值

最坏情况：O(n)，当m很大时需要循环很多次
平均情况：O(n/m)，取决于m的大小
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, t;
int main() {
    fast;
    cin >> n >> m;
    int b = 0;
    for (int i = 1; i*m <= n; ++i) b++;//b = floor(n/m)，n以内m的倍数个数
    t = b;
    for (int i = n+1; b; ++i) {
        b--;
        if (i%m==0) {
            b++;
            t++;//增加结果
        }
    }
    cout << t + n << '\n';
    return 0;
}