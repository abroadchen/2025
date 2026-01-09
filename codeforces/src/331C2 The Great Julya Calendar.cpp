//
// Created by Psy.C on 2026/1/9.
//
/**
* step: 步数（计算结果）
rem: 余数
node() 默认构造函数：将 step 设为 -1（用作未计算的标记）
node(const int s, const int r) 参数构造函数：初始化 step 和 rem
f[10][20][11]: 记忆化数组，用于动态规划缓存
 *tp: 存储 10 的幂次，即 tp[i] = 10^i
 *
*h: 高位的最小值约束
n: 当前处理的位数
x: 当前数字
k: 用于记忆化索引的参数
~key.step 检查是否已计算过（-1 的按位取反为 0）
*如果只有一位数字
如果 x >= h，需要一步操作，余数为 0
否则不需要操作，余数为 x
 *
*cnt: 当前计数
cur: 当前数字的低位部分
t: 当前数字的最高位
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

struct node {
    int step, rem{};
    node() { step = -1ll; }
    node(const int s, const int r) : step(s), rem(r) {}
} f[10][20][11];

int tp[20];
node query(const int h, const int n, int x) {
    const int k = x / 10 == tp[n-1] - 1 ? x % 10 : 10;//当前数字的高位部分是否达到最大值
    node& key = f[h][n][k];//获取对记忆化数组元素的引用
    if (~key.step) return key;//~(-1) 等于 0，所以当 step = -1 时条件为假
    if (n == 1) {
        if (x >= h) return key = {1, 0}; else {
            return key = {0, x};
        }
    }
    int cnt = 0, cur = x % tp[n-1], t = x / tp[n-1];
    while (t >= 0) {
        //处理剩余 n-1 位，约束值为 max(h, t)，当前数字为 cur
        const node tmp = query(max(h, t), n - 1, cur);
        //累加子问题的步骤数 更新当前余数为子问题的余数
        cnt += tmp.step; cur = tmp.rem;
        if (t) {
            cur = cur + tp[n-1] - max(h, t);//更新当前余数：加上 tp[n-1]（10^(n-1)）并减去约束值
            cnt++;//步数加 1
        }
        t--;//最高位数字减 1，继续循环
    }
    return key = {cnt, cur};
}

signed main() {
    fast;
    tp[0] = 1ll;
    for (int i = 1; i <= 18; ++i) tp[i] = tp[i-1] * 10ll;
    tp[19] = 9000000000000000000ll;
    int n, p = 0; cin >> n;
    if (n == 0) { cout << "0"; return 0; }
    while (tp[p] <= n) p++;//计算数字 n 的位数，找到最小的 p 使得 10^p > n
    const node x = query(0, p, n);//从第 0 位约束开始，处理 p 位，数字为 n
    cout << x.step;
    return 0;
}