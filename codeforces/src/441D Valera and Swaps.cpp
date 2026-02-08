//
// Created by Psy.C on 2026/2/8.
//
/**
f[MAXN]: 标记每个位置属于哪个循环（循环编号）
g[MAXN]: 存储置换数组，g[i]表示原来在位置i的元素现在应该去的位置
pos[MAXN]: 存储数值对应的位置索引

n: 置换数组的长度
m: 目标循环数量
ans: 答案变量（未使用）
sum: 记录当前循环的总数
t: 差值变量，用于记录操作次数

for (int x = i; !f[g[x]]; x = g[x]): 从位置i开始追踪循环
x = i: 从位置i开始
!f[g[x]]: 当目标位置g[x]还未被标记时继续
x = g[x]: 移动到下一个位置
f[g[x]] = f[i];: 将目标位置标记为当前循环编号

for (int i = 2; t < m; i++): 当当前循环数少于目标时，循环从位置2开始
if (f[1] != f[i]): 如果位置1和位置i不属于同一循环
t++;: 增加操作计数
for (int x = i; f[x] != f[1]; x = g[x]) f[x] = f[1];: 将i所在循环合并到1所在的循环
printf ("1 %d ", i);: 输出交换操作（将位置1和位置i交换）

for (int i = 1; t > m; i++): 当当前循环数多于目标时
if (g[i] != i): 如果位置i不是固定点（元素不需要留在原位）
for (int j = i + 1; j <= n && t > m; j++): 寻找另一个位置j
if (f[i] == f[j]): 如果i和j在同一循环中
printf ("%d %d ", i, j);: 输出交换操作
swap (g[i], g[j]);: 交换位置i和j的元素
t--;: 减少操作计数
if (g[i] == i) { f[i] = -1; break; }: 如果交换后i变成固定点，标记为-1并退出
f[i] = f[g[i]];: 更新i的循环标记
if (g[j] == j) f[j] = -1;: 如果j变成固定点，标记为-1
else { f[j] = ++sum; ... }: 否则重新计算j所在的新循环

 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3009;

int f[MAXN], g[MAXN], pos[MAXN];

int n, m, ans, sum, t;
int  main() {
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf ("%d", &g[i]), pos[g[i]] = i;

    scanf ("%d", &m);

    for (int i = 1; i <= n; i++)
        if (!f[i]) {
            f[i] = ++sum;//将位置i分配到新的循环编号
            for (int x = i; !f[g[x]]; x = g[x]) f[g[x]] = f[i];
        }

    t = n - sum;//需要的交换次数
    printf ("%d\n", m - t > 0 ? m - t : t - m);

    for (int i = 2; t < m; i++)
        if (f[1] != f[i]) {
            t++;
            for (int x = i; f[x] != f[1]; x = g[x]) f[x] = f[1];
            printf ("1 %d ", i);
        }

    for (int i = 1; t > m; i++) {
        if (g[i] != i)
            for (int j = i + 1; j <= n && t > m; j++)
                if (f[i] == f[j]) {
                    printf ("%d %d ", i, j);
                    swap (g[i], g[j]);
                    t--;
                    if (g[i] == i) {
                        f[i] = -1; break;
                    }
                    f[i] = f[g[i]];

                    if (g[j] == j)  f[j] = -1;
                    else {
                        f[j] = ++sum;
                        for (int x = j; f[g[x]] != sum; x = g[x]) f[g[x]] = sum;
                    }
                }
    }
    return 0;
}