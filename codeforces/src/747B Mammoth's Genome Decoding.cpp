//
// Created by Psy.C on 2026/8/25.
//
/**
- %d ：格式符，读取一个十进制整数存入 &n （ n 的地址），即序列长度 [ o bj ec tO bj ec t ] n 。
- ：格式符中的空格，匹配输入中整数与字符串之间的任意空白字符（空格、换行等）。
- %s ：格式符，读取一个不含空白字符的字符串存入 s （数组名 s 本身就是首元素地址，无需 & ）

若 [ o bj ec tO bj ec t ] n 是4的倍数，进入计数阶段：
- for 循环遍历序列的每个字符，索引 j 从 0 到 n-1
跳过未确定的碱基 ? ，不计数（ continue 直接进入下一次循环迭代）
- 若为'A'， a 加1；
- 否则若为'C'， c 加1；
- 否则若为'G'， g 加1；
- 否则若为'T'， t 加1；
- 非A/C/G/T/ ? 的非法字符会被忽略（题目保证输入合法）。
循环结束后， a/c/g/t 分别存储原序列中已确定的A/C/G/T数量

- int v = n / 4 ：使用C++17的 初始化语句 （init-statement）语法，在 if 条件中声明变量 v ，值为 [ o bj ec tO bj ec t ] n /4 （每种碱基应有的目标数量）。
- 条件判断： c > v || a > v || g > v || t > v
- 若任一已确定碱基的数量 超过 目标值 [ o bj ec tO bj ec t ] v ，则无解（因为 ? 只能替换为缺少的碱基，无法删除已存在的碱基）。
- 若条件成立，输出 === 表示无解
若所有已确定的碱基数量都不超过目标值，进入补全阶段
再次遍历序列的每个字符，用于替换 ?
仅处理当前位置是 ? 的情况，已确定的碱基保持不变
按A→C→G→T的优先级，将 ? 替换为 数量仍未达目标 的碱基：
- 若A的数量 [ o bj ec tO bj ec t ] a < v ，替换为'A'， a 加1；
- 否则若C的数量 [ o bj ec tO bj ec t ] c < v ，替换为'C'， c 加1；
- 否则若G的数量 [ o bj ec tO bj ec t ] g < v ，替换为'G'， g 加1；
- 否则若T的数量 [ o bj ec tO bj ec t ] t < v ，替换为'T'， t 加1；
- 所有 ? 都会被替换（因为已通过可行性检查， ? 的数量恰好补足缺少的碱基）。
注意 ：替换顺序是固定的A→C→G→T，只要总数量符合要求，顺序不影响合法性（题目仅要求数量相等）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;

int main() {
    fast;
    int a = 0, g = 0, c = 0, t = 0, n;
    char s[N];
    scanf("%d %s", &n, s);
    if (n % 4 != 0) puts("===");
    else {
        for (int j = 0; j < n; ++j) {
            if (s[j] == '?') continue;
            if (s[j] == 'A') a++;
            else if (s[j] == 'C') c++;
            else if (s[j] == 'G') g++;
            else if (s[j] == 'T') t++;
        }
        if (int v = n / 4; c > v || a > v || g > v || t > v) puts("===");
        else {
            for (int j = 0; j < n; ++j) {
                if (s[j] == '?') {
                    if (a < v) { s[j] = 'A'; a++; }
                    else if (c < v) { s[j] = 'C'; c++; }
                    else if (g < v) { s[j] = 'G'; g++; }
                    else if (t < v) { s[j] = 'T'; t++; }
                }
            }
            cout << s << '\n';
        }
    }
    return 0;
}