//
// Created by Psy.C on 2026/9/11.
//
/**
cal(n, r) = n - r + 1：这是一个用于计算"第 r 层某段的长度"的宏，常见于塔状/三角形构造问题（比如杨辉三角式的差分层）
a[N] 存储输入（差分系数数组），c[N*N] 存最终输出字符串，v 是写入指针，now 是当前交替的字符极性（0/1 交替）
从下往上（i = n 到 1）‍遍历。若当前 a[i] 已经是 0 就跳过（说明这一层不需要处理）。这里隐含一个贪心：从最低位开始，保证前面已处理的层不再被破坏
取出当前层数 a[i] 作为"这一层的重复份数"
对前 i 项做差分回减：a[j] -= (i-j+1)*d。因为 cal(i,j)=i-j+1。这相当于把"这层的影响"从前缀里扣除，保持后续差分数组的正确性——这是在构造差分数组时同步做前缀和的逆操作
把这层写成 d 次：每次向输出串末尾连续写入 i 个相同字符（循环 j=1..i），然后 now ^= 1 把字符极性翻转（a 变 b、b 变 a），即相邻层字符不同、交替出现
输出拼接好的字符串 c（从下标 1 开始，故 c+1）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define cal(n,r) ((n)-(r)+1)
using namespace std;
constexpr int N = 2003;
int n, a[N], v, now;
char c[N*N];
int main() {
    fast;
    cin >> n;
    int i;
    for (i = 1; i <= n; ++i) cin >> a[i];
    for (i = n; i; --i) {
        if (!a[i]) continue;
        int d = a[i];
        for (int j = 1; j <= i; ++j)
            a[j] -= cal(i, j)*d;
        while (d--) {
            for (int j = 1; j <= i; ++j) c[++v] = now + 'a';
            now ^= 1;
        }
    }
    printf("%s", c+1);
    return 0;
}