//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
s[]：当作栈用的字符数组。
pos：栈顶指针（当前栈内字符个数 / 下一个写入位置）。
tot：统计被消除（成功配对抵消）的对数
getchar() 逐字符读入。
第一个 while 循环一直跳过不是小写字母的字符（如换行、空格、数字等），直到读到一个合法的小写字母 a–z 为止。
这是为了定位到输入中第一段连续小写字母的开头
这是主循环：只要当前字符是小写字母就继续处理。
内部的 if ('a' > ch || ch > 'z') break; 实际上是个冗余判断——因为在进入主循环前已经保证 ch 是小写字母，且循环体里 ch 是在末尾才被重新赋值，所以这个 break 理论上是多余的（防御性写法，不会真正触发）。它等价于主循环条件的再一次检查，可视为冗余但无害
如果栈非空（pos != 0）：
若当前字符 ch 与栈顶 s[pos-1] 相同 → 发生"配对消除"：计数 ++tot（消除了一对），并 --pos（弹出栈顶，即这一对都被消掉，不是只消一个，而是两个相同字符互相抵消）。
否则（不相同）→ 把当前字符 入栈：s[pos++] = ch。
如果栈为 空（pos == 0）：直接把当前字符入栈
读取下一个字符，继续循环
根据消除的对数 tot 的奇偶性输出：
tot 为偶数 → 输出 "No"
tot 为奇数 → 输出 "Yes
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

char s[N];
int pos, tot;
int main() {
    fast;
    char ch = getchar();
    while ('a' > ch || ch > 'z') ch = getchar();
    while ('a' <= ch && ch <= 'z') {
        if ('a' > ch || ch > 'z') break;
        if (pos != 0) {
            if (ch == s[pos-1]) ++tot, --pos;
            else s[pos++] = ch;
        } else s[pos++] = ch;
        ch = getchar();
    }
    if (tot%2 == 0) cout << "No\n"; else cout << "Yes\n";
    return 0;
}