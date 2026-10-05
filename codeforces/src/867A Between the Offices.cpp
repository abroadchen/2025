//
// Created by Psy.C on 2026/10/4.
//
/**
scanf("%d%c", &n, &c)：读入整数 n 和紧接着的一个字符到 c（这个 c 用来吃掉数字后的空白/换行）。
k = getchar()：再读一个字符作为第一个字符 k。
接下来循环 i=1..n-1，用 getchar() 逐个读入剩下的 n-1 个字符。
所以输入应该是形如：第一行一个整数 n，后面紧跟一串长度为 n 的字符（字符只有 S 和另外某种字符，代码里只区分 'S' 和其他）
n：字符总数。
x、y：两个计数器，初始为 0。
c：当前读到的字符；k：上一个字符（k 取的是 "previous/keep" 的意思）。
读入 n，c 吃掉数字后的分隔符（换行等），k 读入第一个真实字符
循环依次比较相邻字符对 (k, c)：

如果相邻两个字符相同，什么都不做。
如果相邻两个字符不同：
前一个字符是 'S'（变成非 S）→ x++
前一个字符是别的（变成 S）→ y++
比较 x 和 y，x > y 输出 YES，否则输出 NO
 */
#include <bits/stdc++.h>
using namespace std;


int main() {
    int n, x(0), y(0); char c, k;
    scanf("%d%c", &n, &c); k = getchar();
    for (int i = 1; i < n; ++i) {
        c = getchar();
        if (k != c) {//相邻两个字符不同
            if (k == 'S') x++;//这个"变化"是从 S 变到别的 → x++
            else y++;//这个"变化"是从别的变到 S → y++
        }
        k = c;//更新上一个字符
    }
    if (x > y) printf("YES\n"); else printf("NO\n");
    return 0;
}