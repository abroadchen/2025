//
// Created by Psy.C on 2026/9/2.
//
/**
- template<class T> ： 函数模板 ，可以读入任意数值类型（int、long long 等）
- void rd(T& x) ：通过 引用 参数修改外部变量（ rd(n) 后 n 就有值了）
f 负号标记： f=1 表示读到了负号 -
ch 当前读到的字符（初始 0）
x 累加的数值（初始 0）
- isdigit(ch) ：判断 ch 是否是数字字符（'0'~'9'）
- 循环直到读到 第一个数字 为止
- 如果中途遇到 '-' ，标记 f=1
- ch 是字符（如 '5' = ASCII 53 = 二进制 00110101 ）
- ch & 15 = ch & 0b1111 = 取低 4 位
- '0' & 15 = 48 & 15 = 0 ， '1' & 15 = 49 & 15 = 1 ，...， '9' & 15 = 57 & 15 = 9
- 快速把字符转成数字 （比 ch-'0' 少一次减法指令）
如果之前遇到过负号，取反。

N constexpr 每行最多 1024 个节点（估算容量）
s[512] char 读入字符串的缓冲区
rt int 根节点编号 = 0（Trie 树根在 0 号节点）
ch int [N*256][28] Trie 的邻接表 ： ch[节点编号][字符索引] = 子节点编号
cnt int 节点计数器 ：下一个新节点的编号
flag bool [N*256] 终止标记 ： flag[节点编号] = true 表示这里是一个完整字符串的结尾

strlen 从头扫描到 '\0' ，从 s+1 开始扫描。
nw = now，当前所在节点


读入：A 有 n 个字符串，B 有 m 个字符串。
把 A 的 n 个字符串全部插入 Trie 树
遍历 B 的 m 个字符串，每个都在 Trie 中查找：
- 找到 → 说明这个字符串 A 也有 → x++ （交集计数加 1）
- 没找到 → A 没有这个字符串，跳过
x 的含义 ：A 和 B 共同拥有 的字符串数量。
- n = n - x → A 独有 的字符串数（去掉交集部分）
- m = m - x → B 独有 的字符串数
两人轮流从自己的字符串中选一个 对方没有 的字符串删除（或者反过来），选不出来的人输。
 */
#include <bits/stdc++.h>
using namespace std;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

constexpr int N = 1024;
char s[512];
int rt = 0, ch[N*256][28], cnt;
bool flag[N*256];
void insert(char *s) {
    int n = strlen(s + 1);
    int nw = rt;
    for (int i = 1; i <= n; ++i) {
        if (ch[nw][s[i]-'a'] == 0)//当前节点没有这个子节点
            ch[nw][s[i]-'a'] = ++cnt;//新建一个节点，编号 = ++cnt
        nw = ch[nw][s[i]-'a'];//跳到子节点
    }
    flag[nw] = true;//最后一个节点标记为字符串终止点，表示"有一个字符串在这里结束了"。
}

bool find(char *s) {
    int n = strlen(s + 1);
    int nw = rt;
    for (int i = 1; i <= n; ++i) {
        if (ch[nw][s[i]-'a'] == 0) return false;
        nw = ch[nw][s[i]-'a'];
    }
    return flag[nw];
}

int main() {
    int n, m; rd(n); rd(m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        insert(s);
    }
    int x = 0;
    for (int i = 1; i <= m; ++i) {
        scanf("%s", s + 1);
        if (find(s)) ++x;
    }
    n -= x; m -= x;
    if (x&1) {
        if (n >= m) puts("YES");
        else puts("NO");
    } else {
        if (n > m) puts("YES");
        else puts("NO");
    }
    return 0;
}