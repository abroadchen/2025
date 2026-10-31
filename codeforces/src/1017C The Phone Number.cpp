//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
x = ⌊√n⌋，即 n 开根号后向下取整（因为 sqrt 返回 double，赋值给 int 会自动去掉小数部分）。x 作为块的标准长度
外层循环：i 从 1 开始，每步跳过 x，即遍历每个块的左端点。块的起始位置是 1, 1+x, 1+2x, ...
mn = i + x - 1：本块的右端点（块尾，即该块内最大数）。
mn = min(mn, n)：防止最后一块超出 n，把尾部截断到 n。例如 n=10, x=3，最后一块的块起始 i=10，mn=12，min(12,10)=10
块内倒序输出：从该块的最大数 mn 一路递减输出到块左端 i，每个数后跟一个空格。

例如块 [1,2,3]：mn=3，输出 3 2 1。
注意 while (mn >= i) 在最后一个块可能只有 1 个元素，也能正确输出
外层循环继续处理下一个块，直到 i > n 结束。整个输出就是 n..1 的分块倒序打印
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    int x = sqrt(n);
    for (int i = 1; i <= n; i += x) {
        int mn = i + x - 1;
        mn = min(mn, n);
        while (mn >= i) cout << mn << ' ', mn--;
    }
    return 0;
}