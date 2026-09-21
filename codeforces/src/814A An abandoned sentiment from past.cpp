//
// Created by Psy.C on 2026/9/21.
//
/**
lst 记录最后一个 0 的位置（代码只在 k==1 时用到它）
b 中至少有两个不同（或可排列的）数，无论怎样，总是存在一种填法让数组出现下降（把这两个数按降序放进相邻 0 位即可），因此答案为 Yes。这是思维题的反证思路——只要能构造出下降就输出 Yes。
（严格说这依赖 b 中元素可任意排列填 0 位。）
只有一个待填数 b[0]，把它填进最后一个 0 位（lst）。
填完后扫描整个数组，只要存在一处 a[i] < a[i-1]（下降）就说明不严格递增，输出 Yes；否则 No。
为什么要填在"最后一个 0 位"？因为做法只需判断是否存在下降，填哪个 0 位理论上都能覆盖主要情况；填最后一位配合整体扫描是常见写法
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 205;
int n, k, a[N], b[N];
int main() {
    fast;
    while (cin >> n >> k) {
        int lst = -1;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] == 0) lst = i;
        }
        for (int i = 0; i < k; ++i) cin >> b[i];
        if (k > 1) cout << "Yes\n";
        else {
            a[lst] = b[0];
            bool flg = false;
            for (int i = 1; i < n; ++i)
                if (a[i] < a[i-1]) {
                    flg = true; break;
                }
            if (flg) cout << "Yes\n"; else cout << "No\n";
        }
    }
    return 0;
}