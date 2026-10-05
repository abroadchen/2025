//
// Created by Psy.C on 2026/10/5.
//
/**
a 是个 2 字符字符串（a[0]、a[1] 是内容，a[2] 是 '\0'）。目标串。
n：接下来会读入 n 个词。
每轮循环读入一个 2 字符的词 b，然后检查。注意 goto end 会直接跳出循环跳去输出。
所以输入形如：第一行一个 2 字符目标串和一个整数 n，接下来 n 行，每行一个 2 字符词
k1：是否遇到过"首字符 = 目标串第 2 个字符"的词。
k2：是否遇到过"末字符 = 目标串第 1 个字符"的词
对于目标串 a = a[0]a[1]。判断能否"拼出"目标串：

情形 1：某个读入的词恰好等于目标串 a（b[0]==a[0] && b[1]==a[1]）→ 直接 YES。
情形 2：存在两个词，其中一个的首字符等于 a[1]（b[0]==a[1]），另一个的末字符等于 a[0]（b[1]==a[0]）→ 即把两个词"各取一个字符"拼起来能得到目标串 → YES。
这就是
k
1
k1 和
k
2
k2 的含义：$a[1]$ 出现在某个词的开头，且 $a[0]$ 出现在某个词的末尾，那么可以取"词1的首 + 词2的末"拼出
a
[
0
]
a
[
1
]
a[0]a[1]。
两种情形任一满足就 goto end 输出 YES，否则输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char a[3], b[3];
int n;
bool k1, k2;
int main() {
    fast;
    cin >> a >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> b;
        if (b[1] == a[1] && b[0] == a[0]) goto end;
        if (b[0] == a[1]) k1 = 1;
        if (b[1] == a[0]) k2 = 1;
        if (k1&&k2) goto end;
    }
    cout << "NO";
    return 0;
    end:
    cout << "YES";
    return 0;
}