//
// Created by Psy.C on 2026/10/5.
//
/**
第一行两个数 n、m。
接下来是 n 行，每行 m 个数（每行对应 i 的一个元素）。每行的 m 个数被拼成一个二进制掩码
a[i] 存第 i 行构成的整数
对每行 i：读入 m 个数，把第 j 个数乘以
2
j
−
1
2
j−1
  累加到 a[i]。也就是说，a[i] 的二进制第 j-1（从 0 开始）位表示该行第 j 个数是否为 1。每行被压缩成一个 m 位的二进制整数（掩码）‍
unique 去重：排序后去掉重复的掩码，n 更新为去重后的元素个数。（重复掩码不影响结果，因为判断条件只关心"是否存在"。
如果最小的掩码是 0（即存在一行全是 0），直接输出 YES 并结束。注意：只有 a[1]==0 才可能（排序后 0 在第一位）。如果某行为 0，与谁做按位与都是 0，立即满足条件
双重循环：遍历所有不同的掩码对 (a[i], a[j])，检查是否存在一对掩码满足按位与为 0（!(a[i]&a[j])）。一旦找到就置 flag 并跳出，输出 YES；整个循环结束都没找到则输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+10;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N];
int main() {
    fast;
    int n = rd(), m = rd();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i] += rd()*(1<<(j-1));
    sort(a+1, a+n+1);
    n = unique(a+1, a+1+n) - a - 1;
    if (!a[1]) { cout << "YES\n"; return 0; }
    bool flag = false;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j)
            if (!(a[i]&a[j])) {
                flag = true;
                break;
            }
        if (flag) break;
    }
    cout << (flag ? "YES\n" : "NO\n");
    return 0;
}