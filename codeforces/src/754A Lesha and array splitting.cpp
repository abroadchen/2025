//
// Created by Psy.C on 2026/9/1.
//
/**
n int 数组长度（输入）
a[N] int[105] 数组元素值 a[1..n]
fr[N] int[105] 第 i 段的 起点下标
to[N] int[105] 第 i 段的 终点下标
- n0 ： 数组中非零元素的个数 （后续要统计）。
- cnt ： 最终分成的段数 ，初始 0。
- 循环读入 n 个元素到 a[1..n] 。
- if (a[i]) n0++ ：读入同时 统计非零元素个数 （ a[i] 非零时 a[i] 为真）。
数组 没有任何非零元素 → 不可能分成"每段恰好一个非零元素"的段 → 直接输出 NO 结束。
循环从左到右遍历数组。每次遇到一个新的非零元素时， cnt++ （段数+1），把当前位置作为 新段的起点 fr[cnt] = i 。
- --n0 ：消费掉一个非零元素（还剩 n0-1 个没处理）。
- 如果 --n0 之后变成了 0 → 所有非零元素都处理完了 → 跳出循环。此时最后一段的起点已经记录，终点留到循环结束后填。
跳到下一个非零元素 ：
- 循环跳过连续的零。
- 退出循环时 i 停在下一个非零元素的位置。
- 这个位置 就是当前段的终点 （因为当前段要到"下一个非零元素之前"结束）。
把当前段的终点设为刚才跳到的非零元素位置 i 。
循环 break 出来后，最后一段的终点 to[cnt] 还没填（因为 break 在填 to 之前）。把它填为 n （数组末尾），覆盖剩余的所有元素。
- cout << "YES" ：有解，输出 YES（前面已经过滤了 n0==0 的情况）。
- cout << cnt ：段数。
- 循环输出每段的起点和终点 。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, a[N], fr[N], to[N];
int main() {
    fast;
    cin >> n;
    int n0 = 0, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i]) n0++;
    }
    if (n0 == 0) { cout << "NO" << '\n'; return 0; }
    for (int i = 1; i <= n; ++i) {
        fr[++cnt] = i;
        if (--n0 == 0) break;
        while (a[i] == 0) i++;
        to[cnt] = i;
    }
    to[cnt] = n;
    cout << "YES" << '\n' << cnt << '\n';
    for (int i = 1; i <= cnt; ++i)
        cout << fr[i] << ' ' << to[i] << '\n';
    return 0;
}