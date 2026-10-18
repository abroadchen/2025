//
// Created by Psy.C on 2026/10/17.
//
/**
a[N]：整数数组；l = -inf, r = +inf：答案区间的下界、上界（初始为全部整数）。
s[N]：字符数组，存判定串（从下标 1 开始）
读入 n、数组 a[1..n]、判定串 s[1..n]。
主循环从 i=5 到 n，只处理长度为 5 的"窗口" a[i-4..i]（对应 s[i-4..i]）。
条件判断 s[i] != s[i-1] && (s[i-1]==s[i-2] && s[i-3]==s[i-4] && s[i-2]==s[i-3])：
它检查的是：在窗口末尾 位置 i 与它前一位不同，而 前 4 位（i-1,i-2,i-3,i-4）全部相等（即 s[i-1]==s[i-2]==s[i-3]==s[i-4]）。
也就是说：这是一段连续的 4 个相同字符，然后在 i 处发生反转——形如 ... X X X X Y（X 连续4个，Y≠X）。
这是一个"0/1 判定序列中一段 4 连 '1' 或 4 连 '0' 的边界"。
若命中这个模式，则根据第 i 位的值 s[i] 来收紧答案区间：
若 s[i]=='1'（新增的一位是 '1'）：对窗口内 5 个位置 a[i-4..i] 都执行 l = max(l, a[j]+1)，即下界 l 提升到这些元素+1 的最大值。
若 s[i]=='0'：对 5 个位置执行 r = min(r, a[j]-1)，即上界 r 压低到这些元素−1 的最小值。
最后输出 l r。
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; i++)
using namespace std;

constexpr int N = 1e5+5, inf = 1e9;

int n, a[N], l(-inf), r(inf);
char s[N];
int main() {
    scanf("%d", &n);
    rep(i,1,n) scanf("%d", &a[i]);
    scanf("%s", s+1);
    rep(i,5,n) {
        if (s[i] != s[i-1] && (s[i-1] == s[i-2] && s[i-3] == s[i-4] && s[i-2] == s[i-3])) {
            if (s[i] == '1') rep(j,i-4,i) l = max(l, a[j]+1);
            else rep(j,i-4,i) r = min(r, a[j]-1);
        }
    }
    printf("%d %d", l, r);
    return 0;
}