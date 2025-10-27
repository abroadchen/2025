//
// Created by Psy.C on 2025/10/27.
//
/*
*N: 数组大小上限 (1,100,000)
M: 数值范围上限 (10,000,000)
*n: 输入数字的个数
a[N]: 存储输入的数字
p[N]: 并查集的父节点数组
q[20*N]: 用于快速查找数字在a中位置的索引数组
 *
*并查集的查找函数，采用路径压缩优化：
如果u是根节点则返回u
否则递归查找并直接将u的父节点设为根节点
 *
 *并查集的合并函数
 *找到u和v的根节点
 *随机选择一种方式合并两个集合，避免树的高度过高
 *
 *自定义求最大公约数函数
 *复制参数值到局部变量
 *当b2不为0时继续
 *计算b1除以b2的商
 *计算b1除以b2的余数
 *交换b1和b2，相当于b1=b2, b2=remainder
 *返回最大公约数（此时b2为0，b1即为gcd）
 *
 *读入n个数字，并初始化并查集（每个元素的父节点是自己）
 *去除重复元素，n变为去重后的元素个数
 *
 *
 *
 *枚举i值，生成毕达哥拉斯三元组
 *枚举j值，j从i+1开始，步长为2（保证奇偶性不同）
 *如果i和j不互质则跳过（避免生成重复的本原三元组）
 *根据公式生成毕达哥拉斯三元组：x² + y² = z²
 *如果这三个数中的任意两个都在输入数组中，则将它们合并到同一集合
 *
 *重新计算每个元素的根节点，确保并查集状态正确
 *对根节点数组排序
 *统计不同的根节点个数，即连通分量的个数
 *
 *
 *
 */
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1100000, M = 10000000;
int n, a[N], p[N], q[20*N];


int find(int u) { return p[u] == u ? u : p[u] = find(p[u]); }

void merge(int u, int v) {
    u = find(u), v = find(v);
    if (rand() % 2) p[u] = v;
    else p[v] = u;
}

int gcd(int x, int y) {
    int b1 = x, b2 = y;
    while (b2) {
        int f = b1 / b2;
        b1 -= f * b2;
        swap(b1, b2);
    }
    return b1;
}

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) { scanf("%d",&a[i]); p[i] = i; }
    sort(a, a+n);
    n = unique(a, a+n) - a;
    memset(q, -1, sizeof(q));
    for (int i = 0; i < n; ++i) q[a[i]] = i;//建立数字到其在数组中位置的映射关系

    for (int i = 1; i * i <= M; ++i) {
        for (int j = i + 1; j * j + i * i <= 2 * M; j += 2) {
            if (gcd(i, j) != 1) continue;
            int x = j * j - i * i, y = 2 * j * i, z = j * j + i * i;
            if (q[x] != -1 && q[y] != -1) merge(q[x], q[y]);
            if (q[x] != -1 && q[z] != -1) merge(q[x], q[z]);
            if (q[y] != -1 && q[z] != -1) merge(q[y], q[z]);
        }
    }
    for (int i = 0; i < n; ++i) p[i] = find(i);
    sort(p, p+n);
    int res = unique(p, p+n) - p;
    printf("%d\n", res);
    return 0;
}