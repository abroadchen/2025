//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
a 存棋子的某个位置（数量为 n/2）
i 从 x 开始，每次 +2，一共走 n/2 个位置（因为 (n-x)/2 + 1 步，恰好 n/2 个）。
ret += abs(a[cnt]-i)：第 cnt 个棋子 a[cnt] 移动到目标位置 i 的花费是 |a[cnt] - i|，累加。
返回总花费。
while (cin >> n)：多组数据，直到输入结束（读到 EOF）。每组给一个 n。
for (int i = 0; i < n/2; ++i) cin >> a[i];：读入 n/2 个棋子的位置（下标从 0 开始）。
sort(a, a+n/2);：棋子位置升序排序（贪心匹配的前提：排序后与目标位置一一对应总代价最小）。
cout << min(get(1), get(2)) << '\n';：取两种偏移（从位置 1 开始：1,3,5,... / 从位置 2 开始：2,4,6,...）中的较小总代价并输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 200;
int n, a[N];
int get(int x) {
    int cnt = 0, ret = 0;
    for (int i = x; i <= n; i += 2) {
        ret += abs(a[cnt]-i);
        ++cnt;
    }
    return ret;
}


int main() {
    fast;
    while (cin >> n) {
        for (int i = 0; i < n/2; ++i) cin >> a[i];
        sort(a, a+n/2);
        cout << min(get(1), get(2)) << '\n';
    }
    return 0;
}