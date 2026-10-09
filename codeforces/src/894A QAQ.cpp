//
// Created by Psy.C on 2026/10/9.
//
/**
pre[i]：前缀 Q 计数——字符串前
i
i 个字符（下标
0..
i
−
1
0..i−1）中 Q 的个数。
递推：pre[i] = pre[i-1] + (s[i-1]=='Q')。
nxt[i]：后缀 Q 计数——从下标
i
+
1
i+1 到末尾中 Q 的个数。
逆序递推：nxt[i] = nxt[i+1] + (s[i+1]=='Q')。
即：站在下标
i
i 这个位置，左边（不含自身）有 pre[i] 个 Q，右边（不含自身）有 nxt[i] 个 Q
枚举所有是 A 的位置作中间的那个 A。
对该 A：左边任意选一个 Q（pre[i] 种）、右边任意选一个 Q（nxt[i] 种），构成一个 QAQ 子序列。
乘法原理累加 pre[i]*nxt[i]
输出总方案数
O(len)，空间
O
(
l
e
n
)
O(len)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char s[101];
vector<int> pre, nxt;
int main() {
    fast;
    cin >> s;
    int len = strlen(s); pre.resize(len+1); nxt.resize(len+1);
    pre[0] = 0; nxt[len-1] = 0;
    for (int i = 1; i < len; ++i) {
        pre[i] = pre[i-1];
        if (s[i-1] == 'Q') pre[i]++;
    }
    for (int i = len-2; i >= 0; --i) {
        nxt[i] = nxt[i+1];
        if (s[i+1] == 'Q') nxt[i]++;
    }
    int cnt = 0;
    for (int i = 0; i < len; ++i) {
        if (s[i] == 'A') cnt += pre[i]*nxt[i];
    }
    cout << cnt << '\n';
    return 0;
}