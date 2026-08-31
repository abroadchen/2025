//
// Created by Psy.C on 2026/8/31.
//
/**
读入一个整数 n （需要被拆分的正整数）
1 + 2 + 3 + ... + k = k*(k+1)/2 是 k 个互不相同的正整数的最小可能之和 。
我们要找到 最大的整数 k 使得 k*(k+1)/2 ≤ n 。这是一个一元二次不等式
k = (√(8n + 1) - 1) / 2
  = √(2n + 0.25) - 0.5
       ↑ 因为 8n+1 = 4*(2n+0.25)，开根号就是 2√(2n+0.25)
       再除以 2 就变成 √(2n+0.25)
- double k = sqrt(2.*n+0.25)-0.5 ：用 double 做浮点运算，计算求根公式。
- int kk = static_cast<int>(k) ：向下取整，得到最大的整数 kk 使得 kk*(kk+1)/2 ≤ n
输出拆分后的整数个数 kk
- 前 kk-1 个数 ：直接是 1, 2, 3, ..., kk-1 （这是 kk-1 个互不相同的正整数，它们的和是 (kk-1)*kk/2 ）。
- 最后一个数 ： n - (kk-1)*kk/2 ，凑够总和 n 。 为什么这样一定合法？
- 前 kk-1 个数互不相同，且都 ≤ kk-1 。
- 最后一个数 = n - (kk-1)*kk/2 ，我们需要证明它 > kk-1 （这样所有数都互不相同）：
  - 由 kk*(kk+1)/2 ≤ n < (kk+1)*(kk+2)/2 （kk 是最大的满足条件的整数）
  - n - (kk-1)*kk/2 > (kk*(kk+1)/2) - (kk-1)*kk/2 = kk > kk-1 ✓
  - 所以最后一个数 一定比前面所有数都大 ，保证互不相同
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    double k = sqrt(2.*n+0.25)-0.5;
    int kk = static_cast<int>(k);
    cout << kk << endl;
    for (int i = 1; i <= kk-1; ++i) cout << i << ' ';
    cout << n-(kk-1)*kk/2 << endl;
    return 0;
}