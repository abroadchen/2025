//
// Created by Psy.C on 2026/10/9.
//
/**
如果 x <= c/2（较小的数），从左往右扫描，找第一个满足 x < a[i] 或 a[i]==0（空位）的位置填入。即以"前一半"为基准，把小值尽量往前放，同时保证有序性——x < a[i] 表示把 x 插到第一个大于它（或空）的位置，使左侧保持较小、不会破坏升序。
如果 x > c/2（较大的数），从右往左扫描，找第一个满足 x > a[i] 或空位的位置填入。即大值尽量往后放。
两段合起来的效果：小的一半从左往右填升序，大的一半从右往左填降序地就位，最终让整个数组保持非递减有序（因为它结合了左右两端的贪心放置）。

cout << endl 在交互题中用于刷新输出缓冲（endl 会 flush），把放置位置及时发送给裁判

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
int n, m, c, a[N];
int main() {
    fast;
    cin >> n >> m >> c;
    while (m--) {
        int x; cin >> x;
        if (x <= c/2) {
            for (int i = 1; i <= n; i++) {
                if (x < a[i] || a[i] == 0) {
                    a[i] = x;
                    cout << i << endl;
                    break;
                }
            }
        } else {
            for (int i = n; i; i--) {
                if (x > a[i] || a[i] == 0) {
                    a[i] = x;
                    cout << i << endl;
                    break;
                }
            }
        }
        cout << endl;
    }
    return 0;
}