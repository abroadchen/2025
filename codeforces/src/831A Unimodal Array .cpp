//
// Created by Psy.C on 2026/9/24.
//
/**
n：序列长度；a[i]：序列元素。
f1、f2：状态标记，表示是否已经在某个"下降"阶段
关系	操作
a[i] == a[i-1]（相等）	f1 = true
a[i] < a[i-1]（下降）	f2 = true，并把 f1 置为 false
a[i] > a[i-1]（上升）	不直接改标记

已经下降过（f2==true）后又出现 a[i] >= a[i-1]：
即"降了又升"或"降了又平"，打破了"只降一次"的约束 → NO。
（对应"先升后降"里的"降下去就一路降到底，不能再回头"。）

f1==true 且 a[i] != a[i-1]：
出现过相等后又出现不等 → NO。
（序列一旦出现"相等"，则要求后续全部相等；否则视为非法。）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a[110];
bool f1, f2;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n; ++i) {
        if (a[i] == a[i-1]) f1 = true;
        if (a[i] < a[i-1]) { f2 = true; f1 = false; }
        if ((f2 == true && a[i] >= a[i-1]) ||
            (f1 == true && a[i] != a[i-1])) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}