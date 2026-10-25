//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
s：存放字符串，从下标1开始（s+1）
v[i][0..2]：标记位置 i 附近是否出现过字母 A(0) / B(1) / C(2)
从 s[1] 开始读字符串，len 为其长度
对每个字符位置 i：

若 s[i] 是字母（isalpha）：
cur = s[i] - 'A'：把字母映射到 0(A)、1(B)、2(C)。例如 'A'→0，'B'→1，'C'→2。
将这个字母"存在"标记到三个位置：i-1、i、i+1。即 该字母的水平邻居（左、右）+ 自身 都被记录为"附近有这个字母"。
注意：v[i][cur] 的第二维是 0/1/2 对应 A/B/C，下标 i 是字符串位置。v[i-1]、v[i+1] 用 bool 数组且在边界（i-1=0 或 i+1=len+1）处也无妨，因为 bool 数组越界访问虽然未定义但在此场景往往不致命（N=1007 预留了边界
遍历所有位置 i，若某位置 v[i][0] && v[i][1] && v[i][2]（即 A、B、C 三种字母都出现在该位置附近）同时为真 → 输出 "Yes" 并 return 0。

否则输出 "No"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
using namespace std;

constexpr int N = 1007;

char s[N];
bool v[N][3];
int main() {
    fast;
    scanf("%s", s+1);
    int len = strlen(s+1), i;
    rep(i,len) if (isalpha(s[i])) {
        int cur = s[i] - 'A';
        v[i-1][cur] = v[i+1][cur] = v[i][cur] = true;
    }
    rep(i,len) if (v[i][0] && v[i][1] && v[i][2]) return cout << "Yes\n", 0;
    cout << "No\n";
    return 0;
}