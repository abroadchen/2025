//
// Created by Psy.C on 2025/9/19.
//
/*
*n: 元素种类数
w: 目标权重
dat[1005]: 存储每种元素的数量
sum: 所有元素数量的总和
pos: 值为1的元素的位置（如果存在）
res[1005]: 存储重新分配的数量
 *
*模板函数，用于输出数字并在后面添加空格
处理负数情况
将数字按位分解并输出
 *
 记录值为1的元素位置*
 *
检查不可能的情况：
w小于1或大于总和
只有一种元素但w不等于总和
w等于1但没有值为1的元素*
 *
 *如果只有一种元素，直接输出该元素2*dat[1]次
 *
*如果w=1，将值为1的元素放在序列两端
中间输出其他所有元素各2次
 *
 *
*一般情况的处理：
w减去2（为两端的特殊处理预留）
减少元素1和2的数量各1个
将剩余的w分配给各元素，存储在res数组中
构造序列：1 + 其他元素各2次 + 1,2 + 元素1各2次 + 2 + res中元素各2次
 *
 *
 *时间复杂度：O(sum) 空间复杂度：O(n)
 *
 *
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <cstdio>
using namespace std;

int n, w, dat[1005], sum = 0, pos = -1, res[1005];

template<class T> inline void putnum(T x) {
    if (x < 0) putchar('-'), x = -x;
    register short a[20] = {}, sz = 0;
    while (x) a[sz++] = x % 10, x /= 10;
    if (sz == 0) putchar('0');
    for (int i = sz - 1; i >= 0; --i) putchar('0' + a[i]);
    putchar(' ');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    cin >> n >> w;
    for (int i = 1; i <= n; ++i) {
        cin >> dat[i], sum += dat[i];
        if (dat[i] == 1) pos = i;
    }

    if (w < 1 || w > sum || (n == 1 && w != sum) || (w == 1 && pos == -1))
        return puts("No"), 0;
    puts("Yes");

    if (n == 1) {
        for (int i = 1; i <= 2 * dat[1]; ++i) putnum(1);
    } else if (w == 1) {
        dat[pos]--;
        putnum(pos);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= 2 * dat[i]; ++j)
                putnum(i);
        putnum(pos);
    } else {
        w = w - 2; dat[1]--; dat[2]--;
        for (int i = 1; i <= n; ++i)
            while (w && dat[i])
                res[i]++, w--, dat[i]--;
        putnum(1);
        for (int i = 2; i <= n; ++i)
            for (int j = 1; j <= 2 * dat[i]; ++j)
                putnum(i);
        putnum(1); putnum(2);
        for (int i = 1; i <= 2 * dat[1]; ++i) putnum(1);
        putnum(2);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= 2 * res[i]; ++j)
                putnum(i);
    }
    
    return 0;
}