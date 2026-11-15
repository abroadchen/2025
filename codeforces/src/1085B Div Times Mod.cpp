//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
当 n%b==0 成立时，a = n/b，此时 a*b = (n/b)*b = n 恒成立，所以第二个 if 一定也成立，立即输出并 break。
也就是说：只要找到第一个能整除的 b（从大到小找，即最大的、≤k-1 且整除 n 的 b），就直接输出并退出。
那第二个 if (a*b==n) 的意义是什么？只有在 n%b != 0 但 a 是上一轮赋值的结果时，才可能二次触发
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, k, b, a, x;
int main() {
    fast;
    cin >> n >> k;
    for (b = k-1; b > 0; b--) {
        if (n%b == 0) { a = n/b; x = a*k+b; }
        if (a*b == n) { cout << x; break; }
    }
    return 0;
}