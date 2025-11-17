//
// Created by Psy.C on 2025/11/17.
//
/*
*N = 31451：最大元素个数
n：实际元素个数
a[N]：存储输入的数字序列
b[N]：标记数组，b[i]=1表示第i个元素属于第一个等差数列
p：栈顶指针，用于存储未被选择的元素
st[N]：栈，存储未被选择元素的索引
 *
*初始化栈顶指针p=0
遍历所有元素，将未被标记(b[i]=0)的元素索引压入栈st中
*如果栈为空，重置最后一个元素的标记
如果剩余元素个数≤1，返回true（单个元素或空集可视为等差数列）
*检查栈中元素对应的数值是否构成等差数列
计算公差：a[st[2]] - a[st[1]]
验证后续相邻元素差值是否都等于该公差
如果都相等返回true，否则返回false
 *
 *
 *初始化标记数组b，所有元素初始为0
*计算以a[x]和a[y]为前两项的等差数列公差d
标记第x个元素属于第一个等差数列
*从位置i开始，寻找下一个等差数列元素
如果a[j] == a[i] + d，说明a[j]是等差数列的下一项
标记该元素并更新当前位置i
*检查剩余未标记的元素是否能构成等差数列
如果可以，返回true
*如果不行，尝试去掉最后一个标记的元素
从后往前找到最后一个被标记的元素
取消该元素的标记
再次检查剩余元素是否能构成等差数列
 *
*先输出第一个等差数列（标记为1的元素）
换行
再输出第二个等差数列（未标记的元素）
 *
*以a[2],a[3]为起始的等差数列
以a[1],a[3]为起始的等差数列
以a[1],a[2]为起始的等差数列
 *
 *O(n)：每次solve函数最多遍历数组一次
 *
 */
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 31451;
int n, a[N], b[N], p, st[N];

bool ok() {
    p = 0;
    for (int i = 1; i <= n; ++i) if (!b[i]) st[++p] = i;
    if (!p) b[n] = 0;
    if (p <= 1) return 1;
    for (int i = 2; i <= p; ++i) {
        if (a[st[i]] - a[st[i - 1]] !=
            a[st[2]] - a[st[1]]) return 0;
    }
    return 1;
}

bool solve(int x, int y) {
    memset(b, 0, sizeof(b));
    int d = a[y] - a[x], i = x; b[i] = 1;
    for (int j = i; j <= n; ++j) if (a[j] == a[i] + d) {
        b[j] = 1; i = j;
    }
    if (ok()) return 1;
    x = n;
    while (!b[x]) x--;
    b[x] = 0;
    return ok();
}

void print() {
    for (int i = 1; i <= n; ++i) if (b[i]) printf("%d ", a[i]);
    puts("");
    for (int i = 1; i <= n; ++i) if (!b[i]) printf("%d ", a[i]);
}


int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    if (solve(2, 3)) print();
    else if (solve(1, 3)) print();
    else if (solve(1, 2)) print();
    else puts("No solution");
    return 0;
}