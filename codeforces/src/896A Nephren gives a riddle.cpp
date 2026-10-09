//
// Created by Psy.C on 2026/10/9.
//
/**
代码定义了两段字符串：

f = " What are you doing at the end of the world? Are you busy? Will you save us?"（注意开头有空格，索引 0 是空格）
fn = " What are you doing while sending \"\"? Are you busy? Will you send \"\"?"（\" 是转义的双引号 "）
题目大意：定义一个递归字符串序列
S
n
S
n
​
 ，其中：

S
0
=
f
S
0
​
 =f（基础串）
S
n
=
f
n
S
n
​
 =fn 的模板，但其中两处 "\"\""（即 ""）被替换成
S
n
−
1
S
n−1
​
 。
所以
S
n
=
A
+
S
n
−
1
+
B
+
S
n
−
1
+
C
S
n
​
 =A+S
n−1
​
 +B+S
n−1
​
 +C，其中：

前缀 A = " What are you doing while sending "（含两个引号占位）
中间 B = "? Are you busy? Will you send "
后缀 C = "?"
让me数一下 fn 的具体位置。fn = " What are you doing while sending ""? Are you busy? Will you send "?"

（fn 开头空格，两个 "" 是占位，后面 ? 也带引号）
len[0] = 75 = 字符串 f 的长度（去掉开头空格？让me数）。f = " What are you doing at the end of the world? Are you busy? Will you save us?" 共 75 字符（含开头空格）。
递推：len[n] = 2·len[n-1] + 68。因为
S
n
S
n
​
  由两个
S
n
−
1
S
n−1
​
  加上固定部分（前缀+中间+后缀共 68 个固定字符）。
当增长超过 inf=1e18 时标记为 -1（表示"无限长/溢出"，后续按无限处理）。
注意 if (len[i-1] < 0 || len[i] > inf) len[i] = -1：一旦某层超过上限就置 -1，并且因为 len[i-1]<0 也会让后续全是 -1（长度溢出后所有更大层都是 -1=无穷
dfs(n,k) 输出
S
n
S
n
​
  的第 k 个字符。按结构
S
n
=
A
+
S
n
−
1
+
B
+
S
n
−
1
+
C
S
n
​
 =A+S
n−1
​
 +B+S
n−1
​
 +C 分段：

让me确定 A、B、C 的长度。fn 固定部分中，前缀 A（在第一个 S_{n-1} 前）长度应为 34，中间 B（在两个
S
n
−
1
S
n−1
​
  之间）长度 32，后缀 C 长度 2。这样 34 + 32 + 2 = 68 ✓（固定字符共 68），加上两个
S
n
−
1
S
n−1
​
 。

分段判断（k 是 0-based 索引，fn 开头也是空格所以 fn[k] 直接索引）：

n==0：直接取 f[k]。
k < 35：落在前缀 A（34 个固定字符），输出 fn[k]。注意这里的边界条件。前缀 A 长度是 34（索引 0..33），但条件用 k<35——略宽松，实际因为后面判断 k>34 && k<len[n-1]+35 是进入第一个递归，所以 0..33 归前缀，34 也被 k<35 吃了。嗯，边界细节暂不深究，思路是分段。
第一个 S_{n-1} 段：k>34 && k<len[n-1]+35 → dfs(n-1, k-34)。前缀 A 占 34 个字符，减去后进入
S
n
−
1
S
n−1
​
 。
中间 B 段：k>len[n-1]+34 && k<len[n-1]+67 → fn[k-len[n-1]]。此时 k 减去 len[n-1]（前一个
S
n
−
1
S
n−1
​
 ）定位到 B 的 32 个字符。
第二个 S_{n-1} 段：k>len[n-1]+66 && k<len[n-1]*2+67 → dfs(n-1, k-len[n-1]-66)。减去前缀+第一个
S
n
−
1
S
n−1
​
 +B 后再进
S
n
−
1
S
n−1
​
 。
后缀 C：fn[k-len[n-1]*2]，最后 2 个字符。
当 len[n-1]==-1（无限长）时直接递归到 n-1（因为无限长时前一个 S 覆盖绝大部分，直接进入递归）
读入 q 组询问。
每组：n、k。
若 k > len[n] 且 len[n] != -1（即 k 越界超出第 n 层串长）→ 输出 .（句点）。
否则 dfs 输出第 k 个字符
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e5;
constexpr ll inf = 1e18;
ll len[N+5];
void init() {
    len[0] = 75;
    for (int i = 1; i <= N; i++) {
        len[i] = len[i-1]*2 + 68;
        if (len[i-1] < 0 || len[i] > inf)
            len[i] = -1;
    }
}

string f=" What are you doing at the end of the world? Are you busy? Will you save us?";
string fn=" What are you doing while sending \"\"? Are you busy? Will you send \"\"?";
void dfs(int n, ll k) {
    if (n == 0) { putchar(f[k]); return; }
    if (k < 35) { putchar(fn[k]); return; }
    if (len[n-1] == -1 || k > 34 && k < len[n-1]+35) { dfs(n-1, k-34); return; }
    if (k > len[n-1]+34 && k < len[n-1]+67) { putchar(fn[k-len[n-1]]); return; }
    if (k > len[n-1]+66 && k < len[n-1]*2+67) { dfs(n-1, k-len[n-1]-66); return; }
    putchar(fn[k-len[n-1]*2]);
}

inline ll rd() {
    ll x = 0; bool flg = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') flg = 0;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (flg) x = -x;
    return ~(x-1);
}

int q, n; ll k;
int main() {
    init(); q = rd();
    while (q--) {
        n = rd(), k = rd();
        if (k > len[n] && len[n] != -1) { putchar('.'); continue; }
        dfs(n, k);
    }
    return 0;
}