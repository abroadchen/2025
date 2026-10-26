//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
n：科目数。
a[N]：各科分数。
sum：当前总分
读 n，读入 n 个分数并累加进 sum
将分数从小到大排序（为了最小改动次数，优先改低分，收益最大）
循环 i 从 0 到 n。
循环体更新（第三个表达式）：sum = sum - a[i] + 5：
把第 i 科原分数 a[i] 拿掉，加上满分 5（假设满分 5，改成 5 分）。

注意第一次迭代 i=0 时 a[0] 未定义/越界（a[0] 没被读入，是垃圾值）——实际上这里 i=0 时 sum 不变（由于 a[0] 未被赋值，通常是 0 导致 sum 少加一个垃圾值，但通常写这题的默认 a 是 0 索引边界或把 i=0 作为初始未改动态）。这里的写法依赖 a[0] 为 0（全局数组默认 0）。

准确讲：第一次 i=0 迭代时条件用初始 sum 判断；然后 sum 被更新为 sum-a[1]+5（第 1 科提到满分）；i=1 时判断…… 由于全局数组 a[0]=0，i=0 时 sum - a[0] + 5 = sum+5 会多 5，但这第一次更新不被使用于判断（判断在更新前），所以逻辑基本还是正确的——第 i 次更新表示"已把前 i 科提到满分"
若当前总分满足 sum >= 4.5*n（平均分 ≥ 4.5），则输出当前已改的科数 i，并 exit(0) 终止程序。
因为是从小到大排序后先改最低分（提升最大），所以找到的第一个满足条件的 i 就是最少需要改的科目数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 105;

int n, a[N], sum;
void init() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], sum += a[i];
    sort(a+1, a+n+1);
    for (int i = 0; i <= n; ++i, sum = sum-a[i]+5)
        if (sum >= 4.5*n) cout << i, exit(0);
}


int main() {
    fast;
    init();
    return 0;
}