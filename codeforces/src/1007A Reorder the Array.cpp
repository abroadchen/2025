//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
读入 n 个数，sort 升序排序。
排序后小元素在前，贪心策略通常是把"小的"去匹配尽可能成立的最小"更大的"元素，得到最多对
指针 i 用来定位"待匹配的小元素"，指针 j 用来找"可以被匹配的更大元素"。
循环条件：i < n-1 && j < n（i 到倒数第二、j 不越界）
每轮 i 本来自增 1。但 for 每轮会再 i++。
若 s[j] <= s[i]（匹配失败），执行 i--，把下一轮的 i++ 抵消，使 i 停留在原位，重新尝试当前 i（因为 j 已经移到了更大的位置，也许能配上了）。
若 s[j] > s[i]（成功），则 i 正常前进，配好一对。
简而言之：i 是待匹配的小值，j 始终往右找第一个大于 s[i] 的值；找到成一对并让 i 也前进，找不到则 i 退回重试 j 的下一个


当 j 已到 n-1（最后一个元素），循环体里再 j++ 会让 j == n，此时 s[j] 越界访问！若输入数据使 j 到末尾仍有未匹配的 i，程序会访问 s[n] 越界（未定义行为）‍。

但通常由于排序后大数在后，s[j] > s[i] 的贪心会让 j 不至于在 i 没配完时就撞到末尾，除非 n 较小。严格讲这段代码存在潜在数组越界风险，正确的书写通常会在访问 s[j]、s[i] 前判断 j < n。

所以主流题解做这个贪心时更常见的写法是：

for (int i = 0, j = 0; j < n && i < n; ) {
    if (s[j] > s[i]) { ans++; j++; i++; }
    else j++;
}
或

for (int i = 0, j = 1; j < n; ) {
    if (s[j] > s[i]) { ans++; i++; }
    j++;
}
都是"小 i 配大 j"的等价形式，且都先检查 j < n 再访问
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

int n, s[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s, s + n);
    for (int i = 0, j = 0; i < n-1 && j < n; i++) {
        j++;
        if (s[j] > s[i]) ans++; else i--;
    }
    cout << ans;
    return 0;
}