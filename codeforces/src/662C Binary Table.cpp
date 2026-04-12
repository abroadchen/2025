//
// Created by Psy.C on 2026/4/11.
//
/**
实现快速沃尔什-哈达玛变换算法
lim: 变换的大小（必须是2的幂）
type: 1表示正向变换，-1表示逆向变换
执行迭代蝴蝶操作来计算变换
在逆变换中，除以lim进行归一化

第一层循环 for (int mid = 1; mid < lim; mid<<=1)
mid 表示当前正在处理的子问题规模
每次乘以2，从1开始逐步扩大到整个数组
模拟分治过程：1→2→4→8→...→lim
第二层循环 for (int i = 0; i < lim; i += mid<<1)
i 是每个大小为 mid<<1 的块的起始位置
每次跳跃 mid<<1 个位置到下一个块
保证处理完所有块
第三层循环 for (int j = 0; j < mid; ++j)
j 是块内相对位置
处理当前块的前后两半对应位置的配对
将 (f[i+j], f[i+j+mid]) 变换为 (f[i+j] + f[i+j+mid], f[i+j] - f[i+j+mid])
这种变换满足XOR卷积的性质
当 type == -1 时，进行逆变换：
除以 lim 进行归一化
这是因为正向变换过程中引入了缩放因子
时间复杂度
时间复杂度：O(n log n)，其中 n = lim
空间复杂度：O(1)（原地变换）


n: 输入矩阵的行数
m: 输入矩阵的列数
num[N]: 存储每列的位压缩表示
A[]: 列模式的频率数组
B[]: 位操作的距离数组

读取每行并将列压缩成位表示
每列存储为表示该列位的二进制数
A[num[i]]++: 计算每个列模式的频率
B[i] = B[i>>1]+(i&1): 计算每个状态的popcount（1的位数）
B[i] = min(B[i], n-B[i]): 取1和0的计数之间的最小值（因为我们能够翻转）
对两个数组应用正向FWT
元素间乘以变换后的数组（等效于时间域中的卷积）
应用逆FWT获取结果
将答案初始化为最坏情况（翻转所有内容）
在所有可能的解决方案中找到最小值
输出最小翻转次数
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fwt(ll *f, int lim, int type) {
    for (int mid = 1; mid < lim; mid<<=1)
        for (int i = 0; i < lim; i += mid<<1)
            for (int j = 0; j < mid; ++j) {
                ll p0 = f[i+j], p1 = f[i+j+mid];
                f[i+j] = p0 + p1, f[i+j+mid] = p0 - p1;
            }
    if (type == -1)
        for (int i = 0; i < lim; ++i)
            f[i] /= lim;
}

constexpr int N = 1e5+5;
int n, m, num[N];
char s[N];
ll A[1<<20], B[1<<20];
int main() {
    scanf("%d%d", &n, &m); int sta = 1<<n;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j)
            num[j] = (num[j]<<1) + s[j] - '0';
    }
    for (int i = 1; i <= m; ++i) A[num[i]]++;
    for (int i = 0; i < sta; ++i) B[i] = B[i>>1]+(i&1);
    for (int i = 0; i < sta; ++i) B[i] = min(B[i], n-B[i]);
    fwt(A, sta, 1), fwt(B, sta, 1);
    for (int i = 0; i < sta; ++i) A[i] *= B[i];
    fwt(A, sta, -1);
    ll ans = n*m;
    for (int i = 0; i < sta; ++i) ans = min(ans, A[i]);
    printf("%lld\n", ans);
    return 0;
}