//
// Created by Psy.C on 2025/9/28.
//
/*
*给定数字1到n
为每个数字分配权重（1, 2, 3）
目标是使加权和为质数
Σ(i×权重_i) = 质数
 *
*N = 6000: 最大n值
M = 783: 素数个数上限（6000以内约有783个素数）
p[]: 存储素数的数组
cnt: 素数计数器
vis[]: 埃拉托斯特尼筛法的标记数组
 *
*实现线性筛法（欧拉筛）：

如果i是素数，加入素数表
对每个i，用已知素数标记合数
1ll * i * p[j] 防止溢出
if (!(i % p[j])) break 确保每个合数只被最小素因子标记一次
 *
 *计算s = 1+2+...+n = n×(n+1)/2
 *
 *如果s本身是素数，所有权重都设为1
 *
*当s是偶数时：

寻找素数i (2≤i≤n)，使得s-i也是素数
将第i个数的权重设为2，其余为1
总和变为：s-i×1+i×2 = s+i
但代码实际是：(s-i)+i×2 = s+i（这里逻辑有简化）
更准确的理解：将数字i的权重从1改为2，增加量为i，新和为s+i
 *
*当s是奇数时：

子情况3.1：如果s-2是素数

将数字2的权重改为2
新和为s-2×1+2×2 = s+2
子情况3.2：否则

寻找素数i (i≠3)，使得s-i-3是素数
将数字i权重改为2，数字3权重改为3
新和为s-i×1-3×1+i×2+3×3 = s+i+6
 *
*基于哥德巴赫猜想的思想：

每个充分大的偶数都可以表示为两个素数之和
每个充分大的奇数都可以表示为三个素数之和
 *
 *
*预处理：O(n)（线性筛）
主算法：O(n√n)（素数判断）
空间复杂度：O(n)
 *
 *
 *
*这里的 i^2 用作条件判断：

当 i = 2 时：
i ^ 2 = 0
0 在布尔上下文中为 false
所以 i^2 ? 1 : 2 返回 2
当 i ≠ 2 时：
i ^ 2 ≠ 0
非零值在布尔上下文中为 true
所以 i^2 ? 1 : 2 返回 1
 *
*i ^ j        // 判断 i 是否等于 j
i ^ 0        // 恒等于 i
i ^ i        // 恒等于 0
 *
 *
 */
#include <cmath>
#include <cstdio>
using namespace std;

const int N = 6000, M = 783;

int n, p[M + 5] = {}, cnt;
bool vis[N + 5] = {};


void fiter(const int n) {
    for (register int i = 2; i <= n; ++i) {
        if (!vis[i]) p[++cnt] = i;
        for (register int j = 1; j <= cnt && 1ll * i * p[j] <= n; ++j) {
            vis[i * p[j]] = true;
            if (!(i % p[j])) break;
        }
    }
}

bool isPrime(const int x) {
    for (register int i = 2; 1ll * i * i <= x; ++i) {
        if (!(x % i)) return false;
    }
    return x > 1;
}

void solve() {
    scanf("%d",&n);
    fiter(n);
    const int s = n * (n + 1) >> 1;
    if (isPrime(s)) {
        for (register int i = 1; i <= n; ++i)
            putchar('1'), putchar(i^n ? ' ' : '\n');
    } else if (!(s & 1)) {
        for (register int i = 2; i <= n; ++i) {
            if (!vis[i] && isPrime(s - i)) {
                for (register int j = 1; j <= n; ++j)
                    printf("%d", i^j ? 1 : 2), putchar(j^n ? ' ' : '\n');
                return;
            }
        }
    } else {
        if (isPrime(s - 2)) {
            for (register int i = 1; i <= n; ++i)
                printf("%d", i^2 ? 1 : 2), putchar(i^n ? ' ' : '\n');
        } else {
            for (register int i = 2; i <= n; ++i) {
                if (i ^ 3 && !vis[i] && isPrime(s - i - 3)) {
                    for (register int j = 1; j <= n; ++j)
                        printf("%d", j == 3 ? 3 : (j^i ? 1 : 2)), putchar(j^n ? ' ' : '\n');
                    return;
                }
            }
        }
    }
}

int main() {

    solve();
    return 0;
}