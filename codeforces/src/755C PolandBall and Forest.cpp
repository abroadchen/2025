//
// Created by Psy.C on 2026/9/2.
//
/**
n int 排列的大小
x int 临时变量，读入每个元素值
a[N] int[] 先存排列，后被复用为标记数组 （全局数组初始全 0）
ans int 累加计数器，最终答案

读入当前位置 i 上的 元素值 ，存入 x 。
x == i 返回布尔值 ：
- 如果元素值 x 恰好等于位置编号 i → true （1）→ ans += 1
- 如果元素值 x ≠ 位置编号 i → false （0）→ ans += 0 （不变）
ans 此时的含义 ： 固定点的数量 （元素 i 恰好在位置 i 上的情况）。
x == i （元素在正确位置） a[x] |= false(0) → a[x] 保持不变 值 x 在位置 x，不需要标记
x != i （元素在错误位置） a[x] |= true(1) → a[x] 强制置为 1 值 x 不在位置 x，标记"值 x 错位了"
遍历所有值 1~n ，如果 a[i] == 1 （值 i 错位了）→ cnt++ 。
因为错位值一定成对出现（x 在 y 的位置，y 在 x 的位置），所以除以 2 就是 错位对数 。
ans = 初始固定点数 + 错位对数

读入 + 统计 O(n) 遍历一次
统计 cnt O(n) 再遍历一次
总计 O(n) 两次线性扫描
时间复杂度 O(n)，空间复杂度 O(N)（全局数组大小）。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4+5;

int n, x, a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> x, ans += x == i, a[x] |= x != i;
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i]) ++cnt;
    ans += cnt / 2;
    cout << ans << '\n';
    return 0;
}